#include "Chess.h"
#include <cstdio> // only used it to remove the file after loading data from it. remove(file) is used in Loadgame function.

ChessBoard::ChessBoard()
{
    for (int col = 0; col < 8; col++)
    {
        blackPieces.push_back(ChessPiece(PieceType::Pawn, false, 6, col, 1)); // We create all the pieces and push them to vectors according to their color.
    }
    blackPieces.push_back(ChessPiece(PieceType::Rook, false, 7, 0, 5)); // false means it is black, 7 is row coord, 0 is column coord, 5 is the score.
    blackPieces.push_back(ChessPiece(PieceType::Knight, false, 7, 1, 3));
    blackPieces.push_back(ChessPiece(PieceType::Bishop, false, 7, 2, 3));
    blackPieces.push_back(ChessPiece(PieceType::Queen, false, 7, 3, 9));
    blackPieces.push_back(ChessPiece(PieceType::King, false, 7, 4));
    blackPieces.push_back(ChessPiece(PieceType::Bishop, false, 7, 5, 3));
    blackPieces.push_back(ChessPiece(PieceType::Knight, false, 7, 6, 3));
    blackPieces.push_back(ChessPiece(PieceType::Rook, false, 7, 7, 5));

    whitePieces.push_back(ChessPiece(PieceType::Rook, true, 0, 0, 5));
    whitePieces.push_back(ChessPiece(PieceType::Knight, true, 0, 1, 3));
    whitePieces.push_back(ChessPiece(PieceType::Bishop, true, 0, 2, 3));
    whitePieces.push_back(ChessPiece(PieceType::Queen, true, 0, 3, 9));
    whitePieces.push_back(ChessPiece(PieceType::King, true, 0, 4));
    whitePieces.push_back(ChessPiece(PieceType::Bishop, true, 0, 5, 3));
    whitePieces.push_back(ChessPiece(PieceType::Knight, true, 0, 6, 3));
    whitePieces.push_back(ChessPiece(PieceType::Rook, true, 0, 7, 5));
    for (int col = 0; col < 8; col++)
    {
        whitePieces.push_back(ChessPiece(PieceType::Pawn, true, 1, col, 1));
    }

    for (int row = 0; row < 8; row++) // the Board hold chesspiece pointers, we push the pieces addressed to the board's relevant coordınates
    {
        vector<ChessPiece *> _row;
        for (int col = 0; col < 8; col++) // By the way the indexing of the board starts from bottom left corner.
        {
            if (row == 0 || row == 1)
            {
                _row.push_back(&whitePieces[row * 8 + col]);
            }
            else if (row == 6 || row == 7)
            {
                _row.push_back(&blackPieces[(row - 6) * 8 + col]);
            }
            else
                _row.push_back(nullptr);
        }
        board.push_back(_row);
    }
}

void ChessBoard::printboard() const
{
    int row_number = 8;
    char c = 'a';

    cout << endl;
    for (auto iter = board.rbegin(); iter != board.rend(); ++iter)
    {
        cout << row_number << " |";
        for (const auto &piece : *iter)
        {
            if (piece == nullptr)
                cout << "  .";
            else
                cout << ' ' << *piece;
        }
        --row_number;
        cout << endl;
    }
    cout << "    ------------------------\n   ";

    for (const auto &i : board)
    {
        cout << "  " << c;
        ++c;
    }
    cout << endl;
}

