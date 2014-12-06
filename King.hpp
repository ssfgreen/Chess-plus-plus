#ifndef KING_H
#define KING_H

class ChessPiece;
class ChessBoard;

class King: public ChessPiece {

private:

public:
	// constructor and deconstructor 
  King(Colour _colour);
  ~King();
  // prints the symbol of a king
  virtual void printSymbol();
  // validates the moves a king can make
  virtual bool validateMove(int source, int destination, ChessBoard* board);

};

#endif
