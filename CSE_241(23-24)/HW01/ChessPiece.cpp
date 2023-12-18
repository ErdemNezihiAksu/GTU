#include "Chess.h"

ostream &operator<<(ostream &outStream, const ChessPiece &piece)
{
    if (piece.isWhitePiece())
        outStream << ' ' << static_cast<char>(static_cast<char>(piece.type) - 32);
    else
        outStream << ' ' << static_cast<char>(piece.type);
    return outStream;
}

bool ChessPiece::PieceMotion(ChessBoard &obj, int new_row, int new_col)
{
    switch (getType())          //All of these functions check if the given destinatio coordinates are valid for the source piece.
    {
    case PieceType::Rook:
        return PathofRook(obj, new_row, new_col);
    case PieceType::Bishop:
        return PathofBishop(obj, new_row, new_col);
    case PieceType::Knight:
        return PathofKnight(obj, new_row, new_col); //If the source piece is knight, we check if the given coordinates are valid for that knight.
    case PieceType::King:
        return PathofKing(obj, new_row, new_col);
    case PieceType::Pawn:
        return PathofPawn(obj, new_row, new_col);
    case PieceType::Queen:
        return (PathofRook(obj, new_row, new_col) || PathofBishop(obj, new_row, new_col));
    }
}

bool ChessPiece::PathofRook(ChessBoard &obj, int new_row, int new_col)
{
    const int row = getRow();
    const int col = getCol();

    if (new_row == row)
    {
        if (new_col > col)
        {
            for (int i = col + 1; i < new_col; ++i)
            {
                if (obj[row][i] != nullptr)
                    return false;
            }
        }
        else
        {
            for (int i = col - 1; i > new_col; --i)
            {
                if (obj[row][i] != nullptr)
                    return false;
            }
        }
        return true;
    }
    else if (new_col == col)
    {
        if (new_row > row)
        {
            for (int i = row + 1; i < new_row; ++i)
            {
                if (obj[i][col] != nullptr)
                    return false;
            }
        }
        else
        {
            for (int i = row - 1; i > new_row; --i)
            {
                if (obj[i][col] != nullptr)
                    return false;
            }
        }
        return true;
    }
    return false;
}

bool ChessPiece::PathofBishop(ChessBoard &obj, int new_row, int new_col)
{
    const int row = getRow();
    const int col = getCol();

    if (new_row - new_col == row - col)
    {
        if (new_row > row)
        {
            for (int _row = row + 1, _col = col + 1; _row < new_row && _col < new_col; ++_row, ++_col)
            {
                if (obj[_row][_col] != nullptr)
                    return false;
            }
        }
        else
        {
            for (int _row = row - 1, _col = col - 1; _row > new_row && _col > new_col; --_row, --_col)
            {
                if (obj[_row][_col] != nullptr)
                    return false;
            }
        }
        return true;
    }
    else if (new_row + new_col == row + col)
    {
        if (new_row > row)
        {
            for (int _row = row + 1, _col = col - 1; _row < new_row && _col > new_col; ++_row, --_col)
            {
                if (obj[_row][_col] != nullptr)
                    return false;
            }
        }
        else
        {
            for (int _row = row - 1, _col = col + 1; _row > new_row && _col < new_col; --_row, ++_col)
            {
                if (obj[_row][_col] != nullptr)
                    return false;
            }
        }
        return true;
    }
    return false;
}

bool ChessPiece::PathofKnight(ChessBoard &obj, int new_row, int new_col)
{
    const int row = getRow();
    const int col = getCol();

    if ((abs(row - new_row) == 2 && abs(col - new_col) == 1) || (abs(row - new_row) == 1 && abs(col - new_col) == 2))
        return true;
    return false;
}

bool ChessPiece::PathofKing(ChessBoard &obj, int new_row, int new_col)
{
    const int row = getRow();
    const int col = getCol();

    if ((abs(new_row - row) == 1 && abs(new_col - col) == 1) || (new_row == row && abs(new_col - col) == 1) || (new_col == col && abs(new_row - row) == 1))
        return true;
    return false;
}