void ChessBoard::makeMove()
{
    string move;
    bool flag = false;
    int cur_row, cur_col, new_row, new_col;
    ChessPiece *temp;

    while (!flag)
    {
        if (isWhitesTurn())
            cout << "\n\n[White's Turn]\nEnter your move: ";
        else
            cout << "\n\n[Black's Turn]\nEnter your move: ";
        cin >> move;
        if (move == "suggest")
        {
            Suggest();
            continue;
        }
        else if (move == "save")
        {
            SaveGame();
            cout << "Saving the Game...\n";
            exit(0);
        }
        else if (move.length() == 4)
        {
            if (move[0] >= 'a' && move[0] <= 'h' && move[2] >= 'a' && move[2] <= 'h' && move[1] >= '1' && move[1] <= '8' && move[3] >= '1' && move[3] <= '8')
            {
                cur_row = move[1] - 49, cur_col = move[0] - 97; // transform char coordinates to int.
                new_row = move[3] - 49, new_col = move[2] - 97;
                if (board[cur_row][cur_col] != nullptr && isWhitesTurn() == board[cur_row][cur_col]->isWhitePiece()) // check if there is a valid piece int the source coordinate
                {
                    if (board[new_row][new_col] == nullptr || board[new_row][new_col]->isWhitePiece() != isWhitesTurn()) // check if the piece in desitnation coordinate is not player's own piece
                    {
                        flag = board[cur_row][cur_col]->PieceMotion(*this, new_row, new_col); // send these coordinates to the move function. ıf the move is doable it will return true.
                    }
                    if (flag == true) // if it is true we make the move then set all the pieces that are left under attack
                    {
                        temp = board[new_row][new_col];
                        board[new_row][new_col] = board[cur_row][cur_col];
                        board[cur_row][cur_col] = nullptr;
                        board[new_row][new_col]->setRow(new_row);
                        board[new_row][new_col]->setCol(new_col);
                        if (temp != nullptr)
                            temp->setAlive(false);
                        setThreats();
                        if (isCheck()) // İf king is left under attack that means player actually can not perform thıs move.
                        {
                            cout << "THIS MOVE LEAVES THE KING UNDER THREAT !!";
                            board[cur_row][cur_col] = board[new_row][new_col];
                            board[new_row][new_col] = temp;
                            if (temp != nullptr)
                                temp->setAlive(true);
                            board[cur_row][cur_col]->setRow(cur_row);
                            board[cur_row][cur_col]->setCol(cur_col); // put the pıeces to theır prevıous locatıon.
                            flag = false;                             // make the flag flse so we can ask for a new move
                        }
                    }
                    else
                        cout << "THIS MOVE CAN NOT BE PERFORMED!!";
                }
                else
                {
                    cout << "THERE IS NO SUITABLE PIECE TO MOVE FROM THAT POSITION!!";
                }
            }
            else
            {
                cout << "INVALID COORDINATES";
            }
        }
        else
        {
            cout << "INVALID INPUT!!";
        }
        while (cin.get() != '\n')
            ; // Cleans the input buffer
    }
    if (board[new_row][new_col]->getType() == PieceType::Pawn && ((isWhitesTurn() && new_row == 7) || (!isWhitesTurn() && new_row == 0)))
    {
        // this condition checks if a pawn has reached to the opposite edge of the board. İf so, it changes the pawn with the chosen piece
        printboard();
        PawnSwitch(board[new_row][new_col]);
        board[new_row][new_col]->PieceThreat(*this); // After the change, We set the new threates, (a.k.a finding the pieces under attack.)
    }
    switchPlayer();
}

void ChessBoard::setThreats()
{
    for (ChessPiece &w_piece : whitePieces) // first set all of them to false to avoıd conflicts.
        w_piece.settUnderAttack(false);
    for (ChessPiece &b_piece : blackPieces)
        b_piece.settUnderAttack(false);

    for (ChessPiece &w_piece : whitePieces) // Then set the actual threats
    {
        if (w_piece.isAlive())
            w_piece.PieceThreat(*this);
    }
    for (ChessPiece &b_piece : blackPieces)
    {
        if (b_piece.isAlive())
            b_piece.PieceThreat(*this);
    }
}

bool ChessBoard::isCheck() const // checks if king is under attack
{
    if (isWhitesTurn())
        return whitePieces[4].isUnderAttack();

    return blackPieces[12].isUnderAttack();
}

bool ChessBoard::isGameOver()
{
    bool areThereLegalMoves = false; // if there are no legal move for the player, the game is over
    vector<ChessPiece>::iterator it, endIt;
    int row, col;
    ChessPiece *temp;

    if (isWhitesTurn()) // First,To be able to go through all of player's pieces, we have to know whose turn it is.
    {
        it = whitePieces.begin(); // set the iterator to the vectors accordingly.
        endIt = whitePieces.end();
    }
    else
    {
        it = blackPieces.begin();
        endIt = blackPieces.end();
    }

    for (; it != endIt && areThereLegalMoves == false; ++it) // go Through every piece unless there is a legal move
    {
        if (!(*it).isAlive()) // if the piece is dead, no need to check it
            continue;
        row = (*it).getRow();
        col = (*it).getCol();
        for (int _row = 0; _row < 8 && areThereLegalMoves == false; ++_row)
        {
            for (int _col = 0; _col < 8 && areThereLegalMoves == false; ++_col)
            {
                if (board[_row][_col] == nullptr || board[_row][_col]->isWhitePiece() != isWhitesTurn())
                {
                    areThereLegalMoves = board[row][col]->PieceMotion(*this, _row, _col); // The same thing in the makemove function.
                    if (areThereLegalMoves == true)
                    {
                        temp = board[_row][_col];
                        board[_row][_col] = board[row][col];
                        board[row][col] = nullptr;
                        board[_row][_col]->setRow(_row);
                        board[_row][_col]->setCol(_col);
                        if (temp != nullptr)
                            temp->setAlive(false);
                        setThreats();

                        if (isCheck())
                            areThereLegalMoves = false;

                        board[row][col] = board[_row][_col];
                        board[_row][_col] = temp;
                        if (temp != nullptr)
                            temp->setAlive(true);
                        board[row][col]->setRow(row);
                        board[row][col]->setCol(col);
                    }
                }
            }
        }
    }

    if (areThereLegalMoves == true)
        return false;

    return true;
}

