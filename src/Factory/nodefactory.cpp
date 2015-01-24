#include "nodefactory.h"

using namespace Factory;

NodeFactory::NodeFactory()
{
}

AbstractNode *NodeFactory::getInstance(AbstractNode *node)
{
    VariableNode *v = NULL;
    switch(node->getType()) {
        case AbstractNode::TYPE_VARIABLE:
            v = static_cast<VariableNode*>(node);
            return new VariableNode(v->getVariable());
        case AbstractNode::TYPE_OPERATION_AND:
            return new AndOperationNode();
        case AbstractNode::TYPE_OPERATION_OR:
            return new OrOperationNode();
        case AbstractNode::TYPE_OPERATION_NOT:
            return new NotOperationNode();
        case AbstractNode::TYPE_OPERATION_XOR:
            return new XorOperationNode();
        case AbstractNode::TYPE_OPERATION_EQUIVALENCE:
            return new EquivalenceOperationNode();
        default:
            throw string("NodeFactory: Operation was ont found");
    }
}
