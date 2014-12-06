#include <iostream>
#include "ChessPiece.hpp"
#include "ChessBoard.hpp"
#include "King.hpp"
// for bitwise and
// #include <ciso646>

using namespace std;

King::King(Colour _colour):ChessPiece(_colour){
  type = "King";
  Direction myDirections[] = {NW,N,NE,E,SE,S,SW,W};
    canMove.assign (myDirections, myDirections + sizeof(myDirections) / sizeof(Direction)); 
}
King::~King() {
  
}

bool King::validateMove(int source, int destination, ChessBoard* board) {
  int checkValue = destination - source;
// check specific possible moves
  for(vector<Direction>::iterator it = canMove.begin(); it != canMove.end(); ++it) {
    if (checkValue == *it) {
      return true;
    }
  } 
  // if not valid
    return false;
}

void King::printSymbol() {
  switch (colour) { 
  case WHITE:
    cout << "\u2654";
    break;
  case BLACK:
    cout << "\u265A";
    break;
  default:
    cout << "\u235F";
  }
}
