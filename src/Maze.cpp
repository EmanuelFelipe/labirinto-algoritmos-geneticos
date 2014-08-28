#include "../include/Maze.h"

#include <iostream>
#include <ctime>
#include <cstdlib>

Maze::Maze( int _rows, int _cols ) : rows(_rows), cols(_cols), randomRate(0), entrance(0,0), exit(0,0), costSolution(-1) {
    int i = 0;
    maze = new MazeCell*[_rows];

    for( i = 0; i < _rows; ++i ) {
        maze[i] = new MazeCell[_cols];
    }
}

Maze::~Maze() {
    int i = 0;

    for( i = 0; i < rows; ++i ) {
        delete[] maze[i];
    }
}

void Maze::generateFirstPopulation() {
    int i = 0, j = 0;

    srand( time( NULL ) );

    for( i = 0; i < rows; ++i ) {
        for( j = 0; j < cols; ++j ) {
            maze[i][j] = ( ( rand() % 100 ) <= randomRate ) ? WAY : WALL;
        }
    }
}

std::ostream& operator<<( std::ostream& output, const Maze& m ) {
    m.print( output );
    return output;
}

std::ostream& Maze::print( std::ostream& output ) const {
    int i = 0, j = 0;

    maze[entrance.i][entrance.j] = ENTRANCE;
    maze[exit.i][exit.j] = EXIT;

    for( i = 0; i < rows; ++i ) {
        for( j = 0; j < cols; ++j ) {
            output << maze[i][j];
        }
        if( i+1 < rows ) {
            output << std::endl;
        }
    }

    output << std::endl << "entrance: " << entrance << ", exit: " << exit << std::endl;

    if( costSolution == -1 )
        output << "No solution found" << std::endl;
    else
        output << "Cost solution: " << costSolution << std::endl;

    return output;
}

double Maze::fitnessAt( int i ) const {
    int j = 0;
    double fitness = 0.0;

    // O individuo sem contar as bordas
    for( j = 0; j < cols; ++j ) {
        if( maze[i][j] == WAY ) {
            fitness++;
        }
    }
    // Se ele nao tiver nenhum caminho, vou dar uma chance a mais para ele.
    if( fitness <= 0.1 ) fitness = 0.25;

    return fitness / (double)cols;
}

void Maze::mutationAt( int i, int locus ) {
    maze[i][locus] = ( maze[i][locus] == WALL ? WAY : WALL );
}

void Maze::crossOver( int p1, int p2, int locus ) {
    Type *parent1 = new Type[cols];
    Type *parent2 = new Type[cols];
    int j = 0;

    locus++; // Locus comeca do 1, ja que 0 eh borda
    // Fazendo um backup dos tipos, para depois sobreescrever direto.
    for( j = 0; j < cols; ++j ) {
        parent1[j] = maze[p1][j].getType();
        parent2[j] = maze[p2][j].getType();
    }

    for( j = 0; j < locus; ++j ) {
        maze[p1][j] = parent1[j]; // Filho 1 recebe a primeira parte do parent1
        maze[p2][j] = parent2[j]; // Filho 2 recebe a primeira parte do parent2
    }

    for( j = locus; j < cols; ++j ) {
        maze[p1][j] = parent2[j]; // Filho 1 recebe a segunda parte do parent2
        maze[p2][j] = parent1[j];
    }

    delete[] parent1;
    delete[] parent2;
}

int Maze::getChildrenLength( const DataNode& node ) const {
        int i = node.i();
        int j = node.j();
        int childs = 0;

        //std::cout << node << std::endl;
        //std::cout << '\t' << ( i+1 ) << ", " << j << ": " << ( i + 1 < rows && maze[i+1][j] != WALL && maze[i+1][j] != EXPLORED ) << std::endl;
        //std::cout << '\t' << i << ", " << ( j+1 ) << ": " << ( j + 1 < cols && maze[i][j+1] != WALL && maze[i][j+1] != EXPLORED ) << std::endl;
        //std::cout << '\t' << ( i-1 ) << ", " << j << ": " << ( i - 1 >= 0 && maze[i-1][j] != WALL && maze[i-1][j] != EXPLORED ) << std::endl;
        //std::cout << '\t' << i << ", " << ( j-1 ) << ": " << ( j - 1 >= 0 && maze[i][j-1] != WALL && maze[i][j-1] != EXPLORED ) << std::endl << std::endl;

        //if( i+1 < rows ) std::cout << "maze[" << i+1 << "][" << j << "] = " << maze[i+1][j] << std::endl;
        //if( j+1 < cols ) std::cout << "maze[" << i << "][" << j+1 << "] = " << maze[i][j+1] << std::endl;
        //if( i-1 >= 0 ) std::cout << "maze[" << i-1 << "][" << j << "] = " << maze[i-1][j] << std::endl;
        //if( j-1 >= 0 ) std::cout << "maze[" << i << "][" << j-1 << "] = " << maze[i][j-1] << std::endl;

        if( i + 1 < rows && maze[i+1][j] != WALL && maze[i+1][j] != EXPLORED ) childs++;
        if( j + 1 < cols && maze[i][j+1] != WALL && maze[i][j+1] != EXPLORED ) childs++;
        if( i - 1 >= 0 && maze[i-1][j] != WALL && maze[i-1][j] != EXPLORED ) childs++;
        if( j - 1 >= 0 && maze[i][j-1] != WALL && maze[i][j-1] != EXPLORED ) childs++;

        return childs;
}

