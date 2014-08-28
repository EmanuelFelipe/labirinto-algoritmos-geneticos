#ifndef ENVIROMENT_H
#define ENVIROMENT_H

#include "DataNode.h"

 // Atencao, para efeitos praticos, o enviroment nao repete celula do labirinto...
 // Isso garante que ira ter solucao, mas nao otima...
 // O problema que estava ocorrendo, eh que a busca ficava em loop no labirinto.
 // Porque havia uma repeticao muito grande de caminhos.

class Enviroment {
    public:
        // Aplica o caminho gerado
        virtual void applySolution( const DataNode * ) = 0;
        // Verifica se um noh eh solucao
        virtual bool isSolution( const DataNode& ) const = 0;
        // Custo do noh
        virtual int cost( const DataNode& ) const = 0;
        // Retorna o valor da heuristica daquele noh
        virtual int heuristic( const DataNode& ) const = 0;
        // Retorna o numero de filhos o noh possui
        virtual int getChildrenLength( const DataNode& ) const = 0;
        // Retorna um no com a posicao da entrada
        virtual DataNode* getInitialNode() const = 0;
        // Retorna um vetor com os filhos daquele noh
        virtual DataNode* getChildren( const DataNode& ) const = 0;
        // Reseta o labirinto
        virtual void reset() = 0;
        virtual ~Enviroment() {}
    protected:
    private:
};

#endif // ENVIROMENT_H
