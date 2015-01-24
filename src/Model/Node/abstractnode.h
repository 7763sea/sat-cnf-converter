#ifndef MODEL_NODE_ABSTRACTNODE_H
#define MODEL_NODE_ABSTRACTNODE_H

#include <iostream>

using namespace std;

namespace Model
{
    namespace Collection
    {
        template <typename T>
        class Chain;
    }

namespace Node
{

using namespace Model::Collection;

/**
 * @brief The AbstractNode class
 * Abstract node. Possible implementations are operations and variables
 */
class AbstractNode
{
public:
    enum Type {
        TYPE_ABSTRACT, TYPE_VARIABLE, TYPE_OPERATION_ABSTRACT,
        TYPE_OPERATION_AND, TYPE_OPERATION_NOT, TYPE_OPERATION_OR,
        TYPE_OPERATION_XOR, TYPE_OPERATION_EQUIVALENCE, TYPE_TRUE,
        TYPE_FALSE
    };

    AbstractNode();
    virtual ~AbstractNode();

    AbstractNode *getParent();
    void setParent(AbstractNode *parent);
    Chain<AbstractNode*> *getChildren();
    void addChild(AbstractNode *child);

    /**
     * @brief getType returns type of node
     * @return
     */
    virtual int getType();

    virtual void debugOutput(int nestingLevel = 0) = 0;
    virtual string debugExpression() = 0;

    /**
     * @brief makes a copy of graph with all children
     * @return
     */
    virtual AbstractNode *clone() = 0;

    /**
     * @brief checks if node is a single variable or NOT operation applied to a single variable
     * @return
     */
    bool isSingleVariable();

    /**
     * @brief checks if element consists only from variables and NOT elements applied to variables
     * @return
     */
    bool consistsFromSimpleElements();

    /**
     * @brief checks of operation is disjunction of conjunctions where conjunctions are also some operations
     * @return
     */
    bool isDisjunctionOfComplexConjunctions();

protected:
    AbstractNode *parent;
    Chain<AbstractNode*> *children;

    /**
     * @brief clones children nodes srom src to desrs
     * @param src
     * @param dest
     */
    void cloneChildren(AbstractNode *dest);
};

}
}

#endif // MODEL_NODE_ABSTRACTNODE_H
