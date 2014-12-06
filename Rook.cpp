#include "ChessPiece.hpp"
#include "ChessBoard.hpp"
#include "Rook.hpp"
#include <iostream>

using namespace std;

Rook::Rook(Colour _colour):ChessPiece(_colour) {
  type = "Rook";
  Direction myDirections[] = {N,S};
  canMove.assign (myDirections, myDirections + sizeof(myDirections) / sizeof(Direction)); 
}
Rook::~Rook() {
}

bool Rook::validateMove(int source, int destination, ChessBoard* board) {
  // initialise checkvalue
    int checkValue = destination - source;
  // first check horizontal movement
       if ((checkValue < 8) && (checkValue > -8)) {
      return true;
    }
  // then check remainder
  for(vector<Direction>::iterator it = canMove.begin(); it != canMove.end(); ++it) {
    if ((checkValue % *it) == 0) {
      return true;
    }
  } 

  return false;
}

void Rook::printSymbol() {
  switch (colour) { 
  case WHITE:
    cout << "\u2656";
    break;
  case BLACK:
    cout << "\u265C";
    break;
  default:
    cout << "\u235F";
  }
}
