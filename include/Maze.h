#ifndef MAZE_H
#define MAZE_H

#include <ostream>
#include <vector>
#include "MazeCell.h"
#include "Population.h"
#include "Enviroment.h"
#include "DataNode.h"

typedef struct _doorCoordinates {
    int i, j;

    friend std::ostream& operator<<(std::ostream& output, const _doorCoordinates& door ) {
        output << "{ i: " << door.i << ", j: " << door.j << " }";
        return output;
    }

    public:
        _doorCoordinates( int _i, int _j) : i(_i), j(_j) {};
        bool operator==( const _doorCoordinates& door ) const {
            return door.i == this->i && door.j == this->j;
        };
        bool operator!=( const _doorCoordinates& door ) const {
            return door.i != this->i || door.j != this->j;
        }
        bool operator==( const DataNode& node ) const {
            return this->i == node.i() && this->j == node.j();
        }
        // cpy ctor
        _doorCoordinates& operator=( const _doorCoordinates& door ) {
            this->i = door.i;
            this->j = door.j;

            return *this;
        }
} doorCoordinates;

class Maze : virtual public Population, virtual public Enviroment
{
    friend std::ostream& operator<<(std::ostream&, const Maze& );
    public:
        Maze( int, int );

        // Metodos virtuais da classe Population
        virtual void mutationAt( int, int );
        virtual double fitnessAt( int ) const;
        virtual void generateFirstPopulation();
        virtual void crossOver( int, int, int );
        virtual inline int length() const { return rows; };
        virtual inline int individualLength() const { return cols; };

        //Metodos virtuais da classe Enviroment
        virtual void applySolution( const DataNode * );
        virtual bool isSolution( const DataNode& node ) const { return exit == node; };
        virtual inline int cost( const DataNode& ) const { return 1; };
        virtual int heuristic( const int, const int ) const;
        virtual int heuristic( const DataNode& ) const; // Uso a distancia Manhattan entre a posicao e a saida
        virtual int getChildrenLength( const DataNode& ) const;
        virtual DataNode* getInitialNode() const;
        virtual DataNode* getChildren( const DataNode& ) const;
        virtual void reset();

        std::ostream& print( std::ostream& ) const;
        inline void setRandomRate( int randomRate ) { this->randomRate = randomRate; };
        bool searchDoors();
        bool selectDoors( const int, const int );

        inline bool validDistance( const int min, const int max ) const {
            // Se a menor distancia entra a entrada e saida for maior que o maximo aceitavel...
            // Entao nenhum caminho sera aceito
            return heuristic( entrance.i, entrance.j ) <= max;
        };

        virtual ~Maze();
    protected:
    private:
        MazeCell **maze;
        // Este vector eh usado no metodo que sortei duas portas
        // entre as portas geradas pelo AG.
        std::vector<doorCoordinates> doors;
        int rows, cols;
        int randomRate;

        doorCoordinates entrance, exit;
        int costSolution;
};

#endif // MAZE_H
