#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

const int SIZE = 10;
const char EMPTY = ' ';
const char SHIP = '#';
const char HIT = 'X';
const char MISS = 'O';

using namespace std;

void initializeBoard(vector<vector<char>>& board) {
    for (int i = 0; i < SIZE; i++) {
        vector<char> row(SIZE, EMPTY);
        board.push_back(row);
    }
}

void printBoard(const vector<vector<char>>& board) {
    cout << "   ";
    for (int i = 0; i < SIZE; i++) {
        cout << i << " ";
    }
    cout << endl;

    for (int i = 0; i < SIZE; i++) {
        cout << i << "  ";
        for (int j = 0; j < SIZE; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool isValidPosition(int row, int col) {
    return row >= 0 && row < SIZE&& col >= 0 && col < SIZE;
}

bool isShipOverlap(const vector<vector<char>>& board, int row, int col) {
    static const int dx[] = { 0, 0, 1, -1 };
    static const int dy[] = { 1, -1, 0, 0 };

    for (int i = 0; i < 4; i++) {
        int newRow = row + dx[i];
        int newCol = col + dy[i];
        if (isValidPosition(newRow, newCol) && board[newRow][newCol] == SHIP) {
            return true;
        }
    }

    return false;
}

void placeShips(vector<vector<char>>& board) {
    int shipCount = 0;
    while (shipCount < 5) {
        int row = rand() % SIZE;
        int col = rand() % SIZE;
        if (board[row][col] == EMPTY && !isShipOverlap(board, row, col)) {
            board[row][col] = SHIP;
            shipCount++;
        }
    }
}

bool isGameOver(const vector<vector<char>>& board) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == SHIP) {
                return false;
            }
        }
    }
    return true;
}

void playerTurn(vector<vector<char>>& board) {
    int row, col;
    cout << "Enter target coordinates (row column): ";
    cin >> row >> col;

    if (isValidPosition(row, col)) {
        if (board[row][col] == SHIP) {
            cout << "Hit!\n";
            board[row][col] = HIT;
        }
        else if (board[row][col] == EMPTY) {
            cout << "Miss!\n";
            board[row][col] = MISS;
        }
        else {
            cout << "Already guessed that position.\n";
        }
    }
    else {
        cout << "Invalid coordinates.\n";
    }
}

void computerTurn(vector<vector<char>>& board) {
    int row, col;

    do {
        row = rand() % SIZE;
        col = rand() % SIZE;
    } while (!isValidPosition(row, col) || board[row][col] == HIT || board[row][col] == MISS);

    if (board[row][col] == SHIP) {
        cout << "Computer hit at (" << row << ", " << col << ")!\n";
        board[row][col] = HIT;
    }
    else {
        cout << "Computer missed at (" << row << ", " << col << ")!\n";
        board[row][col] = MISS;
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    vector<vector<char>> playerBoard;
    vector<vector<char>> computerBoard;

    initializeBoard(playerBoard);
    initializeBoard(computerBoard);

    cout << "=== Player's Board ===\n";
    printBoard(playerBoard);
    cout << "=== Computer's Board ===\n";
    printBoard(computerBoard);

    placeShips(playerBoard);
    placeShips(computerBoard);

    while (!isGameOver(playerBoard) && !isGameOver(computerBoard)) {
        playerTurn(computerBoard);
        computerTurn(playerBoard);

        cout << "=== Player's Board ===\n";
        printBoard(playerBoard);
        cout << "=== Computer's Board ===\n";
        printBoard(computerBoard);
    }

    if (isGameOver(playerBoard)) {
        cout << "Congratulations! You won!\n";
    }
    else {
        cout << "Sorry, the computer won!\n";
    }

    return 0;
}
