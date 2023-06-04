
#include "GameField.h"
#include "Color.h"
#include "pieces/PieceType.h"
#include "mainwindow.h"
#include "ChessIcons.h"
#include <QMouseEvent>
#include <map>
#include <string>
#include <QColor>
#include <QDebug>


static int fieldSize = 50;

std::map<PieceType, std::string> pieceChars{
        {PieceType::NONE,   ""},
        {PieceType::PAWN,   "♟"},
        {PieceType::ROOK,   "♜"},
        {PieceType::BISHOP, "♝"},
        {PieceType::KNIGHT, "♞"},
        {PieceType::KING,   "♚"},
        {PieceType::QUEEN,  "♛"},
};


GameField::GameField(const QString &text, int x, int y, QWidget *parent, Qt::WindowFlags f) :
        ClickableLabel(text, parent, f), marked(false) {
    QFont font = this->font();
    font.setPointSize(20);
    font.setBold(true);
    this->setFont(font);
    this->x = x;
    this->y = y;
    overlay = new QLabel(this);
    // Can't figure out how to get dimensions of GameField, all methods return weird 30X100 dimensions
    overlay->setGeometry(0, 0, fieldSize, fieldSize);
    overlay->show();
    overlay->raise();
    setMark(false);
}

GameField::~GameField() noexcept {
    // destructor calls will propagate upwards the inheritance tree, so everything will be cleaned up
    delete overlay;

}


/**
 *
 * @param called_x - identifies which field was called to update
 * @param called_y - identifies which field was called to update
 * @param type - SUBJECT TO CHANGE: the type of piece it's supposed to now hold
 * @param mark - the new state of being marked, false by default
 **/
void GameField::updatePieceCalled(int called_x, int called_y, PieceType type, Color color) {
    if (called_x == x && called_y == y) {
        setPiece(type, color);
    }
}


void GameField::mousePressEvent(QMouseEvent *event) {
    ClickableLabel::mousePressEvent(event);
    if (event->button() == Qt::LeftButton) {
        emit fieldClicked(this);
    }
}

void GameField::setPiece(PieceType type, Color color) {

    std::string fileName = ""; //= ":/resources/";

    if (color == Color::WHITE) {
        fileName += "White_";
    } else {
        fileName += "Black_";
    }
    switch (type) {
        case PieceType::NONE:
            break;
        case PieceType::KING:
            fileName += "king";
            break;
        case PieceType::KNIGHT:
            fileName += "knight";
            break;
        case PieceType::PAWN:
            fileName += "pawn";
            // qDebug() << "Changed pixmap!";
            break;
        case PieceType::QUEEN:
            fileName += "queen";
            break;
        case PieceType::ROOK:
            fileName += "rook";
            break;
        case PieceType::BISHOP:
            fileName += "bishop";
    }
    //fileName += ".png";
    //pixmap.load(QString().fromStdString(fileName));
    QPixmap pixmap = icons.pieceImgs[fileName];
    QString new_text = QString::fromStdString(pieceChars[type]);
    this->setText(new_text);
    this->setPixmap(pixmap.scaled(fieldSize, fieldSize, Qt::AspectRatioMode::KeepAspectRatio));

}

int GameField::getX() const {
    return x;
}

int GameField::getY() const {
    return y;
}

const PieceType &GameField::getPiece() const {
    return piece;
}

void GameField::reset() {
    setPiece(PieceType::NONE, Color::WHITE);
    clicked = false;
    setMark(false);
}

void GameField::setMark(bool new_mark) {

    marked = new_mark;
    if (marked) {
        overlay->setPixmap(
                QPixmap(":/resources/orange_frame_overlay.png").scaled(fieldSize, fieldSize,
                                                                       Qt::AspectRatioMode::KeepAspectRatio));
    } else {
        overlay->setPixmap(QPixmap());
    }
}

void GameField::markUpdateCalled(int called_x, int called_y, bool new_mark) {
    if (this->x == called_x and called_y == this->y) {
        setMark(new_mark);
    }
}

