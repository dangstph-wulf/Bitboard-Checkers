#include <stdio.h>
#include <stdlib.h>
#include "function.h"

void MovePiece(unsigned int *pieces, int from, int to) {           // Moves a piece from one position to another
    *pieces = ModifyBit(*pieces, from, 0);
    *pieces = ModifyBit(*pieces, to, 1); 
}

void CapturePiece(unsigned int *opponent, int pos) {              // Captures a piece at a specific position
    *opponent = ModifyBit(*opponent, pos, 0);
}

int IsOccupied(unsigned int red, unsigned int black, int pos) {   // Checks if a position is occupied by any piece
    return GetBit(red, pos) || GetBit(black, pos);
}

void IndexToRowCol(int index, int *row, int *col) {               // Converts a bitboard index to board row and column
    *row = index / 4;
    *col = (index % 4) * 2;
    if ((*row % 2) == 0) *col += 1;
}

int IsValidMove(unsigned int red, unsigned int black, unsigned int kings, int from, int to, int turn) { // Checks if a move from one position to another is valid
    if (IsOccupied(red, black, to)) return 0;
 
    int fromRow, fromCol, toRow, toCol;                   // Convert indices to row and column
    IndexToRowCol(from, &fromRow, &fromCol);
    IndexToRowCol(to, &toRow, &toCol);

    int dRow = toRow - fromRow;                         
    int dCol = toCol - fromCol;
    int adRow = abs(dRow), adCol = abs(dCol);

    if (adRow == 1 && adCol == 1) {                       // Simple move
        int isKing = GetBit(kings, from);
        if (!isKing) {
            if (turn == 0 && toRow >= fromRow) return 0; 
            if (turn == 1 && toRow <= fromRow) return 0;
        }
        return 1;
    }

    if (adRow == 2 && adCol == 2) {                      // Capture move
        int midRow = (fromRow + toRow) / 2;
        int midCol = (fromCol + toCol) / 2;
        int midIndex = (midRow * 4) + (midCol / 2);

        if (turn == 0) {                                
            if (!GetBit(black, midIndex)) return 0;
        } else { 
            if (!GetBit(red, midIndex)) return 0;
        }
        
        int isKing = GetBit(kings, from);               // Check for king status
        if (!isKing) {
            if (turn == 0 && toRow >= fromRow) return 0;
            if (turn == 1 && toRow <= fromRow) return 0;
        }
        return 2; 
    }

    return 0;
}

int HasCapture(unsigned int myPieces, unsigned int oppPieces, unsigned int kings, int turn) { // Checks if the current player has any possible captures
    for (int idx = 0; idx < 32; ++idx) {
        if (!GetBit(myPieces, idx)) continue;
        int fromRow, fromCol;
        IndexToRowCol(idx, &fromRow, &fromCol);
        int isKing = GetBit(kings, idx);

        const int drs[2] = { -2, 2 };                    
        const int dcs[2] = { -2, 2 };
        for (int ir = 0; ir < 2; ++ir) {
            for (int ic = 0; ic < 2; ++ic) {
                int toRow = fromRow + drs[ir];
                int toCol = fromCol + dcs[ic];
                if (toRow < 0 || toRow > 7 || toCol < 0 || toCol > 7) continue;
                if ((toRow + toCol) % 2 != 0) continue;
                int toIndex = (toRow * 4) + (toCol / 2);
                if (GetBit(myPieces, toIndex) || GetBit(oppPieces, toIndex)) continue;

                int midRow = (fromRow + toRow) / 2;            
                int midCol = (fromCol + toCol) / 2;
                int midIndex = (midRow * 4) + (midCol / 2);
                if (!GetBit(oppPieces, midIndex)) continue;

                if (!isKing) {
                    if (turn == 0 && toRow >= fromRow) continue; 
                    if (turn == 1 && toRow <= fromRow) continue;
                }

                return 1;
            }
        }
    }
    return 0;
}

int PlayerHasMoves(unsigned int pieces, unsigned int oppPieces, unsigned int kings, int turn) { // Checks if the current player has any valid moves
    for (int from = 0; from < 32; ++from) {
        if (!GetBit(pieces, from)) continue;
        for (int to = 0; to < 32; ++to) {
            if (from == to) continue;
            if (IsValidMove(pieces, oppPieces, kings, from, to, turn)) return 1;
        }
    }
    return 0;
}

void PrintBoard(unsigned int red, unsigned int black, unsigned int kings) {     // Prints the current state of the board
    printf("\n   a b c d e f g h\n");
    printf("  +-----------------+\n");

    for (int row = 8; row >= 1; row--) {
        printf("%d |", row);
        for (int col = 1; col <= 8; col++) {
            if ((row + col) % 2 != 0) {
                printf(" .");
            } else {
                int row0 = 8 - row;
                int col0 = col - 1;
                int index = (row0 * 4) + (col0 / 2);
                if (GetBit(red, index)) {
                    if (GetBit(kings, index)) printf("RK"); else printf(" R");
                } else if (GetBit(black, index)) {
                    if (GetBit(kings, index)) printf("BK"); else printf(" B");
                } else {
                    printf("  ");
                }
            }
        }
        printf(" |\n");
    }
    printf("  +-----------------+\n");
}