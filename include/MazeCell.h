#ifndef MAZECELL_H
#define MAZECELL_H

#include <ostream>

enum Type {
    WAY = 0, WALL = 1, EXPLORED = 2, USED = 3, ENTRANCE = 4, EXIT = 5
};

inline std::ostream& operator<<(std::ostream& output, const Type& t ) {
    char c = 'X';

    switch( t ) {
        case WAY: c = ' '; break;
        case WALL: c = '#'; break;
        case EXPLORED: c = '@'; break;
        case USED: c = '*'; break;
        case ENTRANCE: c = '1'; break;
        case EXIT: c = '2'; break;
    }

    output << c;

    return output;
}

class MazeCell {
    friend std::ostream& operator<<(std::ostream&, const MazeCell& );
    public:
        MazeCell( Type );
        MazeCell();
        virtual ~MazeCell();

        inline Type getType() const { return type; };

        bool operator==( const Type& type ) const { return this->type == type; };
        bool operator!=( const Type& type ) const { return this->type != type; };
        MazeCell operator=( const Type& type ) { this->type = type; return *this; };
    protected:
    private:
        Type type; // Indica se eh Caminho, Parede ou Porta
};

#endif // MAZECELL_H
