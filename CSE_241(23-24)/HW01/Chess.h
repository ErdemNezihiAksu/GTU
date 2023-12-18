#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#define FILENAME "chess.bin"

using namespace std;

class ChessBoard;

enum class PieceType : char {
    King = 'k',
    Queen = 'q',
    Rook = 'r',
    Knight = 'n',
    Bishop = 'b',
    Pawn = 'p'
};

class ChessPiece
{
    public:
        ChessPiece(PieceType _type, bool _isWhite, int _row, int _col,int _score=0 ,bool _underAttack = false): type(_type),white(_isWhite),UnderAttack(_underAttack),alive(true),rowId(_row),colId(_col),score(_score) {}
        inline bool isWhitePiece() const {return white;}
        inline bool isUnderAttack() const {return UnderAttack;}
        inline bool isAlive() const {return alive;}
        inline void setAlive(bool value) {alive = value;}
        inline void settUnderAttack(bool value) {UnderAttack = value;} 
        inline void setScore(const int _score) {score = _score;}
        inline const int getScore() const {return score;}
        inline void setRow(int row) {rowId = row;}
        inline void setCol(int col) {colId = col;}
        inline const int getRow() const {return rowId;}
        inline const int getCol() const {return colId;}
        inline void setType(const PieceType _type) {type = _type;}
        inline const PieceType getType() const {return type;}
        friend ostream& operator<<(ostream& outStream, const ChessPiece& piece);
        bool PieceMotion(ChessBoard& obj, int new_row, int new_col); //checks if the given coordinates are valid for chosen piece.
        void PieceThreat(ChessBoard &obj); //checks which pieces the chosen piece threats.
        
    private:
        bool white;
        bool UnderAttack;
        bool alive;
        PieceType type;
        int rowId;
        int colId;
        int score;
        bool PathofRook(ChessBoard& obj, int new_row, int new_col); //Path functıons are called inside PieceMotion function accordingly.
        bool PathofKnight(ChessBoard& obj, int new_row, int new_col);
        bool PathofPawn(ChessBoard& obj, int new_row, int new_col);
        bool PathofBishop(ChessBoard& obj, int new_row, int new_col);
        bool PathofKing(ChessBoard& obj, int new_row, int new_col);
        void ThreatofRook(ChessBoard& obj); //Threat functions are called inside PieceThreaat function accordingly.
        void ThreatofBishop(ChessBoard& obj);
        void ThreatofKnight(ChessBoard& obj);
        void ThreatofPawn(ChessBoard& obj);
        void ThreatofKing(ChessBoard& obj);
};


class ChessBoard
{
    public:
        ChessBoard();
        ChessBoard(const char* filename){/*Intentionaly left empty*/};
        ChessBoard& operator=(const ChessBoard& temp);
        inline void switchPlayer() {White =  (!isWhitesTurn()) ? true : false;}
        inline bool isWhitesTurn() const {return White;}
        vector<ChessPiece*>& operator[] (int row) {return board[row];}
        void makeMove();
        bool isGameOver();
        void printboard() const;
        void Suggest();
        void setThreats();
        bool isCheck() const;
        void CalculateScores();
        void SaveGame();
        static ChessBoard LoadGame();

    private:
        vector<vector<ChessPiece*> >  board;
        vector<ChessPiece> whitePieces;
        vector<ChessPiece> blackPieces;
        bool White = true;
        int scoreBlack;
        int scoreWhite;
        void PawnSwitch(ChessPiece*& piece); //when a pawn reaches to the opposite edge of the board, it turns into another piece.
};
#endif