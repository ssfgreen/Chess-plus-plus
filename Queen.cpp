#include "ChessPiece.hpp"
#include "ChessBoard.hpp"
#include "Queen.hpp"
#include <iostream>

using namespace std;

Queen::Queen(Colour _colour):ChessPiece(_colour){
  type = "Queen";
  Direction myDirections[] = {NW,N,NE,SE,S,SW};
  canMove.assign (myDirections, myDirections + sizeof(myDirections) / sizeof(Direction)); 
}
Queen::~Queen() {
  
}

bool Queen::validateMove(int source, int destination, ChessBoard* board) {
  // initialise checking value
  int checkValue = destination - source;
  // first check horizontal movement
    if ((checkValue < 8) && (checkValue > -8)) {
      return true;
    }
  // then check the rest
  for(vector<Direction>::iterator it = canMove.begin(); it != canMove.end(); ++it) {
    if ((checkValue % *it) == 0) {
      return true;
    }
  }  
  // if none of the above holds - invalid move  
    return false;
}


void Queen::printSymbol() {

  switch (colour) { 
  case WHITE:
    cout << "\u2655";
    break;
  case BLACK:
    cout << "\u265B";
    break;
  default:
    cout << "\u235F";
  }
}
