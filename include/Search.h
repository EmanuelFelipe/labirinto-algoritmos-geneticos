#ifndef SEARCH_H
#define SEARCH_H

#include <vector>
#include <queue>
#include <stack>
#include <iostream>

#include "Enviroment.h"
#include "DataNode.h"

// ReverseComparator eh usado na busca informada, onde o algoritmo de A* usa
// uma fila de prioridade para escolher o no da fronteira com menor f = custo + heuristica
class ReverseComparator {
    private:
    public:
        ReverseComparator(){};
        bool operator() (const DataNode& lhs, const DataNode&rhs) const {
            return lhs > rhs;
        }
};

class Search
{
    public:
        Search( Enviroment *_env ): env(_env), lastInitialNode(NULL), costLimit(250){};
        inline void setCostLimit( int costLimit ) { this->costLimit = costLimit; };

        int hasSolution( bool informed = false  );
        DataNode* run( bool informed = false );

        virtual ~Search(){
            if( lastInitialNode != NULL ) {
                lastInitialNode->clean();
                delete lastInitialNode;
            }
        };
    protected:
        DataNode* getInformedSolution(); // A*
        DataNode* getSolution(); // Busca gulosa.
    private:
        Enviroment *env;
        DataNode *lastInitialNode;
        std::priority_queue<DataNode, std::vector<DataNode>, ReverseComparator> boundary;
        int costLimit; // Se algum no chegar ao limite de custo, ele eh abandonado...
};

#endif // SEARCH_H
