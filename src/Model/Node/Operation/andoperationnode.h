#ifndef MODEL_NODE_OPERATION_ANDOPERATIONNODE_H
#define MODEL_NODE_OPERATION_ANDOPERATIONNODE_H

#include <iostream>

#include "abstractoperationnode.h"

using namespace std;

namespace Model
{
namespace Node
{
namespace Operation
{

/**
 * @brief The AndOperationNode class
 * Operation AND
 */
class AndOperationNode: public AbstractOperationNode
{
public:
    AndOperationNode();
    int getType();
    void debugOutput(int nestingLevel);
    string debugExpression();

    AndOperationNode *clone();
};

}
}
}

#endif // MODEL_NODE_OPERATION_ANDOPERATIONNODE_H
