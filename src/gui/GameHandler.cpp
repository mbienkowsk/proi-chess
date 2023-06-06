
#include "GameHandler.h"
#include <vector>
#include <QThread>
#include "Player.h"

GameHandler::GameHandler()
        : botGame(false), botColor(Color::BLACK), stockfishBot(nullptr) {
    game = new Game();

}


GameHandler::GameHandler(Game *game, bool BotGame, Color botColor)
        : game(game), botGame(BotGame), botColor(botColor) {
    if (game != nullptr && BotGame) {
        stockfishBot = new StockfishBot(*game);
    } else {
        stockfishBot = nullptr;
    }
}

GameHandler::~GameHandler() {
    delete stockfishBot;
    delete game;
}


Game *GameHandler::getGame() const {
    return game;
}


const std::vector<Move> &GameHandler::getValidMoves() const {
    return validMoves;
}

void GameHandler::clearMoves() {
    validMoves.clear();
}

//void GameHandler::setValidMoves(const std::vector<Move> &validMoves) {
//    GameHandler::validMoves = validMoves;
//}


void GameHandler::makeMove(Move const *move) {
    game->makeMove(*move);
}

void GameHandler::newGame(bool botGame, Color bot_color, std::string const &fenNotation) {
    Game *newGame = nullptr;
    try {
        newGame = new Game(Game::fromFEN(fenNotation));
    } catch (FenException &e) {
        delete newGame;
        throw FenException("Incorrect Fen");
    }

    delete stockfishBot;
    delete game;

    game = newGame;
    this->botGame = botGame;
    this->botColor = bot_color;
    if (botGame) {
        stockfishBot = new StockfishBot(*game);
    }
}


void GameHandler::setBotDepth(int depth) {
    stockfishBot->setDepth(depth);
}

void GameHandler::handleBotMove() {
    if (botGame && botColor == game->getCurrentPlayer()->getColor()) {

        Move botMove = stockfishBot->getBestNextMove();
        game->makeMove(botMove);
    }
}

std::string GameHandler::getGameFen() {
    return game->toFEN();
}

bool GameHandler::isStalemate() {
    return game->isStalemate();
}

bool GameHandler::isCheck(Color kingColor) {
    return game->isCheck(kingColor);
}

bool GameHandler::isMate() {
    return game->isMate();
}

const std::vector<Move> &GameHandler::loadMovesFromPosition(Position position) {
    validMoves = game->getLegalMovesFrom(position);
    return validMoves;
}

Piece *GameHandler::getPiece(Position position) {
    return game->getPiece(position);
}

Color GameHandler::getCurrentPlayerColor() {
    return game->getCurrentPlayer()->getColor();
}


Move *GameHandler::findMoveTo(const Position position) {
    for (auto move: validMoves) {
        Position goal = move.getTo();
        if (goal.getCol() == position.getCol() && goal.getRow() == position.getRow()) {
            return new Move(move);
        }
    }
    return nullptr;
}

bool GameHandler::belongsTo(Piece *piece, Player *player) {
    if (piece == nullptr) {
        return false;
    }
    if (player == nullptr) {
        return false;
    }
    auto playerPieces = player->getPieces();
    return std::find(playerPieces.begin(),
                     playerPieces.end(),
                     piece)
           != playerPieces.end(); // check if the piece belongs to the player
}

bool GameHandler::pieceBelongsToCurrent(Piece *piece) {
    return belongsTo(piece, game->getCurrentPlayer());
}

bool GameHandler::fieldBelongsToCurrent(Position position) {
    Piece *piece = game->getPiece(position);
    return pieceBelongsToCurrent(piece);
}




