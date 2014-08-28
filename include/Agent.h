#ifndef AGENT_H
#define AGENT_H

#include "Search.h"
#include "Enviroment.h"
#include "DataNode.h"

class Agent
{
    public:
        Agent( Enviroment *_env );
        virtual ~Agent(){ delete search; };

        inline void setMinCost( int minConst ) { this->minCost = minCost; };
        inline void setMaxCost( int maxCost ) { this->maxCost = maxCost; };

        void run();
    protected:
    private:
        Enviroment *env;
        Search *search;
        int minCost, maxCost;
};

#endif // AGENT_H
