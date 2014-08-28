#include "../include/Search.h"

#include <iostream>
#include <cassert>

int Search::hasSolution( bool informed ) {
    DataNode *solution = ( informed ? getInformedSolution() : getSolution() );
    bool sol = solution != NULL;
    int cost = 0;

    if( sol ) cost = solution->getCost();
    // deixa intacto o labirinto...
    env->reset();

    return sol ? cost : -1;
}

DataNode* Search::run( bool informed ) {
    if( informed ) return getInformedSolution();
    return getSolution();
}

DataNode* Search::getSolution() {
    int i = 0, childrenLength, childCost;
    // Parent node vai ficar com o ultimo "no" da arvore de busca no caminho da solucao...
    DataNode *initialNode, *children, *parentNode, *tempNode;

    if( env == NULL ) return NULL;

    if( lastInitialNode != NULL ) {
        lastInitialNode->clean();
        delete lastInitialNode;
        lastInitialNode = NULL;
    }

    while( boundary.size() > 0 ) boundary.pop();

    initialNode = env->getInitialNode();
    initialNode->setParent( NULL );
    lastInitialNode = initialNode;

    boundary.push( *initialNode );

    do {
        tempNode = const_cast<DataNode*>(&boundary.top());

        // Faz o backup do filho no pai, pois o vai ser deletado pelo container
        // Nao deixar ponteiro dangling no pai...
        if( tempNode->getParent() != NULL ) {
            parentNode = tempNode->getParent();
            parentNode = parentNode->backupChild( *tempNode );
        } else {
            // Esse trecho soh ira acontecer uma vez, para o primeiro noh
            parentNode = new DataNode( *tempNode );
            lastInitialNode = parentNode;
            // Initial eh copiado para parentNode, logo eh seguro deletar
            delete initialNode;
        }

        // Nao deletar os filhos, porque podem estar na fila de prioridade.
        tempNode->setChildren(NULL);
        tempNode->setChildrenLength(0);

        // Aqui sera deletado o tempNode...
        // parentNode agora eh o backup de tempNode
        boundary.pop();

        if( env->isSolution( *parentNode ) ) {
            return parentNode;
        }

        childrenLength = parentNode->getChildrenLength();
        children = parentNode->getChildren();

        for( i = 0; i < childrenLength; ++i ) {

            childCost = parentNode->getCost() + env->cost( children[ i ] );
            children[ i ].setParent( parentNode );
            children[ i ].setCost( childCost );

            children[ i ].setChildrenLength( env->getChildrenLength( children[ i ] ) );
            children[ i ].setChildren( env->getChildren( children[ i ] ) );

            boundary.push( children[ i ] );

        }

    } while( boundary.size() > 0 );

    lastInitialNode->clean();
    delete lastInitialNode;
    lastInitialNode = NULL;

    return NULL;
}

DataNode* Search::getInformedSolution() {
    int i = 0, childrenLength, childCost;
    // Parent node vai ficar com o ultimo "no" da arvore de busca no caminho da solucao...
    DataNode *initialNode, *children, *parentNode, *tempNode;

    if( env == NULL ) return NULL;

    if( lastInitialNode != NULL ) {
        lastInitialNode->clean();
        delete lastInitialNode;
        lastInitialNode = NULL;
    }

    while( boundary.size() > 0 ) boundary.pop();

    initialNode = env->getInitialNode();
    initialNode->setHeuristic( env->heuristic( *initialNode ) );
    initialNode->setParent( NULL );

    lastInitialNode = initialNode;

    boundary.push( *initialNode );

    do {
        tempNode = const_cast<DataNode*>(&boundary.top());

        //std::cout << *tempNode << std::endl;

        // Faz o backup do filho no pai, pois o vai ser deletado pelo container
        // Nao deixar ponteiro dangling no pai...
        if( tempNode->getParent() != NULL ) {
            parentNode = tempNode->getParent();
            parentNode = parentNode->backupChild( *tempNode );
        } else {
            parentNode = new DataNode( *tempNode );
            lastInitialNode = parentNode;
            delete initialNode;
        }

        // Nao deletar os filhos, porque podem estar na fila de prioridade.
        tempNode->setChildren(NULL);
        tempNode->setChildrenLength(0);

        boundary.pop();

        if( env->isSolution( *parentNode ) ) {
            return parentNode;
        }

        childrenLength = parentNode->getChildrenLength();
        children = parentNode->getChildren();

        for( i = 0; i < childrenLength; ++i ) {

            //std::cout << '\t' << children[ i ] << std::endl;

            childCost = parentNode->getCost() + env->cost( children[ i ] );

            children[ i ].setHeuristic( env->heuristic( children[ i ] ) );

            children[ i ].setParent( parentNode );
            children[ i ].setCost( childCost );
            children[ i ].setChildrenLength( env->getChildrenLength( children[ i ] ) );
            children[ i ].setChildren( env->getChildren( children[ i ] ) );

            boundary.push( children[ i ] );
        }

    } while( boundary.size() > 0 );

    lastInitialNode->clean();
    delete lastInitialNode;
    lastInitialNode = NULL;

    return NULL;
}
