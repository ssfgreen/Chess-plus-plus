#include "ChessPiece.hpp"
#include "ChessBoard.hpp"
#include "Pawn.hpp"
#include <iostream>
#include <vector>

using namespace std;

Pawn::Pawn (Colour _colour):ChessPiece(_colour){
  type = "Pawn";

  // initialise with possible moves.
  if (colour == WHITE) {
    Direction myDirections[] = {N,NW,NE};
    canMove.assign (myDirections, myDirections + sizeof(myDirections) / sizeof(Direction)); 
 }
  if (colour == BLACK) {
    Direction myDirections[] = {S,SW,SE};
    canMove.assign (myDirections, myDirections + sizeof(myDirections) / sizeof(Direction));
  }
}
Pawn::~Pawn() {
  
}


bool Pawn::validateMove(int source, int destination, ChessBoard* board) {
  
  // check initial move
  int checkValue = destination - source;

  // check for forward capturing
  if (board->squareOccupied(destination)) {
    if((checkValue == N) || (checkValue == S) ||
       (checkValue == DOUBLEN) || (checkValue == DOUBLES)) {
      return false;
    }
  }

  // check for diagonal moving
  if (!board->squareOccupied(destination)) {
    if ((checkValue == NW) || (checkValue == NE) ||
       (checkValue == SW) || (checkValue == SE)) {
      return false;
    }
  }

  //check against the double push
  if ((row(source)==2) && (colour == WHITE)){
    if ((checkValue == N) || (checkValue == DOUBLEN)) {
      return true;
    }
  }
  
  if ((row(source)==7) && (colour == BLACK)) {
    if ((checkValue == S) || (checkValue == DOUBLES)) {
      return true;
    } 
  }
  
  // check against other specific position moves
  for(vector<Direction>::iterator it = canMove.begin(); it != canMove.end(); ++it) {
    if (checkValue == *it) {
      return true;
    }
  } 

  // if none of the valid moves hold - return false 
   return false;
}


// for print function
void Pawn::printSymbol() {
  switch (colour) { 
  case WHITE:
    cout << "\u2659";
    break;
  case BLACK:
    cout << "\u265F";
    break;
  default:
    cout << "\u235F";
  }
}
