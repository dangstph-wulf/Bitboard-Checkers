#ifndef CONVERT_H
#define CONVERT_H

unsigned int ModifyBit(unsigned int num, int position, int operation);

int GetBit(unsigned int num, int position);

int CountBits(unsigned int num);

unsigned int ShiftLeft(unsigned int num, int positions);

unsigned int ShiftRight(unsigned int num, int positions);

void PrintBinary(unsigned int num);

void PrintHex(unsigned int num);

void MovePiece(unsigned int *pieces, int from, int to);

void CapturePiece(unsigned int *opponent, int pos);

int IsOccupied(unsigned int red, unsigned int black, int pos);

void MovePiece(unsigned int *pieces, int from, int to);

void CapturePiece(unsigned int *opponent, int pos);

void IndexToRowCol(int index, int *row, int *col);

int IsValidMove(unsigned int red, unsigned int black, unsigned int kings, int from, int to, int turn);

void PrintBoard(unsigned int red, unsigned int black, unsigned int kings);

int HasCapture(unsigned int myPieces, unsigned int oppPieces, unsigned int kings, int turn);

int CoordToIndex(const char *coord);

int PlayerHasMoves(unsigned int pieces, unsigned int oppPieces, unsigned int kings, int turn);

#endif