DataNode* Maze::getChildren( const DataNode& node ) const {
    int childrenLength = getChildrenLength( node );
    if( childrenLength == 0 ) return NULL;
    DataNode* children = new DataNode[  childrenLength ];
    int i = node.i();
    int j = node.j();
    int ii = 0;

    // DIREITA
    if( i + 1 < rows && maze[i+1][j] != WALL && maze[i+1][j] != EXPLORED )  {
        maze[i+1][j] = EXPLORED;
        children[ii].i( i + 1 );
        children[ii++].j( j );
    }

    // BAIXO
    if( j + 1 < cols && maze[i][j+1] != WALL && maze[i][j+1] != EXPLORED ) {
        maze[i][j+1] = EXPLORED;
        children[ii].i( i );
        children[ii++].j( j + 1 );
    }

    // ESQUERDA
    if( i - 1 >= 0 && maze[i-1][j] != WALL && maze[i-1][j] != EXPLORED ) {
        maze[i-1][j] = EXPLORED;
        children[ii].i( i - 1 );
        children[ii++].j( j );
    }

    // CIMA
    if( j - 1 >= 0 && maze[i][j-1] != WALL && maze[i][j-1] != EXPLORED ) {
        maze[i][j-1] = EXPLORED;
        children[ii].i( i );
        children[ii++].j( j - 1 );
    }

    return children;
}

int Maze::heuristic( const int i, const int j ) const {
    int di, dj;

    di = i - exit.i;
    dj = j - exit.j;

    if( di < 0 ) di *= -1;
    if( dj < 0 ) dj *= -1;

    return di + dj;
}

int Maze::heuristic( const DataNode& data ) const {
    return heuristic( data.i(), data.j() );
}

DataNode* Maze::getInitialNode() const {
    DataNode* initial = new DataNode( entrance.i, entrance.j );

    initial->setChildrenLength( getChildrenLength( *initial ) );
    initial->setChildren( getChildren( *initial ) );
    initial->setCost( 0 );

    return initial;
}

void Maze::applySolution( const DataNode *lastNode ) {
    DataNode *temp;
    if( lastNode == NULL ) return;

    costSolution = lastNode->getCost();

    // O ultimo noh eh a saida, entao eh melhor comecar do anterior
    temp = lastNode->getParent();

    if( temp == NULL ) return;

    while( temp->getParent() != NULL ) {
        maze[temp->i()][temp->j()] = USED;
        temp = temp->getParent();
    }
}

bool Maze::searchDoors() {
    int i = 0, j = 0;
    int rows_1 = rows - 1, cols_1 = cols - 1;
    int rows_2 = rows_1 - 1, cols_2 = cols_1 - 1;

    // Eh preciso excluir os cantos na verificacao.
    doors.clear();

    // Verrendo a borda superior
    for( j = 1; j < cols_1; ++j ) {
        if( maze[0][j] == WAY ) { // Se a celula eh uma saida/entrada
            if( maze[1][j] == WAY ) { // Se a celula logo a frente for livre, entao considera.
                doors.push_back( doorCoordinates( 0, j ) );
            }
        }
    }

    // Varrendo a borda direita.
    for( i = 1; i < rows_1; ++i ) {
        if( maze[i][cols_1] == WAY ) {
            if( maze[i][cols_2] == WAY ) {
                doors.push_back( doorCoordinates( i, cols_1 ) );
            }
        }
    }

    // Varrendo a borda inferior.
    for( j = 1; j < cols_1; ++j ) {
        if( maze[rows_1][j] == WAY ) {

            if( maze[rows_2][j] == WAY ) {
                doors.push_back( doorCoordinates( rows_1, j ) );
            }
        }
    }

    // Varrendo a borda esquerda.
    for( i = 1; i < rows_1; ++i ) {
        if( maze[i][0] == WAY ) {
            if( maze[i][1] == WAY ) {
                doors.push_back( doorCoordinates( i, 0 ) );
            }
        }
    }

    // Se o size for impar, remove um para ficar exato.
    if( doors.size() % 2 ) {
        doors.pop_back();
    }

    if( doors.size() < 2 ) {
        doors.clear();
        return false;
    }
    return true;
}

bool Maze::selectDoors( const int min, const int max ) {
    int size = doors.size();
    int i, j;

    if( size == 0 ) return false;

    // Fazendo a combinacao de portas 2 a 2 para ver
    // qual delas pode ser valida
    for( i = 0; i < size; ++i ) {
        entrance = doors.at(i);

        for( j = 0; j < size; ++j ) {
            exit = doors.at(j);

            if( i != j && validDistance( min, max ) ) {
                maze[entrance.i][entrance.j] = ENTRANCE;
                maze[exit.i][exit.j] = EXIT;

                if( i > j ) {
                    doors.erase( doors.begin() + i );
                    doors.erase( doors.begin() + j );
                } else {
                    doors.erase( doors.begin() + j );
                    doors.erase( doors.begin() + i );
                }

                return true;
            }
        }
    }

    return false;
}

void Maze::reset() {
    int i = 0, j = 0;

    for( i = 0; i < rows; ++i ) {
        for( j = 0; j < cols; ++j ) {
            if( maze[i][j] == EXPLORED ) {
                maze[i][j] = WAY;
            }
        }
    }

    maze[entrance.i][entrance.j] = WAY;
    maze[exit.i][exit.j] = WAY;
}
