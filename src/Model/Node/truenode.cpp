#include "truenode.h"

using namespace Model::Node;

TrueNode::TrueNode():AbstractNode()
{
}

void TrueNode::debugOutput(int nestingLevel = 0)
{
    for(int i = 0; i < nestingLevel; i++) {
        cout <<  "-";
    }
    cout << "T" << endl;
}



TrueNode *TrueNode::clone()
{
    TrueNode *result = new TrueNode();
    cloneChildren(result);
    return result;
}

int TrueNode::getType()
{
    return this->TYPE_TRUE;
}

string TrueNode::debugExpression()
{
    return string("T");
}
