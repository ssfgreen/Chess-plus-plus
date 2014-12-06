#include <iostream>
#include <string>
#include <cstring>
#include <map>

#include "ChessBoard.hpp"
#include "ChessPiece.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Queen.hpp"
#include "King.hpp"
#include "Pawn.hpp"

using namespace std;

int ChessBoard::counter = 0;
int ChessBoard::moveCounter = 0;

// **** CHESS BOARD CREATION/RESETTING ****
// ****************************************


// setting out the initial chessboard (constructor)
ChessBoard::ChessBoard() {

  for(int i=0; i<128; i++) {
    Board[i] = NULL;
  }
  fillBoard();

}

ChessBoard::~ChessBoard() {

  for(int i =0; i<128; i++) {
    delete Board[i];
    Board[i] = NULL;
  }

}

void ChessBoard::fillBoard() {

  // set whites
  Board[0] = new Rook(WHITE);
  Board[1] = new Knight(WHITE);
  Board[2] = new Bishop(WHITE);
  Board[3] = new Queen(WHITE);
  Board[4] = new King(WHITE);
  Board[5] = new Bishop(WHITE);
  Board[6] = new Knight(WHITE);
  Board[7] = new Rook(WHITE); 

  for(int i=16; i<24; i++) {
    Board[i] = new Pawn(WHITE);
  }

  // set blacks
  Board[112] = new Rook(BLACK);
  Board[113] = new Knight(BLACK);
  Board[114] = new Bishop(BLACK);
  Board[115] = new Queen(BLACK);
  Board[116] = new King(BLACK);
  Board[117] = new Bishop(BLACK);
  Board[118] = new Knight(BLACK);
  Board[119] = new Rook(BLACK); 

  for(int i=96; i<104;i++) {
    Board[i] = new Pawn(BLACK);
  }


  // set arrays to hold onto the piece
  int a  = 0;
  for(int i=0; i<24; i++) {
    Whites[a] = Board[i];
    Board[i]->setPosition(i);
    if(i == 7) {
      i = 15;
    }
    a++;
  }

  int b = 0;
  for(int i=119; i >= 96; i--) {
    Blacks[b] = Board[i];
    Board[i]->setPosition(i);
    if(i==112) {
      i = 104;
    }
    b++;
  }

  cout << "A new chess game is started!" << endl;
}

// resetting the chess board
void ChessBoard::resetBoard() {
  // reset player move counter
  counter = 0;
  // delete former board
  for(int i=0;i<128;i++) {
    if(Board[i] != NULL) {
      delete Board[i];
      Board[i] = NULL;
    }
  }

  fillBoard();

}


// **** PRIMARY FUNCTIONS ****
// *******************************

void ChessBoard::submitMove(string source_square, string destination_square) {
  
  // convert strings to ints
  int source = convertString(source_square);
  int destination = convertString(destination_square);

  if((source == -1) || (destination == -1)){
    printError(INVALID_INPUT);
    return;
  }

  // find attacker and defender
  ChessPiece** attacker;
  ChessPiece** defender;
  string attackerColourStr;
  string defenderColourStr;

  if(Board[source] != NULL) {
    if(Board[source]->returnColour() == WHITE) {
    attacker = Whites;
    defender = Blacks;
    attackerColourStr = "White";
    defenderColourStr = "Black";
    } else if (Board[source]->returnColour() == BLACK) {
      attacker = Blacks;
      defender = Whites;
      attackerColourStr = "Black";
      defenderColourStr = "White";
    }
  }
  
  // check valid player move
  if(!validPlayer(source)) {
    return;
  }

  // check if the move is a valid move (exc. check etc) 
  if (!validMove(source,destination)) {
    cout << attackerColourStr << "'s " << Board[source]->getType() 
    << " cannot move to " << destination_square << endl;
    return;
  }
  // find the position & colour of the kings
  int kingPosition = findKingPosition(attacker);
  int opponentKing = findKingPosition(defender); 

  // If the king moves, need to move the king too
    if (inCheck(source,destination,kingPosition,defender)) {
      printError(INVALID_MOVE);
      printError(KING_IN_CHECK);
      return;
    }

  // print movement
  cout << attackerColourStr << "'s " << Board[source]->getType()
       << " moves from " << source_square << " to " << destination_square
       << " ";
  if (squareOccupied(destination)) {
    cout << "taking " << defenderColourStr << "'s " << Board[destination]->getType();
  } 
  if (inCheck(source, destination, opponentKing,attacker)) {
    cout << endl << defenderColourStr << " is in check";
  }
  if (inCheckMate(source, destination, attacker, defender)) {
    cout << "mate";
  }
  if (!inCheck(source, destination,opponentKing,attacker)) {
    if (staleMate(source, destination, attacker, defender)) {
      cout << endl << "the game has resulted in stalemate";
    }
  }
  cout << endl;

  // move player
  movePiece(source, destination, defender);

  // increment player counter
  counter++;
}


