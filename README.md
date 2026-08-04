### Shift tool 
* I designed this tool to help me with writing code.
* You can easily perform any operation you want—such as OR, XOR, AND, >>, or <<—on numbers or bits.

## Usage 

```
# this command does a shift 
Ashift ">> 24 u32 19216451"
```
* NOTE: Always enclose the operation and arguments in quotes (" ") to prevent the shell from intercepting operators like >> or <<.

```
# XOR command
Ashift "-x 0xFF u32 15461291"

# OR command
Ashift "-o 0xFF u32 15461291"

# AND command
Ashift "-n 0xFF u32 15461291"

```

# Type of variable

* Variables starting with 'u' are unsigned (positive only), and variables starting with 'i' are signed (can be positive or negative). 

* e.g.
```
Ashift ">> 24 u32 19216451"
# u32 means a 32-bit unsigned variable

Ashift "-n 0xFF i16 19216451"
```
*If you want to know more about how to use it, use a command 
```
Ashift -h 

```

## Tool interface
* The natural interface for using commands
```

[ Instruction 1 ]
Data Type   : u32
Mode        : [ OPERATION DETECTED: 2 ]
Value (Raw) : 15461291
Target Arg  : 255
Base Block  : [ 00000000 ] [ 11101011 ] [ 11101011 ] [ 10101011 ]
Direction   : Right (>>)
Orig Value  : 15461291
New Value   : 0
Result Block: [ 00000000 ] [ 00000000 ] [ 00000000 ] [ 00000000 ]

======================================================

```
* help interface
```

Options:
  -h, --help    Show this highly optimized help screen.

Operations:
  <<            Left Shift
  >>            Right Shift
  -n            Bitwise AND
  -o            Bitwise OR
  -x            Bitwise XOR

Data Types:
  u8, i8, u16, i16, u32, i32

Examples:
  shift "<< 2 u32 100"   Left shift 100 by 2 as a u32.
  shift ">> 3 i8 100"    Right shift 100 by 3 as an i8.
======================================================
```

## Makefile
* To build the tool
```
make

# windows

make windows

# clean
make clean

# I know it's very basic :)
```


## About tool

* Some might consider the idea naive, but I designed this tool to serve my own specific needs. I decided to share it because someone else might be looking for the exact same thing. If the tool doesn't appeal to you, feel free to modify it—or just throw it in the trash(:



* I used AI to speed up the tool's development after all, who wants to spend a busy day building a tool like this from scratch? However, I reviewed the code myself, and AI wrote 40% of it. My apologies to the LLM haters.

* I am not competing with other tools like qalc or bc; in fact, I rely on them myself. I designed shift to be faster and easier to use for repetitive tasks. While it is true that the Python interpreter performs the same function as my tool, consider the effort involved if you were to keep typing out commands like python -c "print(bin(192 << 24))". It is a somewhat slow process. 
