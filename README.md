# Cogsworth

A simple DirectX 8.0 application written in x86 assembly using Microsoft Assembler (MASM).

Current system time is depicted as Cogsworth, the character from [1991 Disney animated film Beauty and the Beast](https://en.wikipedia.org/wiki/Beauty_and_the_Beast_(1991_film)).

The main assembler code is in [src/Cogsworth.asm](src/Cogsworth.asm). A blueprint C++ version is also present in [src/cpp-blueprint/](src/cpp-blueprint/) folder.

## Building

To build both the assembly code and the C++ blueprint you can use the provided CMake scripts.

A recent version of Microsoft Visual C++ is required (tested with 2022). This project only works in 32-bit mode (x86).
