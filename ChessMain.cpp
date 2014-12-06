#include <iostream>
#include <fstream>

using namespace std;

#include "ChessBoard.hpp"

int main() {

    /*
    

    ofstream output;
    output.open("chessMoves.txt", ios::app);

    string first, second;

    cout << "Play the game" << endl;
    cout << "enter -1 to exit" << endl;

    cb.printBoard();

    output << endl << endl << "// ------ NEW GAME ------ //" << endl << endl;
    do {
      cb.printAllMoves();
      cb.printBoard();
    cout << "enter source: " << endl;
    cin >> first;
    cout << "enter destination: " << endl;
    cin >> second;
    cb.submitMove(first, second);
    if((first != "EE") && (second != "EE")) {
    output << "cb.submitMove(\"" + first + "\",\"" << second << "\");" << endl;
    }
    cb.printBoard();
    cout << endl;
    } while ((first != "EE") && (second != "EE"));

    output.close();
*/


    cout << "===========================" << endl;
    cout << "Testing the Chess Engine" << endl;

    cout << "===========================" << endl;
    cout << endl;

    ChessBoard cb;


    cb.printBoard();

    cout << endl;

    cb.submitMove("D7", "D6");
    cout << endl;

    cb.submitMove("D4", "H6");
    cout << endl;

    cb.submitMove("D2", "D4");
    cout << endl;

    cb.submitMove("F8", "B4");
    cout << endl;

    cout << "===========================" << endl;
    cout << "Alekhine vs. Vasic (1931)" << endl;
    cout << "===========================" << endl;
    cout << endl;

    cb.resetBoard();
    cb.printBoard();
    cout << endl;

    cb.submitMove("E2", "E4");
    //cb.printBoard();
    cb.submitMove("E7", "E6");
    //cb.printBoard();
    cout << endl;

    cb.submitMove("D2", "D4");
    //cb.printBoard();
    cb.submitMove("D7", "D5");
    //cb.printBoard();
    cout << endl;

    cb.submitMove("B1", "C3");
    //cb.printBoard();
    cb.submitMove("F8", "B4");
    //cb.printBoard();
    cout << endl;

    cb.submitMove("F1", "D3");
    //cb.printBoard();
    cb.submitMove("B4", "C3");
    //cb.printBoard();
    cout << endl;

    cb.submitMove("B2", "C3");
    //cb.printBoard();
    cb.submitMove("H7", "H6");
    //cb.printBoard();
    cout << endl;

    cb.submitMove("C1", "A3"); 
    //cb.printBoard();
    cb.submitMove("B8", "D7");
    //cb.printBoard();
    cout << endl;

    cb.submitMove("D1", "E2");
    //cb.printBoard();
    cb.submitMove("D5", "E4");
    //cb.printBoard();
    cout << endl;

    cb.submitMove("D3", "E4");
    //cb.printBoard();
    cb.submitMove("G8", "F6");
    //cb.printBoard();
    cout << endl;

    cb.submitMove("E4", "D3");
    //cb.printBoard();
    cb.submitMove("B7", "B6");
    //cb.printBoard();
    cout << endl;

    cb.submitMove("E2", "E6");
    //cb.printBoard();
    cb.submitMove("F7", "E6");
    //cb.printBoard();
    cout << endl;

    cb.submitMove("D3", "G6");
    cout << endl;
  
    cb.printBoard();

    return 0;
}
