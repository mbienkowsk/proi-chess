#include "Bishop.h"
#include "PieceType.h"
#include "../Color.h"
#include "../Field.h"
#include <vector>


Bishop::Bishop(Color color, Field *field, Player *owner) {
    this->color = color;
    this->parentField = field;
    this->player = owner;
}

std::vector<Move> Bishop::getMoves() const {
    return this->getMovesInDirections({{1,  1},
                                       {1,  -1},
                                       {-1, 1},
                                       {-1, -1}});
}

PieceType Bishop::getType() const {
    return PieceType::BISHOP;
}

Color Bishop::getColor() const {
    return color;
}

Board *Bishop::getBoard() const {
    return parentField->getBoard();
}

Field *Bishop::getField() const {
    return parentField;
}

Player *Bishop::getPlayer() const {
    return player;
}

char Bishop::getCharacter() const {
    return (color == Color::BLACK) ? 'b' : 'B';
}

std::string Bishop::getUnicodeSymbol() const {
    return (color == Color::BLACK) ? "♝" : "♗";
}