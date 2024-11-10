#include "pthread.h"
#include "iostream"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "bits/stdc++.h"
#include "ctime"
#include "cstdlib"
using namespace std;
void printboard(int board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == 0)
                cout << "_";
            else if (board[i][j] == 1)
                cout << "X";
            else
                cout << "O";
        }
        cout << endl;
    }
    cout << endl;
}
bool checkwinner(int board[3][3], int& who)
{
    if (board[0][0] == board[0][1] && board[0][0] == board[0][2] && board[0][0] != 0)
    {
        who = board[0][0];
        return true;
    }
    else if (board[1][0] == board[1][1] && board[1][0] == board[1][2] && board[1][0] != 0)
    {
        who = board[1][0];
        return true;
    }
    else if (board[2][0] == board[2][1] && board[2][0] == board[2][2] && board[2][0] != 0)
    {
        who = board[2][0];
        return true;
    }
    else if (board[0][0] == board[1][0] && board[0][0] == board[2][0] && board[0][0] != 0)
    {
        who = board[0][0];
        return true;
    }
    else if (board[0][1] == board[1][1] && board[0][1] == board[2][1] && board[0][1] != 0)
    {
        who = board[0][1];
        return true;
    }
    else if (board[0][2] == board[1][2] && board[0][2] == board[2][2] && board[0][2] != 0)
    {
        who = board[0][2];
        return true;
    }
    else if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != 0)
    {
        who = board[0][0];
        return true;
    }
    else if (board[0][2] == board[1][1] && board[0][0] == board[2][0] && board[0][2] != 0)
    {
        who = board[0][2];
        return true;
    }
    else
    {
        return false;
    }
}
void findloc(int board[3][3], int& row, int& col, int opp)
{
    bool winner = false;
    int who;
    for (int i = 0; i < 3 && winner == false; i++)
    {
        for (int j = 0; j < 3 && winner == false; j++)
        {
            if (board[i][j] == 0)
            {
                row = i;
                col = j;
                board[i][j] = opp;
                winner = checkwinner(board, who);
                board[i][j] = 0;
            }
        }
    }
}
int main()
{
    int key;
    do {
        int m;
        float n = 1;
        bool winner = false;
        int board[3][3] = { 0 };
        printboard(board);
        int player = 1, row, col, who;

        for (int i = 0; i < 9 && winner == false; i++) {
            if (player == 1) {
                cout << "Press 0 to open something else" << endl;
                cin >> m;
                if (m == 0) {
                  system("g++ -o deallocate dealloc_resource.cpp");
                   system("./deallocate TICTAC");
                    return 0;
                }
                else {
                    cout << "Enter row and column" << endl;
                    cin >> row >> col;
                    findloc(board, row, col, 2);
                    board[row][col] = 1;
                    player = 2;
                }
            }
            else {
                cout << "Enter row and column" << endl;
                cin >> row >> col;
                while (board[row][col] != 0) {
                    cout << "\nreenter\n";
                    cin >> row >> col;
                }
                board[row][col] = 2;
                player = 1;
            }
            printboard(board);
            winner = checkwinner(board, who);
            if (winner) {
                cout << "the winner is player " << who << endl;
            }
            int L;
            cout << "If you want to quit press 0" << endl;
            cout << "Press 1 to continue" << endl;
            cin >> L;
            if (L == 0) {
                break;
            }
            else if (L == 1 && !winner ) {
                cout << "You may continue" << endl;
            }
            if (winner) {
                cout << "Press 1 to restart the game or 0 to exit" << endl;
                cin >> key;
                if (key == 1) {
                    break;
                }
            }
        }
    } while (key != 0);

    cin.ignore();
    cout << "\t\t\t" << "Press any key to Exit..." << endl;
    cin.get();
    // Compile the deallocate resource file before running it
    system("g++ -o deallocate dealloc_resource.cpp");
    // Run the deallocate resource file with an argument CALCULATOR
    system("./deallocate TICTAC ");
    return 0;
}

