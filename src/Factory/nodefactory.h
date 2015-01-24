#ifndef FACTORY_NODEFACTORY_H
#define FACTORY_NODEFACTORY_H

#include <string>

#include "../Model/Node/abstractnode.h"
#include "../Model/Node/variablenode.h"
#include "../Model/Node/Operation/andoperationnode.h"
#include "../Model/Node/Operation/equivalenceoperationnode.h"
#include "../Model/Node/Operation/notoperationnode.h"
#include "../Model/Node/Operation/oroperationnode.h"
#include "../Model/Node/Operation/xoroperationnode.h"

using namespace std;
using namespace Model::Node;
using namespace Model::Node::Operation;

namespace Factory
{

class NodeFactory
{
public:
    NodeFactory();

    /**
     * @brief returns new instance of object with specified type
     * @param type
     * @return
     */
    static AbstractNode *getInstance(AbstractNode *node);
};

}

#endif // FACTORY_NODEFACTORY_H
