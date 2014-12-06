#ifndef BISHOP_H
#define BISHOP_H

class ChessPiece;
class ChessBoard;

class Bishop: public ChessPiece {

private:
 
public:
// constructor and deconstructor
  Bishop(Colour _colour);
  ~Bishop();
  // prints the bishop symbol
  virtual void printSymbol();
  // validates the moves in relation to chess rules
  virtual bool validateMove(int source, int destination, ChessBoard* board);
  
};

#endif