bool ChessBoard::inCheck(int source, int destination, int king, ChessPiece** pieces) {

// if the king is moving
  if(Board[source]->getType() == "King") {    // should be able to do this better?
    king = destination;
  }
  // perform dummy move
    ChessPiece* temp = Board[destination];
    dummyMovePiece(source, destination);

  for(int i=0; i<16;i++) {
    if(pieces[i] != NULL) {
      if(validMove(pieces[i]->getCurrentPosition(), king)) {
        undoDummyMove(source, destination, temp);
        return true;
      }
    }
  }

  undoDummyMove(source, destination, temp);
    
  return false;

}


bool ChessBoard::inCheckMate(int source, int destination, ChessPiece** attacker, ChessPiece** defender) {

  // ONE:: Can the king move out of check???

  int opponentKing = findKingPosition(defender); //findKing(oppositeColour(source));

  // find all possible moves the king can make, save as an array of ints
  allMovesPos(opponentKing);

  // check for each of these positions to see if that get's him out of check
  for(vector<int>::iterator it = allMoves.begin(); it != allMoves.end(); ++it) {
    if(!inCheck(source, destination, *it, defender)) { 
      return false;           
    }
  }

  // TWO:: Can your opponent move their pieces into a position that stops check?

  // perform dummy move
  ChessPiece* temp = Board[destination];
  dummyMovePiece(source, destination);

  // check for each defender if any moves can take them out of check 
  for(int i=0;i<16;i++) {  
    if((defender[i] != NULL) && (defender[i]->getType() != "King")) {
      allMovesPos(defender[i]->getCurrentPosition());
      for(unsigned int n = 0; n < allMoves.size(); n++) {
        if(!inCheck(defender[i]->getCurrentPosition(), allMoves[n], opponentKing, attacker)) {
          undoDummyMove(source, destination, temp);
          return false;
        }
      }
    }
  }

  // undo dummy move
  undoDummyMove(source, destination, temp);

  // or else
  return true;

}

bool ChessBoard::staleMate(int source, int destination, ChessPiece** attacker, ChessPiece** defender) {

  updateStalemateCounter(source, destination);  

  // checking for two conditions of check, but not board repeats three times
  if(!inCheckMate(source, destination, attacker, defender)) {
    return false;
  } else if (moveCounter < 50) {
    return false;
  } else {
    return true;
  }

}


// **** PRIMARY MOVES & VALIDATORS ****
// ************************************

bool ChessBoard::validMove(int source, int destination) {

  if(Board[source] == NULL) {
    return false;
  }

  // check if a valid move for that piece 
  bool validPieceMove = Board[source]->validateMove(source, destination, this);
  if(!validPieceMove) {
    // printError(NOT_VALID_PIECE_MOVE);
    return false;
  }

  // check valid route
  if(!checkRoute(source, destination)) {
    // printError(NOT_VALID_ROUTE);
    return false;
  }

  // if all OK
  return true;
}

bool ChessBoard::checkRoute(int source, int destination) {

  int checkValid = destination - source;
  int coordChange = coordchange(checkValid);

  // check if the route is blocked to the destination
  if (coordChange != -1) {
    if(occupiedRoute(source, destination, coordChange)) {
      return false;
    }
  }

  // check the destination for all (including knight)
  if (Board[destination] != NULL) {
    if (squareColour(destination) == squareColour(source)) {
      return false;
    }
    if (squareColour(destination) == oppositeColour(source)) {
      return true;
    }
  }

  return true;
}

bool ChessBoard::occupiedRoute(int source,int destination,int coordChange) {
  int checkValid = destination - source;

  if (checkValid > 0) {
    for(int position = source+coordChange; position < destination; position = position+coordChange) {
      if (position != destination) {
       if(squareOccupied(position)) {
         return true;
       } 
      } 
    }
  }
  else if (checkValid < 0) {
    for(int position = source-coordChange; position > destination; position = position-coordChange) {
      if(position != destination) {
       if(squareOccupied(position)) {
         return true;
       } 
      }
    } 
  }

  // if none of the above
  return false;

}

void ChessBoard::movePiece(int source, int destination, ChessPiece** defender) {

  if(Board[destination] != NULL) {    // i.e there is a piece here
    for(int i = 0; i<16; i++) {
      if(defender[i] != NULL) {
        if(defender[i] == Board[destination]){
          defender[i] = NULL;
          delete Board[destination];
          Board[destination] = Board[source];
          Board[source] = NULL;    // in Blacks, the piece is still linked
          Board[destination]->storePositions(source, destination);
        }
      }
    }
  }

  // moving a piece without capturing
  else { 
    Board[destination] = Board[source];
    Board[source] = NULL;
    Board[destination]->storePositions(source, destination);
  }
}

