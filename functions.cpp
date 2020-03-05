#include <iostream>
using namespace std;

void greetAndInstruct(){

    string starts;

    // Display starting messages

    cout << "Hello and welcome to the Tic-Tac-Toe challenge: Player against Computer." << endl;
    cout << endl;
    cout << "The board is numbered from 1 to 27 as per the following:" << endl;
    cout << "1|2|3       10|11|12        19|20|21" << endl;
    cout << "-----       --------        --------" << endl;
    cout << "4|5|6       13|14|15        22|23|24" << endl;
    cout << "-----       --------        --------" << endl;
    cout << "7|8|9       16|17|18        25|26|27" << endl;
    cout << endl;
    cout << "Player starts first. Simply input the number of the cell you want to occupy." << endl;
    cout << "Player’s move is marked with X. Computer’s move is marked with O." << endl;
    cout << "Start? (y/n):" << endl;
    cin >> starts;

    // Check for user input, re-ask if incorrect input.
    while (starts != "n" && starts != "y"){
        cout << "Type 'y' if you want to play, 'n' if you want to quit. Input invalid. Please retry." << endl;
        cin >> starts;
    }
    if (starts == "n"){
        exit(0);
    }

}

// Returns the content of the cell of the board. If cell is empty ('e') it will return its number.
string cell(int i, char cellnum){
    // if the cell is empty, the cell will contain the character 'e'. Esle it will contain 'X' or 'O'. If empty, return its number.
    if (cellnum == 'e'){
        std::string num = std::to_string(i+1);
        return num;
    }
    else{
        string c(1, cellnum);
        return c;
    }
}


void displayBoard(char board[]){

    // Display each cells of the board in the correct format.

    cout << endl;
    cout << "///////////////////////////////////////////////////" << endl;
    cout << endl;
    cout << cell(0, board[0]) << "|" << cell(1, board[1]) << "|" << cell(2, board[2]) << "        ";
    cout << cell(9, board[9]) << "|" << cell(10, board[10])<< "|" << cell(11, board[11]) << "        ";
    cout << cell(18, board[18]) << "|" << cell(19, board[19])<< "|" << cell(20, board[20]) << endl;
    cout << endl;
    cout << cell(3,board[3]) << "|" << cell(4,board[4])<< "|" << cell(5,board[5]) << "        ";
    cout << cell(12,board[12]) << "|" << cell(13, board[13])<< "|" << cell(14, board[14]) << "        ";
    cout << cell(21, board[21]) << "|" << cell(22,board[22])<< "|" << cell(23,board[23]) << endl;
    cout << endl;
    cout << cell(6,board[6]) << "|" << cell(7,board[7])<< "|" << cell(8,board[8]) << "        ";
    cout << cell(15, board[15]) << "|" << cell(16, board[16])<< "|" << cell(17,board[17]) << "        ";
    cout << cell(24,board[24]) << "|" << cell(25,board[25])<< "|" << cell(26,board[26]) << endl;
    cout << endl;
    cout << "///////////////////////////////////////////////////" << endl;
    cout << endl;

}

// Returns false if the cell number is out of range or if it has already been played.
bool checkIfLegal( int cellNbre, char board[]){
    return (cellNbre >= 1 && cellNbre <= 27 && board[cellNbre-1] == 'e');
}

// Controls the user move. The player enters the cell number. It should be an integer.
int takeUserMove(char board[]){
    
    cout << "Your turn! Pick a cell number" << endl;

    int input;

    do {
        cin >> input;

        while (!cin) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Input should be a number" << endl;
            cin >> input;
        }  

        if (!checkIfLegal(input, board)){
            cout << "Input should be a number between 1 and 27. The cell on the board should be empty." << endl;
        }

    } while (!checkIfLegal(input, board));
 
    return input;
}

/////////////// Series of helper methods to check if there is a winner

// Checks winning rows on same boards.
bool checkRows(char board[]){
    for (int i=0; i<27; i+=3){
        if (board[i] != 'e' && board[i] == board[i+1] && board[i] == board[i+2]){
            return true;
        }
    }
    return false;
}

