# Ashift

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Release](https://img.shields.io/github/v/release/saa-999/Ashift)](https://github.com/saa-999/Ashift/releases)

A fast CLI tool for performing bitwise operations, shifts, and mathematical expressions on typed integers.

## Table of Contents
- [Background](#background)
- [Install](#install)
- [Usage](#usage)
- [Data Types](#data-types)
- [Contributing](#contributing)
- [License](#license)

## Background

I built Ashift for my own workflow because I needed a fast way to handle repetitive bitwise operations and shifts while visualizing the binary blocks. It is not designed to replace general-purpose calculators like `qalc` or `bc`, but rather to be a quick, focused tool for typed integer math. About 40% of the code was generated with AI assistance. It does exactly what I need, and I'm sharing it in case others find it useful.

## Install

### Download Pre-compiled Binaries (v1.1.0)

**Linux & macOS:**
```bash
sudo curl -L -o /usr/local/bin/Ashift https://github.com/saa-999/Ashift/releases/download/v1.1.0/Ashift
sudo chmod +x /usr/local/bin/Ashift
```

**Windows (PowerShell):**
```powershell
Invoke-WebRequest -Uri "https://github.com/saa-999/Ashift/releases/download/v1.1.0/Ashift.exe" -OutFile "C:\Tools\Ashift.exe"
# Remember to add C:\Tools to your PATH
```

You can also download manually from the [Releases page](https://github.com/saa-999/Ashift/releases).

### Build from Source

Ashift is written in C11 and optimized for performance.

```bash
git clone https://github.com/saa-999/Ashift.git
cd Ashift
```

**Build for Linux/macOS:**
```bash
make
```

**Cross-compile for Windows (requires mingw-w64):**
```bash
make windows
```

To clean build artifacts:
```bash
make clean
```

## Usage

Ashift requires arguments to be passed as a single quoted string to prevent your shell from interpreting characters like `<<`, `>>`, or `&`. 

**Basic syntax:** `Ashift "[op] [arg] <type> <value>"` or `Ashift "<type> <expression>"`

### Examples

```bash
# Shift operations
Ashift "<< 2 u32 100"          # Left shift 100 by 2 as u32
Ashift ">> 3 i8 100"           # Right shift 100 by 3 as i8

# Bitwise operations (Hex input supported)
Ashift "-x 0xFF u32 15461291"  # XOR
Ashift "-o 0xFF u32 15461291"  # OR
Ashift "-n 0xFF u32 15461291"  # AND

# Expressions (v1.1.0+)
Ashift "~ u32 (10+20)"         # Bitwise NOT with compound expression
Ashift " i32 ((4094 + 16 - 1) & ~(16 - 1))"  # Memory alignment math

# Help
Ashift -h
```

### Multi-instruction Chaining
You can chain multiple instructions using `&` as a separator within the quotes.

## Data Types

Ashift supports the following explicit data types:

| Type | Description |
|---|---|
| `u8` | Unsigned 8-bit integer |
| `i8` | Signed 8-bit integer |
| `u16` | Unsigned 16-bit integer |
| `i16` | Signed 16-bit integer |
| `u32` | Unsigned 32-bit integer |
| `i32` | Signed 32-bit integer |

## Contributing
See [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines on how to contribute.

## License
Ashift is licensed under the [MIT License](LICENSE). Copyright (c) 2026 srdv.
