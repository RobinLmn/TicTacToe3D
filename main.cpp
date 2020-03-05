#include "functions.cpp"
#include <array>
#include <iostream>


using namespace std;

int main(){

    greetAndInstruct();

    // Construct empty board
    char board [27];
    for (int i=0; i< (27); i++){
        board[i] = 'e';
    }
    
    // Do each round as long as no one won
    do {
        // 1) Player's turn 
        int input = takeUserMove(board);

        // Update board
        board[input-1] = 'X';
        displayBoard(board);
    
        // Check if he won
        if (checkIfWinner(board)){
            cout << "You won ! :)" << endl;
            exit(0);
        }

        // 2) Computer's turn
        computerMove(board);
        displayBoard(board);

        // Check if he won
        if (checkIfWinner(board)){
            cout << "You Lost :(" << endl;
            exit(0);
        }
        
    } while (!checkIfWinner(board));

    cout << "Thank you for playing our 3D Tic-Tac-Toe game !" << endl;

}