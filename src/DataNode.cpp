#include "../include/DataNode.h"

int DataNode::ctor = 0;
int DataNode::dtor = 0;

DataNode::DataNode( const DataNode& node ) {
    this->_i = node.i();
    this->_j = node.j();
    this->parent = node.getParent();
    this->children = node.getChildren();
    this->childrenLength = node.getChildrenLength();
    this->cost = node.getCost();
    this->heuristic = node.getHeuristic();

    ctor++;
    //std::cout << "ctor1 " << this << std::endl;
}

DataNode& DataNode::operator=( const DataNode& node ) {
    this->_i = node.i();
    this->_j = node.j();
    this->parent = node.getParent();
    this->children = node.getChildren();
    this->childrenLength = node.getChildrenLength();
    this->cost = node.getCost();
    this->heuristic = node.getHeuristic();

    return *this;
}

void DataNode::clean() {
    int i = 0;

    if( childrenLength != 0 && children != NULL ) {
        for( i = 0; i < childrenLength; ++i ) {
            children[ i ].clean();
        }
        delete[] children;
        childrenLength = 0;
        children = NULL;
    }
}

bool DataNode::parentEqual( DataNode& node ) const {
    DataNode *temp = this->parent;

    while( temp != NULL ) {
        if( node == *temp ) return true;
        temp = temp->getParent();
    }

    return false;
}

void DataNode::dump( std::ostream& output ) const {
    if( childrenLength == 0 ) return;
    DataNode *temp = &children[0];

    while( temp <= &children[childrenLength] ) {
        temp++;
        output << '\t' << temp << std::endl;
    }
}

DataNode* DataNode::backupChild( const DataNode& target ) {
    int i = 0;

    for( i = 0; i < childrenLength; ++i ) {
        if( children[ i ] == target ) {
            children[ i ] = DataNode( target );
            return &children[ i ];
        }
    }

    return NULL;
}
