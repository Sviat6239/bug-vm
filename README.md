# dummyVM

A small experimental stack-based virtual machine and parser playground written in C.

**Version:** 0.1.1

## Overview
This repository currently contains two experimental C programs:

- `bugvm.c` reads `bytecode001.bbin`, strips comments, tokenizes each line, and executes a small opcode set on an internal stack.
- `bugc.c` is an early parser/code-generation experiment that reads `code.bg` and prints the tokenized lines.

## Instruction Set Architecture (ISA)
The VM operates on 16-bit opcodes read from hex text and uses a stack with `1024 * 1024` slots.

| Opcode | Mnemonic | Description |
| :--- | :--- | :--- |
| `0x0001` | **OP_PUSH** | Pushes a numeric value onto the stack. |
| `0x0002` | **OP_PUSH_STR** | Pushes a string token onto the stack. |
| `0x0003` | **OP_POP** | Pops the top value off the stack. |
| `0x0004` | **OP_ADD** | Adds two integers or concatenates two strings. |
| `0x0005` | **OP_SUB** | Subtracts two integers or concatenates two strings in the current implementation. |
| `0x0006` | **OP_MUL** | Multiplies two integers or concatenates two strings in the current implementation. |
| `0x0007` | **OP_DIV** | Divides two integers and guards against zero. |
| `0x0008` | **OP_PRINT** | Prints the current top value of the stack without popping it. |
| `0x0009` | **OP_INPUT** | Reads a value from standard input and pushes it as an integer or string. |
| `0xffff` | **OP_HALT** | Successfully terminates program execution. |

## Files
- `bugvm.c` — Main VM source file containing the tokenizer, hex-parser, stack, and execution loop.
- `bugc.c` — Experimental parser/tokenizer prototype.
- `bytecode001.bbin` — Sample text-based bytecode input file for `bugvm.c`.

## Bytecode Example (`bytecode001.bbin`)
```text
0x0001 54    // Push 54 onto the stack
0x0001 47    // Push 47 onto the stack
0x0004       // Add them together (54 + 47)
0x0008       // Print the result (101)
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
The code is still experimental, so some instructions and error messages are rough around the edges.
