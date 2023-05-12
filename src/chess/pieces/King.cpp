#include "King.h"

King::King(Color color, Field *field, Player *owner) {
    this->color = color;
    this->parentField = field;
    this->player = owner;
}

std::vector<Move> King::getMoves() const {
    return std::vector<Move>();
}

PieceType King::getType() const {
    return PieceType::KING;
}

Color King::getColor() const {
    return color;
}

Board *King::getBoard() const {
    return parentField->getBoard();
}

Field *King::getField() const {
    return parentField;
}

Player *King::getPlayer() const {
    return player;
}

char King::getCharacter() const {
    return 'K';
}

std::string King::getUnicodeSymbol() const {
    return (color == Color::BLACK) ? "♚" : "♔";
}