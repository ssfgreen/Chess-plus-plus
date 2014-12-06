#ifndef PAWN_H
#define PAWN_H

class ChessPiece;
class ChessBoard;

class Pawn: public ChessPiece {

private:



public:
	// constructor & deconstructor
  Pawn(Colour _colour);
  ~Pawn();
  // prints the pawn symbol
  virtual void printSymbol();
  // returns if the move is valid or not
  virtual bool validateMove(int source, int destination, ChessBoard* board);
};

#endif
