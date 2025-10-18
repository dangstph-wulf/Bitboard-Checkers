
# CS 3503 Project 1 - Bitboard Checkers Game

## Author
[Stephen Dang]

## Description
My personal implementation of a bitboard checkers game written in C using a 32-bit bitboard to represent the dark squares on the board. Requires 2 players to input their moves directly using column-row coordinates. 

### Features
- Bitboard representation for red/black pieces and kings
- Column-row coordinate input (e.g. `a3 b4`)
- Simple move and single-capture validations
- King promotions when reaching opposing side of the board
- Win detection (no remaining pieces or legal moves)
- Console board display with king markers

### How To Play
- Red will always go first
- When prompted by the console, input 2 coordinates separated by a space (e.g. `a3 b4`), they represent the `from` and `to` parameters respectively (the coordinates MUST be lowercase)
- Catpures and promotions are printed in the console
- Normal Checkers rules apply

## Build Instructions

### Prerequisites
- gcc (MinGW or MSYS2) on Windows or any other C compiler
- gnu Make (or `mingw32-make`) if using the Makefile

### Files
- `main.c` - program entry, game loop, input handling
- `bitboard.c` - bit manipulations
- `game.c` - game functions, move/capture validations, printing board display
- `function.h` - prototype functions
- `Makefile` - build rules (MSYS2/MinGW/gnu Make)

### Build & Run
Using Make (MSYS2 MinGW64 shell recommended):
```bash
cd /c/C\ Projects/Project\ 1
make                            #build
make Run                        #run via Makefile
```

## Notes
This was my first large scale project that I have done with C in Visual Studio Code as well as my first functioning "game". Learning how to implement the different game functions such as capturing and promoting was difficult, but it was also a valuable learning experience in, not just that, but also bitboard representation and manipulation.

