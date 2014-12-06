#include "ChessPiece.hpp"
#include "ChessBoard.hpp"
#include "Knight.hpp"
#include <iostream>

using namespace std;

Knight::Knight(Colour _colour):ChessPiece(_colour) {
 type = "Knight";
 Direction myDirections[] = {KA,KB,KC,KD,KE,KF,KG,KH};
  canMove.assign (myDirections, myDirections + sizeof(myDirections) / sizeof(Direction)); 
}
Knight::~Knight() {
  
}

bool Knight::validateMove(int source, int destination, ChessBoard* board) {
  int checkValue = destination - source;
  // must be a neater way of doing this!!
  for(vector<Direction>::iterator it = canMove.begin(); it != canMove.end(); ++it) {
    if (checkValue == *it) {
      return true;
    }
  } 

  // if not equal to any of these values, return invalid
    return false;
  }

void Knight::printSymbol() {
  switch (colour) { 
  case WHITE:
    cout << "\u2658";
    break;
  case BLACK:
    cout << "\u265E";
    break;
  default:
    cout << "\u235F";
  }
}
