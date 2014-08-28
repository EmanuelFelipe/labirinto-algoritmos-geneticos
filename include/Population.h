#ifndef POPULATION_H
#define POPULATION_H

class Population
{
    public:
        virtual void mutationAt( int, int ) = 0; // Realiza a mutacao do individuo i no locus
        virtual double fitnessAt( int ) const = 0; // Retorna o valor do fitness no individuo i
        virtual void generateFirstPopulation() = 0; // Gera uma populacao randomica para a primeira geracao
        virtual void crossOver( int, int, int ) = 0; // Faz o cross over de dois individuos no locus.
        virtual int length() const = 0;
        virtual int individualLength() const = 0;
        virtual ~Population() {};
    protected:

    private:
};

#endif // POPULATION_H
