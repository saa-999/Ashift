# Contributing to Ashift

Welcome! We appreciate your interest in Ashift. Before you contribute, please review our permission model and guidelines.

## Permission Model

Ashift uses a strict read-only model for its core source code. The core C source is maintained solely by the author.

**Users are permitted to:**
*   Create new files and folders (e.g., documentation, examples, scripts).
*   Read all files to understand the documentation and development process.

**Users must NOT:**
*   Modify, edit, or tamper with the source code files (`main.c`, `shift.c`, `shift.h`, `Makefile`).

## Welcome Contributions

We welcome contributions in the following areas:
*   Documentation improvements
*   Usage examples
*   Bug reports
*   Feature requests

Pull requests that modify the core source code (`main.c`, `shift.c`, `shift.h`, `Makefile`) will **not** be accepted.

## How to Contribute

### Filing Issues
To report a bug or request a feature, please file an issue on [GitHub Issues](https://github.com/saa-999/Ashift/issues).

### Submitting Documentation PRs
To submit documentation or example improvements:
1.  Fork the repository.
2.  Create a new branch for your changes.
3.  Make your additions (remember, do not modify core source files).
4.  Submit a Pull Request.

## Documentation Style Guide
*   Write in direct, plain English.
*   Avoid filler words.
*   Keep sentences concise.
*   The project name is always capitalized as **Ashift**.

## Building Locally

You may need to build the project locally to test and verify your documentation or examples.

**Prerequisites:**
*   GCC (or compatible C11 compiler)
*   GNU Make
*   For Windows cross-compilation: `x86_64-w64-mingw32-gcc`

**Build Commands:**
*   `make` — build for Linux/Mac
*   `make windows` — cross-compile for Windows
*   `make clean` — remove build artifacts
