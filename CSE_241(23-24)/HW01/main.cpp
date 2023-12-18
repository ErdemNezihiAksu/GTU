#include "Chess.h"

int main()
{
    ifstream file(FILENAME, ios::binary);
    ChessBoard game;

    if (file.is_open()) //if there is a file to open, that means there is a saved game.
    {
        file.close();
        string option;
        bool flag = false;
        while (!flag)
        {
            cout << "A SAVED GAME IS FOUND, DO YOU WANT TO LOAD IT:\n1. Yes\n2. No\n>: ";
            cin >> option;
            if (option.length() == 1 && (option[0] == 49 || option[0] == 50))
                flag = true;
            else
                cout << "INVALID OPTION !!" << endl;
            while(cin.get() != '\n'); //Cleans the input buffer
        }
        if (option[0] == 49)
        {
            game = ChessBoard::LoadGame(); //LoadGame() closes and removes the file after reading the data;
        }
    }

    do
    {
        game.printboard();
        game.makeMove();
    } while (!game.isGameOver());

    game.printboard();
    cout << "\n\nGAME OVER " << endl;
    if (game.isCheck())
    {
        cout << "CHECKMATE, ";
        if (game.isWhitesTurn())
            cout << "BLACK WINS !!" << endl;
        else
            cout << "WHITE WINS !!" << endl;
    }
    else
        cout << "STATEMATE, IT'S A DRAW !!" << endl;
}