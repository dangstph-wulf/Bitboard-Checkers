#include <stdio.h>
#include "function.h"

int main() {
    unsigned int redPieces = 0x00000FFF;     // Initial positions for red pieces
    unsigned int blackPieces = 0xFFF00000;   // Initial positions for black pieces
    unsigned int kings = 0;                  // No kings at the start

    int turn = 0;                            // Turn counter (0=Red, 1=Black)
    char from[3], to[3];                     // Input buffers for moves

    printf("\nWelcome to Bitboard Checkers!\n");
    printf("Use coordinates like b6 c5 to move.\n");
    printf("Type Ctrl+C to quit.\n\n");

    while (1) {
        PrintBoard(redPieces, blackPieces, kings);                       // Displays the current board state
        printf("%s's turn. Enter move: ", turn == 0 ? "Red" : "Black");

        if (scanf("%2s %2s", from, to) != 2) {                           // Checks for valid input
            printf("Invalid input. Try again.\n");
            while (getchar() != '\n');
            continue;
        }

        int fromIndex = CoordToIndex(from);                              // Converts 'from' coordinate to index
        int toIndex = CoordToIndex(to);                                  // Converts 'to' coordinate to index

        if (fromIndex == -1 || toIndex == -1) {                          // Checks for valid squares
            printf("Invalid square. Use dark squares like b6.\n");
            continue;
        }

        unsigned int *myPieces = (turn == 0) ? &redPieces : &blackPieces;         // Pointer to current player's pieces
        unsigned int *enemyPieces = (turn == 0) ? &blackPieces : &redPieces;      // Pointer to opponent's pieces

        if (!GetBit(*myPieces, fromIndex)) {                      // Checks there is a piece at 'from' square
            printf("No piece at %s!\n", from);
            continue;
        }

        if (IsOccupied(redPieces, blackPieces, toIndex)) {        // Checks if 'to' square is unoccupied
            printf("That square is occupied.\n");
            continue;
        }

       int valid = IsValidMove(redPieces, blackPieces, kings, fromIndex, toIndex, turn);         // Checks the move if the move is valid
       if (valid == 0) {                                                                         
           printf("Invalid move from %s to %s (IsValidMove returned %d)\n", from, to, valid);
           continue;
       }

       if (valid == 2) {                                         // Handle captures
           int fromRow, fromCol, toRow, toCol;
           IndexToRowCol(fromIndex, &fromRow, &fromCol);
           IndexToRowCol(toIndex, &toRow, &toCol);
           int midRow = (fromRow + toRow) / 2;
           int midCol = (fromCol + toCol) / 2;
           int midIndex = (midRow * 4) + (midCol / 2);
           CapturePiece(enemyPieces, midIndex);

          char capSq[3] = {0};                                   // Prepares to print captured square
          int capRow, capCol;
          IndexToRowCol(midIndex, &capRow, &capCol);
          capSq[0] = 'a' + capCol;
          capSq[1] = '0' + (8 - capRow);
          printf("%s captured a piece at %s\n", (turn == 0) ? "Red" : "Black", capSq);
       }

       MovePiece(myPieces, fromIndex, toIndex);                 // Moves the pieces

       {
           int toRow, toCol;                                    // Checks for king promotion
           IndexToRowCol(toIndex, &toRow, &toCol);
           int alreadyKing = GetBit(kings, toIndex);
           if (!alreadyKing) {
               if ((turn == 0 && toRow == 0) || (turn == 1 && toRow == 7)) {
                   kings = ModifyBit(kings, toIndex, 1);
               }
           }
       }

      int oppHasPiece = 0;                                                                    // Checks for win conditions
      for (int i = 0; i < 32; ++i) {
          if (GetBit(*enemyPieces, i)) { oppHasPiece = 1; break; }
      }
      if (!oppHasPiece) {                                                                    // Opponent has no pieces left
          printf("%s wins! Opponent has no pieces remaining.\n", (turn == 0) ? "Red" : "Black");
          break;
      }

      if (!PlayerHasMoves(*enemyPieces, *myPieces, kings, 1 - turn)) {                       // Opponent has no legal moves
          printf("%s wins! Opponent has no legal moves.\n", (turn == 0) ? "Red" : "Black");
          break;
      }
       turn ^= 1;                                             // Switches turns
    }
}

