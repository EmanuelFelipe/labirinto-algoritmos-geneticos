#include "../include/Agent.h"

Agent::Agent( Enviroment *_env ): env(_env) {
    search = new Search( _env );
};

void Agent::run() {
    DataNode *sol = NULL, *tempSol = NULL;

    // Usando a busca informada para obter a solucao
    tempSol = sol = search->run( true );

    //std::cout << "dump sol " << std::endl;

    //while( tempSol != NULL ) {
    //    std::cout << '\t' << *tempSol << std::endl;
    //    tempSol = tempSol->getParent();
    //}

    if( sol != NULL ) {
        // Aplica o caminho gerado pelo algoritmo de busca.
        std::cout << "Solution found: " << sol->getCost() << std::endl;
        env->applySolution( sol );
    } else {
        std::cout << "No Solution found" << std::endl;
    }
}
