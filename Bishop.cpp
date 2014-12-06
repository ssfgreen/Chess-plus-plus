#include "ChessPiece.hpp"
#include "ChessBoard.hpp"
#include "Bishop.hpp"
#include <iostream>

using namespace std;

Bishop::Bishop(Colour _colour):ChessPiece(_colour){
  type = "Bishop";
  Direction myDirections[] = {SW,SE,NW,NE};
    canMove.assign (myDirections, myDirections + sizeof(myDirections) / sizeof(Direction)); 
}
Bishop::~Bishop() {
}

bool Bishop::validateMove(int source, int destination, ChessBoard* board) {
  int checkValue = destination - source;
  // check horizontal movement
    for(vector<Direction>::iterator it = canMove.begin(); it != canMove.end(); ++it) {
    if ((checkValue % *it) == 0) {
      return true;
    }
  } 
    // or else
    return false;
}

void Bishop::printSymbol() {
  switch (colour) { 
  case WHITE:
    cout << "\u2657";
    break;
  case BLACK:
    cout << "\u265D";
    break;
  default:
    cout << "\u235F";
  }
}

