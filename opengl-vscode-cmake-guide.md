# OpenGL + GLUT + VS Code + CMake Setup Guide

Clean setup steps, including the PATH/DLL pitfall found during troubleshooting.

> **⚠️ The #1 Windows gotcha:** if you have Anaconda/Miniconda installed, its `mingw-w64\bin` folder often sits _before_ MSYS2's in your system PATH and ships an older `libwinpthread-1.dll`. That mismatch causes silent compiler failures (exit code 1, no error text) or "entry point not found" errors from `cc1plus.exe`. Fix: in System Environment Variables → Path, move `C:\msys64\mingw64\bin` **above** any Anaconda/Conda path. Always fully restart VS Code after any PATH change.

---

## 1 · Compiler & GLUT installation

### Windows

1. Install **MSYS2** from `msys2.org`.
2. Open **MSYS2 UCRT64** (not the plain MSYS2 shell) and run:
   ```
   pacman -Syu
   pacman -Syu
   pacman -S mingw-w64-x86_64-toolchain --needed
   pacman -S mingw-w64-x86_64-freeglut
   ```
   Running `-Syu` twice is normal — the first pass updates core files and often closes the window.
3. Add `C:\msys64\mingw64\bin` to your **system PATH**, and make sure it's **above** any Anaconda/Conda entries (see warning above). Reorder via Environment Variables → Path → Move Up.
4. Verify in a _brand-new_ terminal (not one already open):
   ```powershell
   g++ --version
   $env:Path -split ';' | Select-String mingw64
   ```
5. Copy `libfreeglut.dll` from `C:\msys64\mingw64\bin` into your project folder (next to the future .exe), or add that bin folder to PATH — the DLL must be reachable at runtime.

### Linux

```bash
sudo apt update
sudo apt install build-essential cmake
sudo apt install freeglut3-dev
sudo apt install libgl1-mesa-dev libglu1-mesa-dev
```

Verify: `g++ --version` and `cmake --version`.

### macOS

```bash
xcode-select --install
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
brew install freeglut cmake
```

OpenGL itself ships with macOS as a framework (deprecated since 10.14 but functional); only freeglut needs Homebrew.

---

## 2 · VS Code

- Install VS Code, then the extensions: **C/C++** (Microsoft), **CMake Tools** (Microsoft), **CMake** (twxs, for syntax highlighting).
- Open your _project root folder_ directly (File → Open Folder) — not a parent folder — so `.vscode/` is found.

---

## 3 · Project layout

```
my-project/
├── CMakeLists.txt
├── main.cpp
└── .vscode/
    └── settings.json   (optional — CMake Tools mostly configures itself)
```

---

## 4 · CMakeLists.txt (cross-platform)

This single file builds correctly on Windows, Linux, and macOS — CMake Tools in VS Code detects it automatically, no manual `tasks.json` needed.

```cmake
cmake_minimum_required(VERSION 3.16)
project(GLUTApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- macOS: force Homebrew's freeglut instead of Apple's deprecated
# system GLUT.framework. Must be set BEFORE find_package(GLUT). ---
if(APPLE)
  if(EXISTS /opt/homebrew/lib/libglut.dylib)
    set(GLUT_glut_LIBRARY /opt/homebrew/lib/libglut.dylib)  # Apple Silicon
    set(GLUT_INCLUDE_DIR /opt/homebrew/include)
  elseif(EXISTS /usr/local/lib/libglut.dylib)
    set(GLUT_glut_LIBRARY /usr/local/lib/libglut.dylib)      # Intel Mac
    set(GLUT_INCLUDE_DIR /usr/local/include)
  endif()
  include_directories(${GLUT_INCLUDE_DIR})
endif()

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})

# --- Windows/MSYS2: freeglut's CMake config uses a different target name ---
if(WIN32)
  find_package(GLUT CONFIG QUIET)
  if(TARGET GLUT::GLUT)
    target_link_libraries(${PROJECT_NAME} PRIVATE GLUT::GLUT opengl32 glu32)
  else()
    target_link_libraries(${PROJECT_NAME} PRIVATE freeglut opengl32 glu32)
  endif()

  # Copy the freeglut DLL next to the exe automatically
  find_file(FREEGLUT_DLL libfreeglut.dll PATHS "C:/msys64/mingw64/bin")
  if(FREEGLUT_DLL)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different ${FREEGLUT_DLL} $<TARGET_FILE_DIR:${PROJECT_NAME}>)
  endif()
endif()
```

**Why the macOS block matters:** CMake's built-in `FindGLUT` module defaults to Apple's deprecated system `GLUT.framework` even when you've installed freeglut via Homebrew — and on some macOS/SDK combinations that produces a broken build target ("No rule to make target ... GLUT"). The block above forces CMake to use the Homebrew-installed freeglut instead, which avoids that bug and matches what step 1's `brew install freeglut` actually installed. It auto-detects both Apple Silicon (`/opt/homebrew`) and Intel (`/usr/local`) paths, so it works unmodified on either Mac type.

---

## 5 · Configure & build in VS Code

1. Open the project folder. VS Code should prompt **"CMake Tools: configure project?"** — click Yes. If not: `Ctrl+Shift+P` → "CMake: Configure".
2. Pick a **kit** when prompted:
   - **Windows:** choose the GCC entry pointing at `C:\msys64\mingw64\bin\g++.exe`. If it's missing, run `Ctrl+Shift+P` → "CMake: Scan for Kits".
   - **Linux/macOS:** the default GCC/Clang kit is usually correct.
3. Build: click **Build** in the CMake Tools status bar, or `Ctrl+Shift+P` → "CMake: Build" (`F7`).
4. Run: click the ▶ **Run** button in the status bar, or "CMake: Run Without Debugging" (`Shift+F5`).

This replaces the old `tasks.json` g++ command entirely — CMake Tools generates and re-runs the correct compile/link command every time automatically, including on Linux/macOS with their own paths, so you don't maintain three separate configs.

### Debugging

CMake Tools auto-generates a debug target. Set a breakpoint, then `F5` ("CMake: Debug") — no manual `launch.json` required for a standard single-executable project like this.

---

## 6 · Sanity checklist before you report a bug

All platforms:

- `g++ --version` and `cmake --version` both print cleanly in a _freshly opened_ terminal.
- The project folder opened in VS Code is the one that directly contains `CMakeLists.txt`.
- `CMake: Configure` output (View → Output → CMake/Build) shows `Found GLUT` and `Found OpenGL` with real paths, not blank.

Windows only:

- MSYS2's `mingw64\bin` is first among any `*\bin` folders containing `libwinpthread-1.dll` — this matters if you also have Anaconda, Git for Windows, or another MinGW install:
  ```powershell
  $env:Path -split ';' | %{if(Test-Path "$_\libwinpthread-1.dll"){$_}}
  ```
- VS Code was fully restarted (all windows closed, check Task Manager) after any PATH change — a new terminal tab alone is not enough.

macOS only:

- `find /opt/homebrew/lib /usr/local/lib -name "libglut*"` shows a file — confirms Homebrew's freeglut is actually installed and where.
- If configure still reports the system `GLUT.framework` instead of Homebrew's path, delete the `build/` folder and reconfigure — CMake caches the first result it finds.

Linux only:

- If `find_package(GLUT)` fails, you're missing `libgl1-mesa-dev` / `libglu1-mesa-dev` alongside `freeglut3-dev` — all three are required.

---

_freeglut · OpenGL · CMake Tools — tested against the Windows PATH/DLL issue found in this session._