void ChessBoard::dummyMovePiece(int source, int destination) {

  if(Board[destination] != NULL) {    // i.e there is a piece here
    if(Board[destination]->returnColour() == WHITE) {
      for(int i = 0; i<16; i++) {
	     if(Whites[i] != NULL) {
	       if(Whites[i] == Board[destination]){
	         Whites[i] = NULL;
	         Board[destination] = Board[source];
	         Board[source] = NULL;    // in Blacks, the piece is still linked
	         Board[destination]->storePositions(source, destination);
	        } 
	      } 
      }
    }
    else if(Board[destination]->returnColour() == BLACK) {
      for(int i = 0; i<16; i++) {
      	if(Blacks[i] != NULL) {
      	  if(Blacks[i] == Board[destination]){
      	    Blacks[i] = NULL;
      	    Board[destination] = Board[source];
      	    Board[source] = NULL;    // in Blacks, the piece is still linked
      	    Board[destination]->storePositions(source, destination);
      	  }
      	}
      }
    }
  }

  // moving a piece without capturing
  else { 
    Board[destination] = Board[source];
    Board[source] = NULL;
    Board[destination]->storePositions(source, destination);
  }
}

void ChessBoard::undoDummyMove(int source, int destination, ChessPiece* temp) {

  Board[source] = Board[destination];
  Board[destination] = temp;
  Board[source]->storePositions(-1, source);

  if(Board[destination] != NULL) {
    if(Board[destination]->returnColour() == WHITE) {
      for(int i = 0; i<16; i++) {
	     if(Whites[i] == NULL) {
      	  Whites[i] = Board[destination];
      	  Board[destination]->storePositions(-1, destination);
      	  return;
      	}
      }
    }
    else if(Board[destination]->returnColour() == BLACK) {
      for(int i = 0; i<16; i++) {
      	if(Blacks[i] == NULL) {
      	  Blacks[i] = Board[destination];
      	  Board[destination]->storePositions(-1, destination);
      	  return;
      	}
      }
    }
  }
}


// **** HELPERS ****
// *****************

int ChessBoard::convertString(string square) {
  // check to ensure it's the correct length
  if(square.length() != 2) {
    return -1;
  }

  // do the conversion to rank & file
  char array[2];
  strcpy(array, square.c_str());

  char rank = array[0];
  char file = array[1];

  // ensure rank and file are correct possibilities
  if((rank < 'A') || (rank > 'H') || (file < '1') || (file > '8')) {
    return -1;
  }

  // convert to 0x88 board
  int conversion = 16*(file-49) + (rank-65);

  // check on the 0x88 board
  if(inBounds(conversion)) {
    return conversion;
  } else {
    return -1;
  }

}

Colour ChessBoard::whoseTurn() {
  if(counter%2 == 0) {
    return WHITE;
  }
  else
    return BLACK;
}

bool ChessBoard::validPlayer(int square) {
  if(Board[square] == NULL) {
    printError(THERE_IS_NO_PIECE_AT_THIS_POSITION);
    return false;
  }
  else if(whoseTurn() == Board[square]->returnColour()) {
    return true;
  }
  else {
    printError(NOT_PLAYERS_MOVE);
    return false;
  }
}

bool ChessBoard::squareOccupied(int position) {
  if(Board[position] == NULL) {
    return false;
  }
  else 
    return true;
}

Colour ChessBoard::squareColour(int position) {
  if(Board[position] != NULL) {
    return Board[position]->returnColour();
  }
  else 
    return NONE;
}

int ChessBoard::coordchange(int checkValid) {
  if (checkValid%NW == 0) { return NW; }
  if (checkValid%N == 0) { return N; }
  if (checkValid%NE == 0) { return NE; }
  if ((checkValid >= -7) && (checkValid <= 7)) { return E; } 
          // note: east, because west == -1
  else 
    return -1;
}

bool ChessBoard::inBounds(int destination) {
  if ((destination & 0x88) == 0) {
    return true;
  }
  else
    return false;
}

Colour ChessBoard::oppositeColour(int position) {
  Colour myColour = Board[position]->returnColour();

  switch (myColour) {
  case BLACK:
    return WHITE;
  case WHITE:
    return BLACK;
  default: 
    return WHITE;
  }
}

string ChessBoard::oppositeColourStr(int position) {
  Colour myColour = Board[position]->returnColour();

  switch (myColour) {
  case BLACK:
    return "White";
  case WHITE:
    return "Black";
  default: 
    return "None";
  }
}

