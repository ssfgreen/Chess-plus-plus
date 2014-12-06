#ifndef QUEEN_H
#define QUEEN_H

class ChessPiece;
class ChessBoard;

class Queen: public ChessPiece {

private:

public:
	// constructor and deconstructor
  Queen(Colour _colour);
  ~Queen();
  // prints the Queen symbol
  virtual void printSymbol();
  // validates the queens moves
  virtual bool validateMove(int source, int destination, ChessBoard* board);
  
};

#endif
