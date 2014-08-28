#ifndef DATANODE_H
#define DATANODE_H

#include <iostream>
#include <ostream>

/***
    Classe usada para guardar a posicao do node no Maze.
    Ela eh passada para o Enviroment que fornece todas as informacoes sobre esse DataNode.
*/

class DataNode {
    friend std::ostream& operator<<(std::ostream& output, const DataNode& node ) {
        output << "{ i: " << node.i() << ", j: " << node.j()
                  << ", childrenLength: " << node.getChildrenLength()
                  << ", cost: " << node.getCost()
                  << ", heuristic: " << node.getHeuristic() << " }";
        return output;
    }
    public:
        static int dtor, ctor;

        DataNode( const DataNode &node );

        DataNode():
            _i(0), _j(0), parent(NULL), children(NULL),
            childrenLength(0), cost(0), heuristic(0) {

                //std::cout << "ctor2 " << this << std::endl;
                ctor++;
        };
        DataNode( int i, int j ):
            _i(i), _j(j), parent(NULL), children(NULL),
            childrenLength(0), cost(0), heuristic(0) {

                //std::cout << "ctor3 " << this << std::endl;
                ctor++;
        };

        inline int i() const { return _i; };
        inline int j() const { return _j; };
        inline void i( int _i ) { this->_i = _i; };
        inline void j( int _j ) { this->_j = _j; };
        inline DataNode* getParent() const { return parent; };
        inline void setParent( DataNode *parent ) { this->parent = parent; };
        inline DataNode* getChildren() const { return children; };
        inline void setChildren( DataNode* children ) { this->children = children; };
        inline int getChildrenLength() const { return childrenLength; };
        inline void setChildrenLength( int childrenLength ) { this->childrenLength = childrenLength; };
        inline int getCost() const { return cost; };
        inline void setCost( int cost ) { this->cost = cost; };
        inline int getHeuristic() const { return heuristic; };
        inline void setHeuristic( int heuristic ) { this->heuristic = heuristic; };
        inline int getTotalCost() const { return cost + heuristic; };

        void dump( std::ostream& ) const;

        void clean();
        bool parentEqual( DataNode & ) const;
        DataNode* backupChild( const DataNode& );

        virtual ~DataNode() {
            //std::cout << "dtor "<< this << std::endl;
            dtor++;
        };

        bool operator<( const DataNode &node1) const {
            return this->getTotalCost() < node1.getTotalCost();
        }
        bool operator>( const DataNode &node1 ) const {
            return this->getTotalCost() > node1.getTotalCost();
        }
        bool operator==( const DataNode &aNode ) const {
            return this == &aNode || ( this->_i == aNode.i() && this->_j == aNode.j() );
        }
        DataNode& operator=( const DataNode& );
    protected:
    private:
        int _i, _j;
        DataNode *parent;
        DataNode *children;
        int childrenLength;
        int cost, heuristic;
};

#endif // DATANODE_H
