#ifndef CHESS_POSITION_H
#define CHESS_POSITION_H


#include <string>

class Position {
private:
    int column;
    int row;

public:
    Position(int row, int col);
    int getRow() const;
    int getCol() const;
    std::string toString() const;
};


#endif //CHESS_POSITION_H
