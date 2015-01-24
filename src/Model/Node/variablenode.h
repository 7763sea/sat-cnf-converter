#ifndef MODEL_NODE_VARIABLENODE_H
#define MODEL_NODE_VARIABLENODE_H

#include <iostream>
#include <sstream>
#include "abstractnode.h"

using namespace std;

namespace Model
{
namespace Node
{

/**
 * @brief The VariableNode class
 * Contains information about variable from expression
 */
class VariableNode: public AbstractNode
{
public:
    VariableNode(int variable);

    int getVariable();
    void debugOutput(int nestingLevel);
    string debugExpression();

    int getType();
    VariableNode *clone();
protected:
    int variable;
};

}
}

#endif // MODEL_NODE_VARIABLENODE_H
