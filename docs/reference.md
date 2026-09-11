# Ashift Reference

## Operations

| Flag | Name | Syntax | Example |
| --- | --- | --- | --- |
| `<<` | Left Shift | `<< <arg> <type> <value>` | `<< 2 u8 4` |
| `>>` | Right Shift | `>> <arg> <type> <value>` | `>> 1 u16 8` |
| `&` | Bitwise AND | `& <arg> <type> <value>` | `& 0x0F u32 0xFF` |
| `\|` | Bitwise OR | `\| <arg> <type> <value>` | `\| 0xF0 u8 0x0F` |
| `^` | Bitwise XOR | `^ <arg> <type> <value>` | `^ 0xFF u8 0xAA` |
| `~` | Bitwise NOT | `~ <type> <value>` | `~ u8 0x0F` |

*Note: Multiple instructions can be chained using the `&` separator (e.g., `<< 2 u8 4 & >> 1 u8 16`).*

## Data Types

| Name | Size | Range | Signedness |
| --- | --- | --- | --- |
| `u8` | 8-bit | 0 to 255 | Unsigned |
| `i8` | 8-bit | -128 to 127 | Signed |
| `u16` | 16-bit | 0 to 65,535 | Unsigned |
| `i16` | 16-bit | -32,768 to 32,767 | Signed |
| `u32` | 32-bit | 0 to 4,294,967,295 | Unsigned |
| `i32` | 32-bit | -2,147,483,648 to 2,147,483,647 | Signed |

## Command Syntax Grammar

The general syntax for a single instruction is:
`[op] [arg] <type> <value>`

- `[op]`: The operation flag (e.g., `<<`, `|`, `~`).
- `[arg]`: The argument for the operation. (Omitted for unary operations like `~`).
- `<type>`: The data type descriptor (e.g., `u8`, `i32`).
- `<value>`: The target value to operate on.

Both `[arg]` and `<value>` can be compound expressions.

## Expression Syntax

Compound expressions can be used in place of numeric literals for `[arg]` and `<value>`. The following operators are supported, ordered by precedence (highest to lowest):

1. `()`: Parentheses
2. `~`, `+`, `-`: Unary operations
3. `*`, `/`, `%`: Multiplication, division, modulo
4. `+`, `-`: Addition, subtraction
5. `<<`, `>>`: Bitwise shifts
6. `&`: Bitwise AND
7. `^`: Bitwise XOR
8. `|`: Bitwise OR

Numeric literals can be specified in decimal or hexadecimal (prefixed with `0x`).

## Exit Codes

- `0`: Success
- Non-zero: Error (e.g., invalid syntax, unknown type, parse failure)

## Output Format

The output presents the initial state, the operation applied, and the final state, accompanied by a binary visualization. 

Example representation:
- Target value displayed in decimal, hex, and binary.
- Applied operation and argument.
- Result displayed in decimal, hex, and binary.
