#include "falsenode.h"

using namespace Model::Node;

FalseNode::FalseNode():AbstractNode()
{
}

void FalseNode::debugOutput(int nestingLevel = 0)
{
    for(int i = 0; i < nestingLevel; i++) {
        cout <<  "-";
    }
    cout << "F" << endl;
}

FalseNode *FalseNode::clone()
{
    FalseNode *result = new FalseNode();
    cloneChildren(result);
    return result;
}

int FalseNode::getType()
{
    return this->TYPE_FALSE;
}

string FalseNode::debugExpression()
{
    return string("F");
}