bool ChessPiece::PathofPawn(ChessBoard &obj, int new_row, int new_col)
{
    const int row = getRow();
    const int col = getCol();

    if (isWhitePiece())
    {
        if (new_row == row + 1 && new_col == col && obj[new_row][new_col] == nullptr)
            return true;
        if (new_row == row + 1 && (new_col == col + 1 || new_col == col - 1) && obj[new_row][new_col] != nullptr && !obj[new_row][new_col]->isWhitePiece())
            return true;
        if(new_row == row + 2 && row == 1 && new_col == col && obj[new_row][new_col] == nullptr)
            return true;
    }
    else
    {
        if (new_row == row - 1 && new_col == col && obj[new_row][new_col] == nullptr)
            return true;
        if (new_row == row - 1 && (new_col == col + 1 || new_col == col - 1) && obj[new_row][new_col] != nullptr && obj[new_row][new_col]->isWhitePiece())
            return true;
        if(new_row == row - 2 && row == 6 && new_col == col && obj[new_row][new_col] == nullptr)
            return true;
    }
    return false;
}

void ChessPiece::PieceThreat(ChessBoard &obj)
{
    switch (getType())
    {
    case PieceType::Rook:       //All of these functions set the pieces that are threatend by the source piece under attack.
        ThreatofRook(obj);
        break;
    case PieceType::Bishop:
        ThreatofBishop(obj);    //if the source piece is bishop, then every piece that are threatend by that bishop are set underattack.
        break;
    case PieceType::Knight:
        ThreatofKnight(obj);
        break;
    case PieceType::King:
        ThreatofKing(obj);
        break;
    case PieceType::Pawn:
        ThreatofPawn(obj);
        break;
    case PieceType::Queen:
        ThreatofRook(obj);
        ThreatofBishop(obj);
        break;
    }
}

void ChessPiece::ThreatofRook(ChessBoard &obj)
{
    const int row = getRow();
    const int col = getCol();

    for (int _col = col + 1; _col < 8; ++_col)
    {
        if (obj[row][_col] != nullptr)
        {
            if(isWhitePiece() != obj[row][_col]->isWhitePiece())
                obj[row][_col]->settUnderAttack(true);
            break;
        }
    }
    for (int _col = col - 1; _col >= 0; --_col)
    {
        if (obj[row][_col] != nullptr)
        {
            if(isWhitePiece() != obj[row][_col]->isWhitePiece())
                obj[row][_col]->settUnderAttack(true);
            break;
        }
    }
    for (int _row = row + 1; _row < 8; ++_row)
    {
        if (obj[_row][col] != nullptr)
        {
            if( isWhitePiece() != obj[_row][col]->isWhitePiece())
                obj[_row][col]->settUnderAttack(true);
            break;
        }
    }
    for (int _row = row - 1; _row >= 0; --_row)
    {
        if (obj[_row][col] != nullptr)
        {
            if(isWhitePiece() != obj[_row][col]->isWhitePiece())
                obj[_row][col]->settUnderAttack(true);
            break;
        }
    }
}

void ChessPiece::ThreatofBishop(ChessBoard &obj)
{
    const int row = getRow();
    const int col = getCol();

    for (int _row = row + 1, _col = col + 1; _row < 8 && _col < 8; ++_row, ++_col)
    {
        if (obj[_row][_col] != nullptr)
        {
            if(isWhitePiece() != obj[_row][_col]->isWhitePiece())
                obj[_row][_col]->settUnderAttack(true);
            break;
        }
    }
    for (int _row = row - 1, _col = col - 1; _row >= 0 && _col >= 0; --_row, --_col)
    {
        if (obj[_row][_col] != nullptr)
        {
            if(isWhitePiece() != obj[_row][_col]->isWhitePiece())
                obj[_row][_col]->settUnderAttack(true);
            break;
        }
    }
    for (int _row = row + 1, _col = col - 1; _row < 8 && _col >= 0; ++_row, --_col)
    {
        if (obj[_row][_col] != nullptr)
        {
            if(isWhitePiece() != obj[_row][_col]->isWhitePiece())
                obj[_row][_col]->settUnderAttack(true);
            break;
        }
    }
    for (int _row = row - 1, _col = col + 1; _row >= 0 && _col < 8; --_row, ++_col)
    {
        if (obj[_row][_col] != nullptr)
        {
            if(isWhitePiece() != obj[_row][_col]->isWhitePiece())
                obj[_row][_col]->settUnderAttack(true);
            break;
        }
    }
}

