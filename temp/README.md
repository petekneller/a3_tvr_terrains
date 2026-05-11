# Tacview Recorder Linux Extension

This directory contains the source code and build system to compile the Tacview Recorder extension for Linux servers.

## Files
- `tacview_recorder.c`: The core C extension source code, refactored for cross-platform compatibility (Linux/Windows).
- `Makefile`: Build system to compile 32-bit (`tacview_recorder.so`) and 64-bit (`tacview_recorder_x64.so`) Linux libraries.
- `test_extension.c`: A verification tool to ensure the extension correctly loads and handles file operations on Linux.

## Why it's done this way
- **Cross-Platform Macros**: Added `RV_EXTENSION_EXPORT` to handle library symbol exports correctly on both Windows and Linux.
- **Path Compatibility**: Implemented automatic backslash (`\`) to forward slash (`/`) conversion in the file-opening logic, as Linux filesystems do not support Windows-style paths commonly passed by Arma 3 SQF.
- **Security**: Replaced `sprintf` with `snprintf` to prevent buffer overflows and ensure memory safety.

## How to use
1. Run `make all` in this directory.
2. The compiled `.so` files will be placed in the `ext/` subdirectory.
3. Place the appropriate `.so` file in the root of your Arma 3 mod folder (e.g., `@TacviewRecorder/`).
4. Set the `TVR_outputPath` CBA setting on your server to a valid POSIX-friendly path (e.g., `tacview_logs`).
