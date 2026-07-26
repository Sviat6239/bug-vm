# dummyVM

An experimental stack-based virtual machine and bytecode interpreter written in C.

> **Current Version:** **0.4.0**

---

## Overview

dummyVM is a hobby project focused on building a simple virtual machine from scratch.

The project currently includes:

- a stack-based virtual machine;
- a text-based bytecode format;
- a tokenizer/parser for loading bytecode files;
- support for multiple runtime object types;
- labels and control flow;
- local variable storage;
- comparison flags and conditional branching.

The project is still under active development and serves as a playground for experimenting with compiler and VM design.

---

# Features

- Stack-based execution model
- Integer, floating-point and string values
- Arithmetic instructions
- Logical operations
- Comparison instructions
- Conditional and unconditional jumps
- Labels
- Local variable storage
- Input / output instructions
- String manipulation
- Simple text-based bytecode format

---

# Project Structure

```
dummyVM/
│
├── bugvm.c          Virtual machine implementation
├── bugc.c           Experimental parser / compiler prototype
├── bytecode.bbin    Sample bytecode program
└── README.md
```

---

# Instruction Set Architecture (ISA)

The VM executes hexadecimal 16-bit opcodes stored inside a text bytecode file.

Current instruction groups include:

## Stack

| Opcode | Mnemonic | Description |
|--------:|----------|-------------|
| `0x0001` | OP_PUSH | Push generic value |
| `0x0002` | OP_PUSH_INT | Push integer |
| `0x0003` | OP_PUSH_STR | Push string |
| `0x0004` | OP_PUSH_FLOAT | Push floating-point value |
| `0x0005` | OP_POP | Remove top stack value |

---

## Arithmetic

| Opcode | Mnemonic |
|--------:|----------|
| `0x0006` | OP_ADD |
| `0x0007` | OP_SUB |
| `0x0008` | OP_MUL |
| `0x0009` | OP_DIV |

Supports arithmetic on numeric types and string concatenation where applicable.

---

## Input / Output

| Opcode | Mnemonic |
|--------:|----------|
| `0x000A` | OP_PRINT |
| `0x000B` | OP_INPUT |

---

## Variables

| Opcode | Mnemonic |
|--------:|----------|
| `0x000C` | OP_STORE |
| `0x000D` | OP_LOAD |

Local variables are stored in an internal local storage array.

---

## Comparison

| Opcode | Mnemonic |
|--------:|----------|
| `0x000E` | OP_CMP |

Comparison sets internal VM flags used by conditional jumps.

---

## Branching

| Opcode | Mnemonic |
|--------:|----------|
| `0x000F` | OP_JMP |
| `0x0010` | OP_JNZ |
| `0x0011` | OP_JZ |
| `0x0012` | OP_JNE |
| `0x0013` | OP_JE |
| `0x0014` | OP_JGE |
| `0x0015` | OP_JG |
| `0x0016` | OP_JLE |
| `0x0017` | OP_JL |

---

## Logic

| Opcode | Mnemonic |
|--------:|----------|
| `0x0018` | OP_AND |
| `0x0019` | OP_OR |
| `0x001A` | OP_NOT |

---

## Functions

| Opcode | Mnemonic |
|--------:|----------|
| `0x001B` | OP_CALL |
| `0x001C` | OP_RET |

Currently reserved for future implementation.

---

## String Operations

| Opcode | Mnemonic |
|--------:|----------|
| `0x001D` | OP_STRLEN |
| `0x001E` | OP_STRCMP |

---

## Labels

| Opcode | Mnemonic |
|--------:|----------|
| `0x001F` | OP_LABEL |

---

## Debug Instructions

| Opcode | Mnemonic |
|--------:|----------|
| `0x0020` | OP_PRT_STACK |
| `0x0021` | OP_PRT_ALL_STACK |
| `0x0022` | OP_PRT_LOCAL |
| `0x0023` | OP_PRT_ALL_LOCAL |

---

## Program Control

| Opcode | Mnemonic |
|--------:|----------|
| `0xFFFF` | OP_HALT |

Stops VM execution.

---

# Example Bytecode

```text
0x0002 54
0x0002 47
0x0006
0x000A
0xFFFF
```

Output:

```text
101
```

---

# Build

Linux / macOS

```bash
gcc -std=c99 -O2 -Wall -Wextra bugvm.c -o bugvm
```

Windows (MinGW)

```bash
gcc -std=c99 -O2 -Wall -Wextra bugvm.c -o bugvm.exe
```

---

# Run

```bash
./bugvm
```

or

```bash
bugvm.exe
```

---

# Roadmap

Planned features include:

- Binary bytecode format
- Proper function calls
- Call stack
- Dynamic memory management
- Arrays
- Objects / structs
- Standard library
- Bytecode optimizer
- Garbage collector
- Native function interface

---

# License

This project is currently experimental and intended for educational purposes.