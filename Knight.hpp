#ifndef KNIGHT_H
#define KNIGHT_H

class ChessPiece;
class ChessBoard;

class Knight: public ChessPiece {

private:

public: 
	// constructor and deconstructor 
  Knight(Colour _colour);
  ~Knight();
  // prints a Knight symbol
  virtual void printSymbol();
  // validates the move of the Knight
  virtual bool validateMove(int source, int destination, ChessBoard* board);	
  
};

#endif
