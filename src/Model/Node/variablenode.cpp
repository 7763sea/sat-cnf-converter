#include "variablenode.h"

using namespace Model::Node;

VariableNode::VariableNode(int variable):AbstractNode()
{
    this->variable = variable;
}

int VariableNode::getVariable()
{
    return variable;
}

void VariableNode::debugOutput(int nestingLevel = 0)
{
    for(int i = 0; i < nestingLevel; i++) {
        cout <<  "-";
    }
    cout << " Variable (" << variable << ")" << endl;
}




VariableNode *VariableNode::clone()
{
    VariableNode *result = new VariableNode(getVariable());
    cloneChildren(result);
    return result;
}

int VariableNode::getType()
{
    return this->TYPE_VARIABLE;
}

string VariableNode::debugExpression()
{
    string stringVar;
    ostringstream convert;
    convert << variable;
    stringVar = convert.str();
    return string("x") + stringVar;
}