void ChessPiece::ThreatofKnight(ChessBoard &obj)
{
    const int row = getRow();
    const int col = getCol();

    if (row - 2 >= 0 && col + 1 < 8 && obj[row - 2][col + 1] != nullptr && isWhitePiece() != obj[row - 2][col + 1]->isWhitePiece())
    {
        obj[row - 2][col + 1]->settUnderAttack(true);
    }
    if (row - 2 >= 0 && col - 1 >= 0 && obj[row - 2][col - 1] != nullptr && isWhitePiece() != obj[row - 2][col - 1]->isWhitePiece())
    {
        obj[row - 2][col - 1]->settUnderAttack(true);
    }
    if (row + 2 < 8 && col + 1 < 8 && obj[row + 2][col + 1] != nullptr && isWhitePiece() != obj[row + 2][col + 1]->isWhitePiece())
    {
        obj[row + 2][col + 1]->settUnderAttack(true);
    }
    if (row + 2 < 8 && col - 1 >= 0 && obj[row + 2][col - 1] != nullptr && isWhitePiece() != obj[row + 2][col - 1]->isWhitePiece())
    {
        obj[row + 2][col - 1]->settUnderAttack(true);
    }
    if (row - 1 >= 0 && col + 2 < 8 && obj[row - 1][col + 2] != nullptr && isWhitePiece() != obj[row - 1][col + 2]->isWhitePiece())
    {
        obj[row - 1][col + 2]->settUnderAttack(true);
    }
    if (row - 1 >= 0 && col - 2 >= 0 && obj[row - 1][col - 2] != nullptr && isWhitePiece() != obj[row - 1][col - 2]->isWhitePiece())
    {
        obj[row - 1][col - 2]->settUnderAttack(true);
    }
    if (row + 1 < 8 && col + 2 < 8 && obj[row + 1][col + 2] != nullptr && isWhitePiece() != obj[row + 1][col + 2]->isWhitePiece())
    {
        obj[row + 1][col + 2]->settUnderAttack(true);
    }
    if (row + 1 < 8 && col - 2 >= 0 && obj[row + 1][col - 2] != nullptr && isWhitePiece() != obj[row + 1][col - 2]->isWhitePiece())
    {
        obj[row + 1][col - 2]->settUnderAttack(true);
    }
}

void ChessPiece::ThreatofPawn(ChessBoard &obj)
{
    const int row = getRow();
    const int col = getCol();

    if (isWhitePiece() && row < 7)
    {
        if (col < 7 && obj[row + 1][col + 1] != nullptr && !obj[row + 1][col + 1]->isWhitePiece())
            obj[row + 1][col + 1]->settUnderAttack(true);
        if (col > 0 && obj[row + 1][col - 1] != nullptr && !obj[row + 1][col - 1]->isWhitePiece())
            obj[row + 1][col - 1]->settUnderAttack(true);
    }
    else if(row > 0)
    {
        if (col < 7 && obj[row - 1][col + 1] != nullptr && obj[row - 1][col + 1]->isWhitePiece())
            obj[row - 1][col + 1]->settUnderAttack(true);
        if (col > 0 && obj[row - 1][col - 1] != nullptr && obj[row - 1][col - 1]->isWhitePiece())
            obj[row - 1][col - 1]->settUnderAttack(true);
    }
}

void ChessPiece::ThreatofKing(ChessBoard &obj)
{
    const int row = getRow();
    const int col = getCol();

    for (int _row = row - 1; _row <= row + 1; ++_row)
    {
        if (_row < 0 || _row > 7)
            continue;
        for (int _col = col - 1; _col <= col + 1; ++_col)
        {
            if (_col < 0 || _col > 7 || (_row == row && _col == col))
                continue;
            if (obj[_row][_col] != nullptr && isWhitePiece() != obj[_row][_col]->isWhitePiece())
                obj[_row][_col]->settUnderAttack(true);
        }
    }
}