#ifndef ADAPTER_SATADAPTER_H
#define ADAPTER_SATADAPTER_H

#include <string>
#include <stdlib.h>

#include "../Model/satfilemodel.h"
#include "../Utils/stringutil.h"
#include "../Model/Node/abstractnode.h"
#include "../Model/Collection/chain.h"
#include "../Model/Node/Operation/abstractoperationnode.h"
#include "../Model/Node/Operation/andoperationnode.h"
#include "../Model/Node/Operation/oroperationnode.h"
#include "../Model/Node/Operation/notoperationnode.h"
#include "../Model/Node/Operation/xoroperationnode.h"
#include "../Model/Node/Operation/equivalenceoperationnode.h"
#include "../Model/Node/variablenode.h"

using namespace std;
using namespace Model;
using namespace Model::Collection;
using namespace Model::Node;
using namespace Model::Node::Operation;
using namespace Utils;

namespace Adapter
{

/**
 * @brief The SatAdapter class
 * Converter for SAT format
 */
class SatAdapter
{
public:
    /**
     * @brief MODE_COMMENTS regime when program reads comment from input data
     */
    const int MODE_COMMENTS;

    /**
     * @brief MODE_COMMENTS regime when program reads problem from input data
     */
    const int MODE_PROBLEM;
    /**
     * @brief MODE_EXPRESSION regime when program parses SAT expression
     */
    const int MODE_EXPRESSION;

    SatAdapter();

    /**
     * @brief Convert array of lines(strings) in SAT format to file model
     * @param lines
     * @return
     */
    SatFileModel *satToFileModel(Chain<string> *lines);

protected:
    /**
     * @brief mode current mode
     */
    int mode;

    /**
     * @brief processComment process comment line
     * @param fileModel
     * @param input
     */
    void processComment(SatFileModel *fileModel, string input);

    /**
     * @brief processComment process line which contains information about problem
     * @param fileModel
     * @param input
     */
    void processProblem(SatFileModel *fileModel, string input);

    /**
     * @brief processComment process line which contains expression
     * @param fileModel
     * @param input
     */
    void processExpression(SatFileModel *fileModel, string input);

    /**
     * @brief evaluateExpression Evaluates an expression and builds operation graph
     * @param input
     * @return
     */
    AbstractOperationNode *evaluateExpression(string input);

    /**
     * @brief evaluateExpression Evaluates operation (AND, OR, ...)
     * @param input
     * @return
     */
    AbstractOperationNode *evaluateOperation(string input, int nestingLevel);

    /**
     * @brief createOperationFromString create operation without arguments
     * @param input
     * @param endPosition position of next element after operation (usually it is set of arguments or single argument)
     * @return
     */
    AbstractOperationNode *createOperationFromString(string input, int *endPosition);

    /**
     * @brief evaluateExpression Evaluates operation arguments (variables or another operations)
     * @param input
     * @return
     */
    Chain<AbstractNode*> *evaluateArguments(string input, int nestingLevel);

    /**
     * @brief isOperation checks if input string represents an operation (begins with operation character)
     * @param input
     * @return
     */
    bool isOperation(string input);

    /**
     * @brief checks is operation contains apropriate number of arguments
     * @param operationNode
     */
    void checkArgumentsNumber(AbstractOperationNode *operationNode);

    /**
     * @brief Finds a variable with maximum number to calculate num of variables
     * @param node
     * @return
     */
    int calculateNumVariables(AbstractNode *node);
};

}

#endif // ADAPTER_SATADAPTER_H
