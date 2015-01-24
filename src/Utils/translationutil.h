#ifndef UTILS_TRANSLATIONUTIL_H
#define UTILS_TRANSLATIONUTIL_H

#include <iostream>

#include "../Model/Node/abstractnode.h"
#include "../Factory/nodefactory.h"
#include "../Utils/stringutil.h"
#include "../Model/Node/truenode.h"
#include "../Model/Node/falsenode.h"

using namespace std;
using namespace Model::Node;
using namespace Factory;
using namespace Utils;

namespace Utils
{

class TranslationUtil
{
public:
    TranslationUtil();

    static AbstractNode *applyDeMorgansLaws(AbstractNode *operation);

    /**
     * @brief translates operations with multiple arguments to set of operations with two arguments
     * @param operation
     * @return
     */
    static AbstractNode *convertToBinaryTree(AbstractNode *operation);

    /**
     * @brief removes duplications in children elements
     * @param node
     * @return
     */
    static AbstractNode *removeDuplications(AbstractNode *node, bool forceCheck, unsigned long long *numModifications);

    /**
     * @brief sorts children (example: { 1; -1; 2; 3; -3 })
     * @param node
     * @return
     */
    static AbstractNode *sortChildren(AbstractNode *node);

    /**
     * @brief Eliminates opposite members (example: (x4 and -4) = FALSE, (4 OR -4 = TRUE))
     * @param node
     * @return
     */
    static AbstractNode *eliminateOppositeMembers(AbstractNode *node, unsigned long long *numModifications);

    /**
     * @brief eliminates member variables like TRUE/FALSE
     * @param node
     * @return
     */
    static AbstractNode *eliminateMembersWithConstants(AbstractNode *node, unsigned long long *numModifications);
};

}

#endif // UTILS_TRANSLATIONUTIL_H
