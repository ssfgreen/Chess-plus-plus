
#include <iostream>
#include "ChessPiece.hpp"
#include <string>
#include "ChessBoard.hpp"

using namespace std;

ChessPiece::ChessPiece(Colour _colour) {
  colour = _colour;
  symbol = 'x';
  type = "no type";
  currentPosition = -1;
  previousPosition = -1;

}
ChessPiece::~ChessPiece(){
}

int ChessPiece::row(int position) {

  if ((position & 0x88) == 0) {
    return ((position/16)+1);
      }
  else
    return -1;
}

bool ChessPiece::checkBounds(int destination) {
int bitwise0x88 = destination & 0x88;

if (bitwise0x88 == 0) {
  return true;
}
else
  return false;

}

string ChessPiece::getColour() {
  switch (colour) {
  case BLACK:
    return "Black";
    break;
  case WHITE:
    return "White";
    break;
  default:
    return "NONE";
  }
}

void ChessPiece::storePositions(int source, int destination) {
  currentPosition = destination;
  previousPosition = source;
}

void ChessPiece::printSymbol() { 
  cout << "NO SUBCLASS PRINT";
}

bool ChessPiece::validateMove(int source, int destination, ChessBoard* board) {
  return false; 
}

Colour ChessPiece::returnColour() {
  return colour;
}

string ChessPiece::getType() {
  return type;
}

int ChessPiece::getCurrentPosition() {
  return currentPosition;
}

int ChessPiece::getPreviousPosition() {
  return previousPosition;
}

void ChessPiece::setPosition(int position) {
  currentPosition = position;
}
