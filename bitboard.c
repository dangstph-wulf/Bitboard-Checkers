#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include "function.h"

static inline int IndexToBit(int index) {                                // Converts board index to bit position
    return 31 - index;
}

unsigned int ModifyBit(unsigned int num, int position, int operation) {        // Modifies a specific bit in the bitboard
    int b = IndexToBit(position);
    switch (operation){
    case 0: return num & ~(1U << b);                                           // Clear bit
    case 1: return num | (1U << b);                                            // Set bit
    case 2: return num ^ (1U << b);                                            // Toggle bit
    }
    return num;
}

int GetBit(unsigned int num, int position) {                            // Retrieves the value of a specific bit in the bitboard
    int b = IndexToBit(position);
    return (num >> b) & 1U;
}

int CountBits(unsigned int num) {                                      // Counts the number of set bits in the bitboard
    int count = 0;
    while (num) {
        count += num & 1;
        num >>= 1;
    }
    return count;
}

unsigned int ShiftLeft(unsigned int num, int positions) {              // Shifts the bitboard left by a specified number of positions
    return num << positions;
}

unsigned int ShiftRight(unsigned int num, int positions) {             // Shifts the bitboard right by a specified number of positions
    return num >> positions;
}

void PrintBinary(unsigned int num) {                                   // Prints the bitboard in binary format
    int bits = 32;
    for (int i = bits - 1; i >= 0; i--) {
        putchar((num & (1U << i)) ? '1' : '0');
        if (i % 4 == 0) putchar(' ');
    }
    putchar('\n');
}

int CoordToIndex(const char *coord) {                                  // Converts board coordinates (e.g., "b6") to bitboard index
    if (coord == NULL || strlen(coord) < 2) return -1;

    char file = tolower(coord[0]);
    char rank = coord[1];

    if (file < 'a' || file > 'h' || rank < '1' || rank > '8') return -1;

    int colNum = (file - 'a') + 1;  
    int rowNum = (rank - '0');      

    if ((rowNum + colNum) % 2 != 0) return -1;

    int row = 8 - rowNum;           
    int col = colNum - 1;           
    int index = (row * 4) + (col / 2);
    return index;
}
