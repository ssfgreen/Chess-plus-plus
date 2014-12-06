#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <string>
#include <vector>

class ChessBoard;

// sets the colours of each piece
enum Colour {NONE,BLACK,WHITE};
// sets the possible directions each can take
enum Direction {N = 16, NE = 17, E = 1, SE = -15, S = -16, 
    SW = -17, W = -1, NW = 15, DOUBLEN = 32, DOUBLES = -32,
    KA = 31, KB = -31, KC = 14, KD = -14, KE = 33, KF = -33,
    KG = 18, KH = -18};


class ChessPiece {

private:


protected:

  // **** INHERITED MEMBERS ****
  // ***************************

  // colour (player)	
  Colour colour;
  // representitive symbol for chess board printing
  char symbol;
  // stores the type of the piece
  std::string type;
  // stores the directions the piece can move
  std::vector<Direction> canMove;
  // positions on the chessboard(0x88) 
  int currentPosition;
  int previousPosition;
  // checks if the positions is on the board 
  bool checkBounds(int destination);  
  // returns the row the position is on
  int row(int position);

public:

  // **** INITIALISATION FUNCTIONS ****
  // **********************************

  // standard constructor
  ChessPiece(Colour colour);
  // standard deconstructor
  virtual ~ChessPiece();
  
  // **** MOVE VALIDATION ****
  // **********************************

  // validates the move for the ChessBoard (in relation to each piece)
  virtual bool validateMove(int source, int destination, ChessBoard* board);

  // **** GET/SET FUNCTIONS ****
  // ****************************

  // stores previous and current positions of each piece
  void storePositions(int source, int destination);
  // sets the position at the start
  void setPosition(int position);
  // gets the current position of a piece
  int getCurrentPosition();
  // gets the previous position of a piece
  int getPreviousPosition();
  // gets the colour of a piece as a string
  std::string getColour();
  // returns the colour of a peice as a Colour
  Colour returnColour();
  // gets the type of a piece
  virtual std::string getType();

  // **** PRINTING FUNCTIONS ****
  // ****************************

  // prints the symbol for the chess board
  virtual void printSymbol();

};

#endif
