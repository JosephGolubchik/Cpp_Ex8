#include "Board.h"

#include <iostream>
#include <string>
using namespace std;

int main() {
// 	Board board;
// 	cin >> board;
// 	string filename = board.draw(600);
// 	cout << filename << endl;

    Board board1{3};  // Initializes a 3x3 board
    
	board1[{1,1}]='X';
	board1[{1,2}]='O';
	board1[{2,2}]='O';
	board1[{0,2}]='X';
	
	board1.draw(300);
	/* Shows the following board:
	
	. . X 
	. X O 
	. . O 
	
	*/

}