void ChessBoard::PawnSwitch(ChessPiece *&piece)
{
    if ((piece)->getType() != PieceType::Pawn) // Only a pawn can transform
        return;
    PieceType type;
    string s;
    bool flag = false;
    int score;
    while (!flag)
    {
        cout << "Choose the piece you want to replace with:"
             << "\n1. ROOK\n2. KNIGHT\n3. BISHOP\n4. QUEEN\n>: ";
        cin >> s;
        if (s.length() == 1 && s[0] >= 49 && s[0] <= 52)
            flag = true;
        while (cin.get() != '\n')
            ;
    }
    switch (s[0])
    {
    case '1':
        type = PieceType::Rook;
        score = 5;
        break;
    case '2':
        type = PieceType::Knight;
        score = 3;
        break;
    case '3':
        type = PieceType::Bishop;
        score = 3;
        break;
    case '4':
        type = PieceType::Queen;
        score = 9;
        break;
    }

    piece->setType(type);
    piece->setScore(score);
}

void ChessBoard::CalculateScores()
{
    scoreBlack = 0;
    scoreWhite = 0;
    for (int i = 0; i < 16; ++i)
    {
        if (blackPieces[i].isAlive())
        {
            if (blackPieces[i].isUnderAttack())
                scoreBlack += blackPieces[i].getScore() / 2;
            else
                scoreBlack += blackPieces[i].getScore();
        }
        if (whitePieces[i].isAlive())
        {
            if (whitePieces[i].isUnderAttack())
                scoreWhite += whitePieces[i].getScore() / 2;
            else
                scoreWhite += whitePieces[i].getScore();
        }
    }
}

void ChessBoard::Suggest()
{
    int cur_row, cur_col, new_row, new_col;
    int best_score = -100, score; // Inıtıalıze the best score wıth a very low value.
    bool isLegalMove;
    ChessPiece *temp;
    vector<ChessPiece>::iterator it, endIt;

    if (isWhitesTurn()) // set the iterators to the player to who we wıll make suggestıon
    {
        it = whitePieces.begin();
        endIt = whitePieces.end();
    }
    else
    {
        it = blackPieces.begin();
        endIt = blackPieces.end();
    }

    for (; it != endIt; ++it) // The idea is to go through every piece of the player that is alive and calculate a score for every possible move.
    {                         // then choosing the move that producces the best score.
        if (!it->isAlive())
            continue;

        int row = it->getRow();
        int col = it->getCol();

        for (int _row = 0; _row < 8; ++_row)
        {
            for (int _col = 0; _col < 8; ++_col)
            {
                if (board[_row][_col] == nullptr || board[_row][_col]->isWhitePiece() != isWhitesTurn())
                {
                    isLegalMove = board[row][col]->PieceMotion(*this, _row, _col);
                    if (isLegalMove == true) // if the piece can go to the given coordinates legaly, we calculate the score for that move
                    {
                        temp = board[_row][_col];
                        board[_row][_col] = board[row][col];
                        board[row][col] = nullptr;
                        board[_row][_col]->setRow(_row);
                        board[_row][_col]->setCol(_col);
                        if (temp != nullptr)
                            temp->setAlive(false);
                        setThreats();
                                       // we make the move,set the threat,
                        if (isCheck()) // if the move leaves the king under attack, we make sure we dont make that move.
                            score = -100;
                        else
                        {
                            switchPlayer();
                            if(isGameOver()) //game over checks if the opononent has any legal moves, we swıtch player becasue of that.
                                score = 100; //if the move ends the game we make sure we pick it.
                            else
                            {
                                CalculateScores();
                                if(!isWhitesTurn()) //Due to having changed player, if its not whites turn it actually is white's turn
                                    score = scoreWhite - scoreBlack;
                                else
                                    score = scoreBlack - scoreWhite;
                            }
                            switchPlayer(); //switch the player back
                        }
                        if (score > best_score) // ıf the score is bigger, we keep this move
                        {
                            cur_row = row;
                            cur_col = col;
                            new_row = _row;
                            new_col = _col;
                            best_score = score;
                        }
                        board[row][col] = board[_row][_col];    //after calculatıng the score, we put the pıece back so we can check for a new move
                        board[_row][_col] = temp;   
                        if (temp != nullptr)
                            temp->setAlive(true);
                        board[row][col]->setRow(row);
                        board[row][col]->setCol(col);
                    }
                }
            }
        }
    }
    cout << "Suggestion is " << static_cast<char>(cur_col + 97) << static_cast<char>(cur_row + 49) << static_cast<char>(new_col + 97)
         << static_cast<char>(new_row + 49); //we print the move that produces the best score.
}

