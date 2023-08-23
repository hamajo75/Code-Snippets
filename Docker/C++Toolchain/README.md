# Using a Docker container including a toolchain

## Requirements

- Contain build tools.
- Pull a github repository.
  - Alternative: checkout before building the image and add the repository folder.
- Build & run analysis tools: cpplint, cppcheck, clang-tidy, clang-format, valgrind, gcovr, etc.