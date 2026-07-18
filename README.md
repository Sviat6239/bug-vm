# dummyVM

A small experimental stack-based virtual machine written in C.

**Version:** 0.1.0

## Overview
This project contains a minimal, lightweight Virtual Machine (VM) skeleton that reads text-based bytecode files containing hexadecimal opcodes, tokenizes them, and executes them using an internal stack environment. 

## Instruction Set Architecture (ISA)
The VM operates on a 16-bit opcode scale (interpreted from hex text) and utilizes a dedicated data stack ($1024 \times 64$ elements).

| Opcode | Mnemonic | Description |
| :--- | :--- | :--- |
| `0x0001` | **OP_PUSH** | Pushes a 32-bit integer argument onto the stack. |
| `0x0002` | **OP_POP** | Pops the top value off the stack. |
| `0x0003` | **OP_ADD** | Pops two values, adds them, and pushes the result. |
| `0x0004` | **OP_SUB** | Pops two values, subtracts the first from the second, pushes the result. |
| `0x0005` | **OP_MUL** | Pops two values, multiplies them, and pushes the result. |
| `0x0006` | **OP_DIV** | Pops two values, divides the second by the first (guards against zero). |
| `0x0007` | **OP_PRINT**| Prints the current top value of the stack without popping it. |
| `0x0008` | **OP_INPUT**| Reads an integer from standard input and pushes it onto the stack. |
| `0xffff` | **OP_HALT** | Successfully terminates program execution. |

## Files
- `bugvm.c` — Main source file containing the tokenizer, hex-parser, and execution loop.
- `bytecode001.bbin` — Sample text-based bytecode input file.

## Bytecode Example (`bytecode001.bbin`)
```text
0x0001 54    // Push 54 onto the stack
0x0001 47    // Push 47 onto the stack
0x0003       // Add them together (54 + 47)
0x0007       // Print the result (101)
0xffff       // Halt
```

## Build
On Linux or macOS:

```sh
gcc -std=c99 -Wall -Wextra -o bugvm bugvm.c
```

On Windows with MinGW or MSVC, use the equivalent C compiler invocation.

## Run
```sh
./bugvm
```

## Notes
This project is still in an early stage, so the parser and execution logic are incomplete.