int ChessBoard::findKingPosition(ChessPiece** pieces) {

  for(int i = 0; i<16;i++) {
    if (pieces[i] != NULL) {
      if(pieces[i]->getType() == "King") {
        return pieces[i]->getCurrentPosition();
      }
    }
  }
  return -1;
}

 void ChessBoard::updateStalemateCounter(int source, int destination){
    // represents a capture, so reset stalemate counter
  if(Board[destination] != NULL) {
    moveCounter = 0;
  }
  // if a pawn is moving, this resets the counter too.
  if(Board[source]->getType() == "Pawn"){
    moveCounter = 0;
  }
}


void ChessBoard::allMovesPos(int position) {

  allMoves.clear();

  for(int i = 0; i<127; i++) {
    if(!(i & 0x88)) { // !(position & 0x88) 
      if(validMove(position, i)) {
        allMoves.push_back(i); 
      }
    }
  }
}

// **** ERROR PRINTING ****
// ************************

void ChessBoard::printError(int code) {
  switch (code) {
  case NOT_PLAYERS_MOVE:
    cout << "It's not your move" << endl;
    break;
  case THERE_IS_NO_PIECE_AT_THIS_POSITION:
    cout << "There is no piece at this position." << endl;
    break;
  case INVALID_MOVE:
    cout << "This is an invalid move." << endl;
    break;
  case NOT_VALID_ROUTE:
    cout << "There is a piece in the way. Invalid route." << endl;
    break;
  case NOT_VALID_PIECE_MOVE:
    cout << "This piece cannot make this type of move." << endl;
    break;
  case INCORRECT_PAWN_DIRECTION:
    cout << "The pawn cannot move this way." << endl;
    break;
  case KING_IN_CHECK:
    cout << "You must not place your king in check." << endl;
    break;
  case INVALID_INPUT:
    cout << "Invalid move input" << endl;
    break;
  default:
    cout << "HUH?!";
  }
}

// **** PRINTING FUNCTIONS ****
// ****************************

void ChessBoard::printAllMoves() {
  cout << endl << "Blacks" << endl;
  for(int i = 0; i<16; i++) {
    if(Blacks[i] != NULL) {
      cout << Blacks[i]->getType() << "("
	   << Blacks[i]->getCurrentPosition() << ") : ";
      allMovesPos(Blacks[i]->getCurrentPosition());
      for(unsigned int i=0; i< allMoves.size(); i++) {
	cout << allMoves[i] << ", ";
      }
      cout << endl;
    }
    else {
      cout << "NULLER" << endl;
    }
  }
  cout << endl;

  cout << "Whites" << endl;
  for(int i = 0; i<16; i++) {
    if(Whites[i] != NULL) {
      cout << Whites[i]->getType() << "("
	   << Whites[i]->getCurrentPosition() << ") : ";
      allMovesPos(Whites[i]->getCurrentPosition());
      for(unsigned int i=0; i< allMoves.size(); i++) {
	cout << allMoves[i] << ", ";
      }
      cout << endl;
    }
    else {
      cout << "NULLER" << endl;
    }
  }
}


void ChessBoard::printLists() {
  cout << endl << "Blacks" << endl;
  for(int i = 0; i<16; i++) {
    if(Blacks[i] != NULL) {
      cout << Blacks[i]->getType() << ": "
	   << Blacks[i]->getCurrentPosition() << ": "
	   << endl;
    }
    else {
      cout << "NULLER" << endl;
    }
  }
  cout << endl;

  cout << "Whites" << endl;
  for(int i = 0; i<16; i++) {
    if(Whites[i] != NULL) {
      cout << Whites[i]->getType() << ": "
	   << Whites[i]->getCurrentPosition() << ": "
	   << endl;
    }
    else {
      cout << "NULLER" << endl;
    }
  }
}


void ChessBoard::printBoard() {
  // print header
  cout << "  ";
  for (char i='A'; i<='H';i++) {
    cout << " " << i << "  ";
  }
  cout << endl;

  // print top line
  cout << " \u250C";
  for(int i = 7; i >=1; i--){
    cout << "\u2500\u2500\u2500\u252C";
  }
  cout << "\u2500\u2500\u2500\u2510" << endl;

  // print row by row
  int square = 112;
  for(int row = 8; row>=1; row--) {
    cout << row << "\u2502";
    for (int i=square; i<square+8; i++) {
      if(Board[i] == NULL) {
	cout << "   \u2502";
      }
      else {
	cout << " ";
	Board[i]->printSymbol();
	cout << " ";
	cout << "\u2502";
      }
    }
    cout << endl;

    //print the grid lines
    if(row>1) {
      cout << " \u251C";
      for (int i=7;i>=1;i--) {
	cout << "\u2500\u2500\u2500\u253C";
      }
      cout << "\u2500\u2500\u2500\u2524" << endl;
    }
    square = square -16;
  }

  // print bottom
  cout << " \u2514";
  for (int i = 7; i>=1;i--) {
    cout << "\u2500\u2500\u2500\u2534";
  }
  cout << "\u2500\u2500\u2500\u2518" << endl;

}