// Checks winning columns.
// Example: 1 / 4 / 7
bool checkCol(char board[]){
    // Check each board one by one
    for (int i=0; i< 19; i += 9){
        // Check each column of the board
        for (int j=i; j< (i+3); j++){
            // Check all the elements of the column, separated by a step of 3.
            if (board[j] != 'e' && board[j] == board[j+3] && board[j] == board[j+6]){
                return true;
            }
        }
    }
    return false;
}

// Checks winning rows on different boards.
// Example : 1 / 10 / 19
// Example : 6 / 15 / 24
// Example : 8 / 17 / 26
bool check3DRows(char board[]){
    // Scheme : from cell 1 to 9, 3D rows are separated by a step of 9.
    for (int i=0; i< 9; i++){
        if (board[i] != 'e' && board[i] == board[i+9] && board[i] == board[i+18]){
            return true;
        }
    }
    return false;
}

// Checks every diagonals by brute force. Same format as checkCol() but separated methods for readability.
bool checkDiag(char board[], int start, int end, int step1, int step2){
    for (int i=start; i< end; i += step1){
        if (board[i] != 'e' && board[i] == board[i+step2] && board[i] == board[i+step2*2]){
            return true;
        }
    }
    return false;
}

//////////////////////////////////////////////////////////

bool checkIfWinner(char board[]){

    //Check diagonals of each board. Example 1/5/9 ; 21/23/25
    bool checkDiagnonalFacesLR = checkDiag(board, 0, 19, 9, 4);
    bool checkDiagonalFacesRL = checkDiag(board, 2, 21, 9, 2);
    bool checkFaces = checkDiagnonalFacesLR || checkDiagonalFacesRL;

    // Check diagonals of the sides (going in the screen). Example: 21/15/9 ; 1/13/25
    bool checkDiagSidesLR = checkDiag(board, 0, 3, 1, 12);
    bool checkDiagSidesRL = checkDiag(board, 18, 21, 1, -6);
    bool checkSides = checkDiagSidesLR || checkDiagSidesRL;
    
    // Check diagonals of the cube, there are two : 1/14/27 and 21/14/7
    bool checkDiagCube1 = (board[0] != 'e' && board[0] == board[13] && board[0] == board[26]);
    bool checkDiagCube2 = (board[6] != 'e' && board[6] == board[13] && board[6] == board[20]);
    bool checkCube = checkDiagCube1 || checkDiagCube2;

    // Check top/down diagonals of the cubes for each row. Example: 1/11/21 ; 25/17/9
    bool checkDiagTopLR = checkDiag(board, 0, 7, 3, 10);
    bool checkDiagTopRL = checkDiag(board, 2, 9, 3, 8);
    bool checkTop = checkDiagTopLR || checkDiagTopRL;


    bool checkAllDiag = checkFaces || checkSides || checkCube || checkTop;

    return checkCol(board) || checkRows(board) || check3DRows(board) || checkAllDiag;
}

void computerMove(char board[]){
    bool endTurn = false;
    int i = 0;

    // check every cell of the board

    // try to play as the computer to see if he can win
    i = 0;
     while (!endTurn  && i<27) {
        if (checkIfLegal(i+1, board)){
            board[i] = 'O';
            if (checkIfWinner(board)){
                std::string cellStr = std::to_string(i+1);
                cout << "The computer played : " + cellStr << endl;
                endTurn = true;
            }
            else{
                board[i] = 'e';
            }
        }
        i++;
    }

    i = 0;
    // try to play as the player to see if there is a winning possibility. If such, play at this case to blopck player
    while (!endTurn  && i<27) {
        if (checkIfLegal(i+1, board)){
            board[i] = 'X';
            if (checkIfWinner(board)){
                board[i] = 'O';
                endTurn = true;
                std::string cellStr = std::to_string(i+1);
                cout << "The computer played : " + cellStr << endl;
            }
            else{
                board[i] = 'e';
            }
        }
        i++;
    }

    // No one can win, play randomly
    while (!endTurn){
        int cell = (1 + std::rand() % (28) );
        if (checkIfLegal(cell, board)){
            board[cell-1] = 'O';
            std::string cellStr = std::to_string(cell);
            cout << "The computer played : " + cellStr << endl;
            endTurn = true;
        }
    }

}
