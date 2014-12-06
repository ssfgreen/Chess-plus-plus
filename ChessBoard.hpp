#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "ChessPiece.hpp"
#include <string>
#include <map>
#include <list>


#define NOT_PLAYERS_MOVE -1
#define THERE_IS_NO_PIECE_AT_THIS_POSITION -2
#define INVALID_MOVE -3
#define NOT_VALID_ROUTE -4
#define NOT_VALID_PIECE_MOVE -5
#define INCORRECT_PAWN_DIRECTION -6
#define KING_IN_CHECK -7
#define INVALID_INPUT -8


class ChessBoard {
  
private:

  // **** MEMBERS ****
  // *****************

  // the array holds the chess board
  ChessPiece* Board[128];
  // counter to know whose turn it is (odd/even == W/B)
  static int counter;
  // a counter for 50 move stalemate
  static int moveCounter;
  // stores pointers to pieces in each team
  ChessPiece* Whites[16];
  ChessPiece* Blacks[16];
  // all moves possible for a certain position
  std::vector<int> allMoves;

  
  // **** MOVING AND VALIDATION ****
  // *******************************

  // checks against the board if the players are in check
  bool inCheck(int source, int destination, int king, ChessPiece** pieces);
  // checks if a piece is in checkmate
  bool inCheckMate(int source, int destination, ChessPiece** attacker, ChessPiece** defender);
  // stalemate checks if there are any valid moves left to make
  bool staleMate(int source, int destination, ChessPiece** attacker, ChessPiece** defender);
  // checking that the move is valid
  bool validMove(int source, int destination);
  // checks to see if the route is correct without interruptions
  bool checkRoute(int source, int destination);
  // checks to see if there are other pieces in the way
  bool occupiedRoute(int source,int destination,int coordChange);
  // Move piece
  void movePiece(int source, int destination, ChessPiece** defender);  
  // performs a dummy move (needed for checking check)
  void dummyMovePiece(int source, int destination);
  // undoes the previous dummy move
  void undoDummyMove(int source, int destination, ChessPiece* temp);
 
  // **** HELPERS ****
  // *****************

  // converting the input string location to an array square value
  int convertString(std::string square);
  // returning the player whose turn it is
  Colour whoseTurn();
  // check correct player turn
  bool validPlayer(int square);
  // check a square colour
  Colour squareColour(int position);
  // find the incremental step for each move to destination
  int coordchange(int checkValid);
  // checks to see if the destination is on the board
  bool inBounds(int destination);
  // finds the opposite colour of the current position
  Colour oppositeColour(int position);
  // returns the opposite colour as a string
  std::string oppositeColourStr(int position);
  // finds the position of the king given the list of pieces
  int findKingPosition(ChessPiece** pieces);
  // the counter for a 50 move stalemate
  void updateStalemateCounter(int source, int destination);
  // finds all the moves possible for a player
  void allMovesPos(int position);
  // performs the majority of error printing
  void printError(int code);


public:

  // **** CHESS BOARD CREATION/RESETTING/MOVE ****
  // ****************************************

  // Board Constructor
  ChessBoard();
  // Board deconstructor
  ~ChessBoard();
  // fills the board
  void fillBoard();
  // Resetting the board  
  void resetBoard();
  // Submitting move to the board
  void submitMove(std::string source_square, std::string destination_square);
  // check if a square is occupied
  bool squareOccupied(int position);
  
  // **** PRINTING FUNCTIONS ****
  // ****************************

  // prints a list of all the moves possible on the board
  void printAllMoves();
  // prints the list of black and white pieces
  void printLists();
  // Printing the chess board
  void printBoard();
 
};

#endif
