#include "../include/GeneticAlgorithm.h"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>

#define DEBUGMODE_ 1

void GeneticAlgorithm::run() {
    int i = 0;
    int iterations = 0;
    int parent1, parent2;
    int crossOverIteration, minCrossOver;
    int randomLocus = -1;
    int populationSize = population->length();
    int individualLength = population->individualLength();
    double randomDouble = 0.0, fitnessCrossRate;

    srand( time( NULL ) );
    totalCrossOvers = 0;

    minCrossOver = ( rand() % 3 ) + 1;

    while( iterations++ < minIterations ) {

        parent1 = parent2 = -1;
        crossOverIteration = 0;

        while( crossOverIteration < minCrossOver ) {

            for( i = 0; i < populationSize; ++i ) {

                randomDouble = ( static_cast<double>( rand() ) / static_cast<double>( RAND_MAX ) );
                fitnessCrossRate = ( population->fitnessAt( i ) / static_cast<double>( populationSize ) ) * crossOverRate;
                fitnessCrossRate *= ( fitnessCrossRate < 0.1 ? 5 : 1 ); // Aumentar um pouco a chance.

                if( randomDouble <= fitnessCrossRate ) {
                    if( parent1 == i || parent2 == i ) continue;

                    if( parent1 == -1 ) {
                        parent1 = i;
                    } else {
                        parent2 = i;
                    }
                }

                if( parent1 != -1 && parent2 != -1 ) {

                    randomLocus = rand() % individualLength; // Pegar um locus randomico como ponto de cross over

                    population->crossOver( parent1, parent2, randomLocus );

                    parent1 = parent2 = -1;
                    crossOverIteration++;
                    totalCrossOvers++;
                }
            }
        }

        // Verificar por Mutacoes
        for( i = 0; i < populationSize; ++i ) {
            if( rand() % 10 <= mutationRate ) {

                randomLocus = rand() % individualLength;
                population->mutationAt( i, randomLocus );
                totalMutations++;

            }
        }

    }
}

GeneticAlgorithm::~GeneticAlgorithm() {}