void ChessBoard::SaveGame()
{
    ofstream file(FILENAME, ios::binary);

    if (!file)
    {
        cerr << "Error in opening file for writing !!" << endl;
        return;
    }

    file.write(reinterpret_cast<const char *>(&White), sizeof(White)); // save whose turn it is.
    int size = whitePieces.size();
    file.write(reinterpret_cast<const char *>(whitePieces.data()), size * sizeof(ChessPiece)); // save the white pieces
    file.write(reinterpret_cast<const char *>(blackPieces.data()), size * sizeof(ChessPiece)); // save the black pieces
    file.close();
}

ChessBoard ChessBoard::LoadGame()
{
    ifstream file(FILENAME, ios::binary);

    if (!file)
    {
        cerr << "Error opening file for reading" << endl;
        exit(1);
    }
    ChessBoard temp(FILENAME); //we create a temporary chessboard object so that we can hold the datas in the fıle.
    ChessPiece piece(PieceType::Pawn, false, -1, -1, -1); //create a temporary piece to read the pieces from the file.

    file.read(reinterpret_cast<char *>(&temp.White), sizeof(temp.White)); // read whose turn it is
    for (int i = 0; i < 16; ++i)
    {
        file.read(reinterpret_cast<char *>(&piece), sizeof(ChessPiece)); // read the white pieces
        temp.whitePieces.push_back(piece); //push the pieces to the temporary chessboard object.
    }
    for (int i = 0; i < 16; ++i)
    {
        file.read(reinterpret_cast<char *>(&piece), sizeof(ChessPiece)); // read the black pieces
        temp.blackPieces.push_back(piece);
    }
    file.close();

    if (remove(FILENAME) != 0) //after reading, remove the file.
        cerr << "Error deleting file !!" << endl;

    return temp; //We return this object and assign it to our original chessboard object in the main function.(overloaded  operator=)
}

ChessBoard &ChessBoard::operator=(const ChessBoard &temp)
{
    int row, col;

    for (auto &old_w_piece : whitePieces) //in our original Chessboard object, we make every coordinate point to nullptr.
    {
        if (old_w_piece.isAlive())
        {
            row = old_w_piece.getRow();
            col = old_w_piece.getCol();
            board[row][col] = nullptr;
        }
    }
    for (auto &old_b_piece : blackPieces)
    {
        if (old_b_piece.isAlive())
        {
            row = old_b_piece.getRow();
            col = old_b_piece.getCol();
            board[row][col] = nullptr;
        }
    }
    whitePieces.empty(); //then we empty the vectors.
    blackPieces.empty();
    whitePieces = temp.whitePieces; //Then we assign the values that read from the fıle.
    blackPieces = temp.blackPieces;
    White = temp.White; //Then we assign whose turn it was.
    for (auto &w_piece : whitePieces) //Then we put the pieces on the board.
    {
        if (w_piece.isAlive())
        {
            row = w_piece.getRow();
            col = w_piece.getCol();
            board[row][col] = &w_piece;
        }
    }
    for (auto &b_piece : blackPieces)
    {
        if (b_piece.isAlive())
        {
            row = b_piece.getRow();
            col = b_piece.getCol();
            board[row][col] = &b_piece;
        }
    }

    return *this;
}