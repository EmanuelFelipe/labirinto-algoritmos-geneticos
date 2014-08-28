#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include "Population.h"

/*
    O meu Algoritmo genetico ira considerar cada linha interna, removendo-se as bordas como um membro da populacao.
    Logo a funcao de fitness eh proporcional ao numero de celulas do tipo WAY vezes uma probabilidade de CrossOver fixa.
*/

class GeneticAlgorithm
{
    public:

        GeneticAlgorithm( Population* _population ) : population( _population ) {};
        virtual ~GeneticAlgorithm();

        inline void setMinIterations( int minIterations ) { this->minIterations = minIterations;};
        inline void setMutationRate( double mutationRate ) { this->mutationRate = mutationRate; };
        inline void setCrossOverRate( double crossOverRate ) { this->crossOverRate = crossOverRate; };
        inline const int getTotalCrossOver() const { return totalCrossOvers; };
        inline const int getTotalMutations() const { return totalMutations; };

        void run(); // Funcao principal da classe, executa o A.G

    protected:
    private:
        int minIterations; // Numero maximo de iteracoes
        double crossOverRate; // Taxa de CrossOver
        double mutationRate; // Taxa de mutacao

        Population *population;
        int totalCrossOvers, totalMutations;
};

#endif // GENETICALGORITHM_H
