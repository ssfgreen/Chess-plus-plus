#ifndef ROOK_H
#define ROOK_H

class ChessPiece;
class ChessBoard;

class Rook: public ChessPiece {

private:

public:
	// constructor & deconstructor
  Rook(Colour _colour);
  ~Rook();
  // prints the Rook symbol
  virtual void printSymbol();
  // validates the Rooks moves
  virtual bool validateMove(int source, int destination, ChessBoard* board);	
  
};

#endif
