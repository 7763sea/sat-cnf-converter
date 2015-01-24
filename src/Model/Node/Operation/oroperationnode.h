#ifndef MODEL_NODE_OPERATION_OROPERATIONNODE_H
#define MODEL_NODE_OPERATION_OROPERATIONNODE_H

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
 * @brief The OrOperationNode class
 * Operation OR
 */
class OrOperationNode: public AbstractOperationNode
{
public:
    OrOperationNode();
    int getType();
    void debugOutput(int nestingLevel);
    string debugExpression();

    OrOperationNode *clone();
};

}
}
}

#endif // MODEL_NODE_OPERATION_OROPERATIONNODE_H
