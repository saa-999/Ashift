# Ashift Workflow

This guide details the development workflow, build processes, and contribution policies for Ashift.

## Building Ashift

The project uses `make` as its build system. Run these commands from the project root:

- **Native Build (Linux/macOS)**: 
  ```bash
  make
  ```
  Produces the `ashift` executable.

- **Windows Cross-Compilation**: 
  ```bash
  make windows
  ```
  Requires `x86_64-w64-mingw32-gcc`. Produces `ashift.exe`.

- **Clean Build Artifacts**: 
  ```bash
  make clean
  ```
  Removes compiled binaries and object files.

## Source Organization

The repository is structured as follows:
- `/` - Root directory containing the `Makefile` and core source files (`main.c`, `shift.c`, `shift.h`).
- `/docs/` - Documentation directory (where this file resides).

## Contribution Policy

External contributions follow strict guidelines:
- **Source Code**: The source code is read-only for external contributors. Pull requests modifying C source files or headers will not be accepted.
- **Documentation**: We welcome documentation improvements. Submit pull requests to modify files in the `/docs/` directory.
- **Issues**: If you find bugs in the code or want to propose features, open an issue on the GitHub repository rather than submitting a code PR.

## Release Process

The release cycle involves the following steps:
1. Tag the release commit (e.g., `git tag v1.1.0`).
2. Build native Linux/macOS and Windows binaries using the `Makefile`.
3. Create a GitHub release from the tag, attaching the compiled binaries.

## Version History

- **v1.1.0**: Introduced the recursive descent parser, support for compound expressions, and the bitwise NOT operation.
- **v1.0.0**: Initial release featuring basic bitwise operations and literal parsing.
