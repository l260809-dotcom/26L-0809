#include<iostream>
using namespace std;
void inBoard(int board[8][8])
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            board[row][col] = 0;
            if ((row + col) % 2 == 1)
            {
                if (row < 3) board[row][col] = 2;
                else if (row > 4) board[row][col] = 1;
            }
        }
    }
}

void printBoard(int board[8][8])
{
    cout << " A B C D E F G H" << endl;

    for (int row = 0; row < 8; row++)
    {
        cout << row + 1 << " ";
        for (int col = 0; col < 8; col++)
        {
            if (board[row][col] == 0) cout << ". ";
            else cout << board[row][col] << " ";
        }
        cout << endl;
    }

}
bool isValidMove(int board[8][8], int row1, int col1, int row2, int col2, int chance)
{
    if (row1 < 0 || row1 > 7 || col1 < 0 || col1 > 7)
        return false;

    if (row2 < 0 || row2 > 7 || col2 < 0 || col2 > 7)
        return false;

    if (board[row2][col2] != 0)
        return false;

    int piece = board[row1][col1];
    if (piece != chance && piece != chance + 2) // chance + 2 for king 
        return false;

    int drow = row2 - row1; // drow means new row minus old row
    int dcol = col2 - col1; // dcol means new column minus old column
    if (dcol != 1 && dcol != -1)
        return false;

    bool king = (piece > 2);
    if (king)
        return (drow == 1 || drow == -1);
    if (chance  == 1)
        return drow == -1;
    return drow == 1;
}

bool isvalidJump(int board[8][8], int row1, int col1, int row2, int col2, int chance)
{
    if (row1 < 0 || row1 > 7 || col1 < 0 || col1 > 7)
        return false;
    if (row2 < 0 || row2 > 7 || col2 < 0 || col2 > 7)
        return false;
    if (board[row2][col2] != 0)
        return false;

    int piece = board[row1][col1];
    if (piece != chance && piece != chance + 2)
        return false;

    int drow = row2 - row1;
    int dcol = col2 - col1;
    if (dcol != 2 && dcol != -2) return false;
    if (drow != 2 && drow  != -2) return false;

    bool isKing = (piece > 2);
    if (!isKing)
    {
        if (chance == 1 && drow != -2) return false;
        if (chance == 2 && drow != 2) return false;
    }

    int mid = board[(row1 + row2) / 2][(col1 + col2) / 2];
    if (chance == 1)return (mid == 2 || mid == 4);
    return (mid == 1 || mid == 3);
}

void movePiece(int board[8][8], int row1, int col1, int row2, int col2)
{
    board[row2][col2] = board[row1][col1];
    board[row1][col1] = 0;

    if (board[row2][col2] == 1 && row2 == 0) board[row2][col2] = 3;
    if (board[row2][col2] == 2 && row2 == 7) board[row2][col2] = 4;
}

int main()
{
    int board[8][8];
    inBoard(board);
    int chance = 1;

    while (true)
    {
        printBoard(board);
        cout << "Player " << chance << " move (example: 6 A 5 B), 0 to quit: ";

        int row1, row2;
        char col1, col2;
        cin >> row1;
        if (row1 == 0) break;
        cin >> col1 >> row2 >> col2;

        if (col1 >= 'a')
            if (col2 >= 'a')
                col1 = col1 - 32;
        col2 = col2 - 32;

        int row1_converted = row1 - 1, col1_converted = col1 - 'A';
        int row2_converted = row2 - 1, col2_converted = col2 - 'A';

        if (isValidMove(board, row1_converted, col1_converted, row2_converted, col2_converted, chance))
        {
            movePiece(board, row1_converted, col1_converted, row2_converted, col2_converted);
            chance = 3 - chance;
        }
        else if (isvalidJump(board, row1_converted, col1_converted, row2_converted, col2_converted, chance))
        {
            board[(row1_converted + row2_converted) / 2][(col1_converted + col2_converted) / 2] = 0;
            movePiece(board, row1_converted, col1_converted, row2_converted, col2_converted);
            chance = 3 - chance;
        }
        else
        {
            cout << "Invalid move, try again." << endl;
        }
    }
    return 0;
}