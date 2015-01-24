#ifndef MODEL_NODE_OPERATION_EQUIVALENCEOPERATIONNODE_H
#define MODEL_NODE_OPERATION_EQUIVALENCEOPERATIONNODE_H

#include <iostream>

#include "abstractoperationnode.h"

using namespace std;

namespace Model
{
namespace Node
{
namespace Operation
{

class EquivalenceOperationNode: public AbstractOperationNode
{
public:
    EquivalenceOperationNode();
    int getType();
    void debugOutput(int nestingLevel);
    string debugExpression();

    EquivalenceOperationNode *clone();
};

}
}
}

#endif // MODEL_NODE_OPERATION_EQUIVALENCEOPERATIONNODE_H
