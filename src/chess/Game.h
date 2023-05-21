#ifndef CHESS_GAME_H
#define CHESS_GAME_H


#include <vector>
#include <string>

class Board;
class Move;
class Player;
class Piece;
class Position;
class King;

class Game {
private:
    Board  *board;
    Player *whitePlayer;
    Player *blackPlayer;
    Player *currentPlayer;
    std::vector<Move> moveHistory;

    bool canWhiteKingsideCastle;
    bool canWhiteQueensideCastle;
    bool canBlackKingsideCastle;
    bool canBlackQueensideCastle;
    Position *enPassantTarget;
    int halfmoveClock;
    int fullmoveNumber;

    std::string castlingAvailabilityFEN() const;

public:
    Game(std::string whiteName = "Player 1", std::string blackName = "Player 2");

    ~Game();

    Board *getBoard() const;

    Player *getCurrentPlayer();

    std::vector<Move> &getMoveHistory();

    std::string toFEN() const;

    Player *getWhitePlayer() const;

    Player *getBlackPlayer() const;

    void makeMove(Move move);

    Game afterMove(Move move) const;

    std::vector<Move> getMovesFrom(Position position) const;

    std::vector<Move> getAllPlayerMoves(Player &player) const;

    bool isMate() const;

    bool isCheck() const;


};


#endif //CHESS_GAME_H
