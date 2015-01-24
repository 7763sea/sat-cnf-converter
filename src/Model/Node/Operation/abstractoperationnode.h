#ifndef MODEL_NODE_OPERATION_ABSTRACTOPERATIONNODE_H
#define MODEL_NODE_OPERATION_ABSTRACTOPERATIONNODE_H

#include <iostream>

#include "../abstractnode.h"

using namespace std;

namespace Model
{
namespace Node
{
namespace Operation
{

/**
 * @brief The AbstractOperationNode class
 * Abstract class for operations (AND, OR, etc)
 */
class AbstractOperationNode: public AbstractNode
{
public:
    AbstractOperationNode();    
    int getType();
    virtual void debugOutput(int nestingLevel) = 0;
    virtual ~AbstractOperationNode();
};

}
}
}

#endif // MODEL_NODE_OPERATION_ABSTRACTOPERATIONNODE_H
