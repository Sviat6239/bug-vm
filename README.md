# dummyVM

A small experimental virtual machine written in C.

## Overview
This project currently contains a minimal VM skeleton in [bugvm.c](bugvm.c). It reads a bytecode input file named [bytecode001.bin](bytecode001.bin) and is intended to grow into a simple interpreter for a small instruction set.

## Files
- [bugvm.c](bugvm.c) - Main source file for the VM
- [bytecode001.bin](bytecode001.bin) - Sample bytecode input file

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
