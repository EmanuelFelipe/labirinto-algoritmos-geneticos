#include <iostream>
#include <queue>

#include "include/GeneticAlgorithm.h"
#include "include/Maze.h"
#include "include/FileHandler.h"
#include "include/Search.h"
#include "include/DataNode.h"
#include "include/Agent.h"

#define ROWS 50
#define COLS 50
#define MIN_ITERATIONS 100
#define MUTATION_RATE 0.2
#define CROSS_OVER_RATE 0.6
#define RANDOM_RATE 60
#define MIN_COST 70
#define MAX_COST 90

int main( int argc, char ** argv ) {

    std::string *filename = NULL;
    int times = 0, cost = 0, innerTimes = 0;
    bool mazeValid = false;
    FileHandler *file = NULL;
    Maze *maze = new Maze( ROWS, COLS );
    GeneticAlgorithm *algorithm = new GeneticAlgorithm( maze );
    Search *search = new Search( maze );
    Agent *agent = new Agent( maze );

    if( argc == 2 ) {
        filename = new std::string( argv[1] );
    } else {
        filename = new std::string( "maze.txt" );
    }

    algorithm->setMinIterations( MIN_ITERATIONS );
    algorithm->setMutationRate( MUTATION_RATE );
    algorithm->setCrossOverRate( CROSS_OVER_RATE );

    maze->setRandomRate( RANDOM_RATE );
    maze->generateFirstPopulation();

    do {
        times++;
        algorithm->run();

        mazeValid = maze->searchDoors();
        // Se ele nao tem portas suficientes para testar
        // Executa o A.G denovo
        if( ! mazeValid ) {
            continue;
        }

        while( ( mazeValid = maze->selectDoors( MIN_COST, MAX_COST ) ) ) {

            // Se a menor distancia entre a entrada e saida for maior
            // que o MAX_COST, entao nao ha caminho valido
            if( ! maze->validDistance( MIN_COST, MAX_COST ) ) {
                continue;
            }

            cost = search->hasSolution( true ); // Usa o algoritmo A*, mais rapido a convergencia...
            if( cost >= MIN_COST && cost <= MAX_COST ) {
                break;
            }
            innerTimes++;
        }
        if( times % 10 == 0 ) {
            std::cout << times << ": " << DataNode::ctor << ", " << DataNode::dtor << std::endl;
        }

    } while( ! mazeValid );

    agent->run();

    try {
        file = new FileHandler( filename->c_str() );
        file->printMaze( maze );
        std::cout << "Maze dump in " << *filename << std::endl;
    } catch( int e ) {
        std::cout << file->getErrorMessage();
    }

    delete agent;
    delete search;
    delete maze;
    delete filename;
    delete algorithm;
    delete file;

    return 0;
}
