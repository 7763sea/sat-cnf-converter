#include "abstractnode.h"
#include "../Collection/chain.h"
#include "../Collection/chainiterator.h"

using namespace Model::Node;
using namespace Model::Collection;

AbstractNode::AbstractNode()
{
    children = new Chain<AbstractNode*>();
}

AbstractNode::~AbstractNode()
{
    ChainIterator<AbstractNode*> *iterator = children->getIterator();
    while(true == iterator->hasNext()) {
        AbstractNode *node = iterator->next();
        delete node;
        iterator->removeCurrent();
    }
    delete iterator;
    delete children;
}

AbstractNode *AbstractNode::getParent()
{
    return parent;
}

void AbstractNode::setParent(AbstractNode *parent)
{
    this->parent = parent;
}

Chain<AbstractNode*> *AbstractNode::getChildren()
{
    return children;
}

void AbstractNode::addChild(AbstractNode *child)
{
    children->add(child);
}

void AbstractNode::cloneChildren(AbstractNode *dest)
{
    ChainIterator<AbstractNode*> *iterator = children->getIterator();
    int i = 1;
    while(true == iterator->hasNext()) {
        AbstractNode *child = iterator->next();
        AbstractNode *clonedChild = child->clone();
        dest->addChild(clonedChild);
        i++;
    }
    delete iterator;
}

int AbstractNode::getType()
{
    return this->TYPE_ABSTRACT;
}

bool AbstractNode::consistsFromSimpleElements()
{
    ChainIterator<AbstractNode*> *iterator = children->getIterator();
    while(true == iterator->hasNext()) {
        AbstractNode *child = iterator->next();
        if(AbstractNode::TYPE_VARIABLE == child->getType())
            continue;
        if(AbstractNode::TYPE_OPERATION_NOT == child->getType()) {
            AbstractNode *notChild = child->getChildren()->getFirstElement();
            if(AbstractNode::TYPE_VARIABLE == notChild->getType())
                continue;
        }
        return false;
    }
    return true;
}

bool AbstractNode::isDisjunctionOfComplexConjunctions()
{
    if(AbstractNode::TYPE_OPERATION_OR != getType())
        return false; //not a disjunction

    int numOperations = 0;
    ChainIterator<AbstractNode*> *iterator = children->getIterator();
    while(true == iterator->hasNext()) {
        AbstractNode *child = iterator->next(); //Get an element which might be conjunction

        //Disjunction contains elements which are not parts of conjunction
        if(!((AbstractNode::TYPE_VARIABLE == child->getType()) ||
               (AbstractNode::TYPE_OPERATION_AND == child->getType()) ||
               (AbstractNode::TYPE_OPERATION_NOT == child->getType()))) {
            return false;
        }

        if(AbstractNode::TYPE_OPERATION_AND == child->getType()) {
            if(child->getChildren()->getSize() > 1)
                numOperations++;
        }

        if(AbstractNode::TYPE_OPERATION_NOT == child->getType()) {
            AbstractNode *grandChild = child->getChildren()->getFirstElement();
            if(AbstractNode::TYPE_VARIABLE != grandChild->getType()) {
                return false; //Contains complex NOT operation
            }
        }

    }
    return (numOperations > 0);
}

bool AbstractNode::isSingleVariable(){
    if(!(AbstractNode::TYPE_VARIABLE == getType() ||
             AbstractNode::TYPE_OPERATION_NOT == getType()))
        return false;

    AbstractNode *var = NULL;
    if(AbstractNode::TYPE_VARIABLE == getType()) {
        var = this;
    } else if(AbstractNode::TYPE_OPERATION_NOT == getType()) {
        var = children->getFirstElement();
    }
    if(AbstractNode::TYPE_VARIABLE == var->getType())
        return true;

    return false;
}
