#include "equivalenceoperationnode.h"
#include "../../../Model/Collection/chain.h"

using namespace Model::Node::Operation;
using namespace Model::Collection;

EquivalenceOperationNode::EquivalenceOperationNode(): AbstractOperationNode()
{
}

void EquivalenceOperationNode::debugOutput(int nestingLevel = 0)
{
    for(int i = 0; i < nestingLevel; i++) {
        cout <<  "-";
    }
    cout << " EQUAL " << endl;
    ChainIterator<AbstractNode*> *iterator = children->getIterator();
    while(true == iterator->hasNext()) {
        AbstractNode *child = iterator->next();
        child->debugOutput(nestingLevel + 1);
    }
    delete iterator;
}

EquivalenceOperationNode *EquivalenceOperationNode::clone()
{
    EquivalenceOperationNode *result = new EquivalenceOperationNode();
    cloneChildren(result);
    return result;
}

int EquivalenceOperationNode::getType()
{
    return this->TYPE_OPERATION_EQUIVALENCE;
}

string EquivalenceOperationNode::debugExpression()
{
    string result("(");
    ChainIterator<AbstractNode*> *iterator = children->getIterator();
    while(true == iterator->hasNext()) {
        AbstractNode *child = iterator->next();
        result += child->debugExpression();
        if(true == iterator->hasNext())
            result += " EQUAL ";
    }
    delete iterator;
    result += ")";
    return result;
}
