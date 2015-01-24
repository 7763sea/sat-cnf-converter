#ifndef TRANSLATOR_SATTOCNFTRANSLATOR_H
#define TRANSLATOR_SATTOCNFTRANSLATOR_H

#include <math.h>

#include "../Model/Collection/chain.h"
#include "../Model/Collection/chainiterator.h"
#include "../Model/Node/Operation/abstractoperationnode.h"
#include "../Model/Node/Operation/oroperationnode.h"
#include "../Model/Node/Operation/andoperationnode.h"
#include "../Model/Node/Operation/notoperationnode.h"
#include "../Model/Node/truenode.h"
#include "../Model/Node/falsenode.h"
#include "../Utils/translationutil.h"
#include "../Factory/nodefactory.h"
#include "../Exception/expressionequalstrueexception.h"
#include "../Exception/expressionequalsfalseexception.h"

using namespace Model::Collection;
using namespace Model::Node::Operation;
using namespace Factory;
using namespace Utils;
using namespace Exception;

namespace Translator
{

/**
 * @brief Translates SAT graph to 'disjunction of conjuctions' graph
 */
class SatToCnfTranslator
{
public:
    SatToCnfTranslator(bool debugMode);

    /**
     * @brief translate input graph. Entry point
     * @param input
     * @return
     */
    AbstractNode *translate(AbstractNode *input);

protected:

    AbstractNode *originalGraph;
    AbstractNode *translatedGraph;

    /**
     * @brief how much updates was commited after last iteration
     */
    int numLastIterationUpdates;

    bool debugMode;

    /**
     * @brief Converts operations like 'equivalence' and 'xor'
     * into conjunction ((NOT x1 OR x2) AND (x1 OR NOT x2))
     */
    AbstractNode *convertComplexToConjunction(AbstractNode *parentElement, int nestingLevel);

    /**
     * @brief translated "a EQUIVAVENT b" to "(NOT x1 OR x2) AND (x1 OR NOT x2)"
     * @param parentElement
     * @param childElement
     * @param childElementIndex
     */
    AbstractNode *translateEquivalence(AbstractNode *element);


    /**
     * @brief translated "a XOR b" to "(NOT x1 OR NOT x2) AND (x1 OR x2)"
     * @param parentElement
     * @param childElement
     * @param childElementIndex
     */
    AbstractNode *translateXor(AbstractNode *element);

    /**
     * @brief eliminates NOT elements applied to another operations
     * @param element
     * @return
     */
    AbstractNode *eliminateComplexNotOperators(AbstractNode *element, unsigned long long *numModifications);

    /**
     * @brief perform operations for optimization of graph
     * @param element
     * @param numModifications
     * @return
     */
    AbstractNode *optimize(AbstractNode *element, unsigned long long *numModifications);

    AbstractNode *translateDnfToCnf(AbstractNode *element, unsigned long long *numModifications);

    AbstractNode *optimizeAnd(AbstractNode *element, unsigned long long *numModifications);

    AbstractNode *optimizeOr(AbstractNode *element, unsigned long long *numModifications);
};

}

#endif // TRANSLATOR_SATTOCNFTRANSLATOR_H
