#include "../include/MazeCell.h"

MazeCell::MazeCell(): type(WALL) {}

MazeCell::MazeCell( Type _type ): type(_type) {}

std::ostream& operator<<( std::ostream& output, const MazeCell& m ) {
    output << m.getType();
    return output;
}

MazeCell::~MazeCell() {}
