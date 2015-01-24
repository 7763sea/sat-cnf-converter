#include "satadapter.h"

using namespace Adapter;

SatAdapter::SatAdapter():
    MODE_COMMENTS(1),
    MODE_PROBLEM(2),
    MODE_EXPRESSION(3)
{
    mode = this->MODE_COMMENTS;
}

SatFileModel *SatAdapter::satToFileModel(Chain<string> *lines)
{
    SatFileModel *result = new SatFileModel();

    //Stage 1. Parse input
    ChainIterator<string> *iterator = lines->getIterator();
    while(true == iterator->hasNext()) {
        string line(iterator->next());
        if(0 == line.size())
            continue;
        if(0 == line.substr(0, 1).compare("c")) {
            this->processComment(result, line);
        } else if(0 == line.substr(0, 1).compare("p")) {
            this->processProblem(result, line);
        } else {
            this->processExpression(result, line);
        }
    }
    delete iterator;

    //Stage 2. Build expression graph
    AbstractOperationNode *rootGraphElement = evaluateExpression(result->getExpresion());
    result->setRootGraphElement(rootGraphElement);

    //Stage 3. Validate number of variables. OF number of variables is invalid, calculate it
    if(0 == result->getNumVariables()) {
        result->setNumVariables(calculateNumVariables(rootGraphElement));
    }

    return result;
}

void SatAdapter::processComment(SatFileModel *fileModel, string input)
{
    this->mode = this->MODE_COMMENTS;
    string comment(input.substr(1));

    //Trim spaces
    while((0 < comment.size()) && (0 == comment.substr(0, 1).compare(" "))) {
        comment = comment.substr(1);
    }
    while((0 < comment.size()) && (0 == comment.substr(comment.size() - 1, 1).compare(" "))) {
        comment = comment.substr(0, comment.size() - 2);
    }
    fileModel->addComment(comment);
}

void SatAdapter::processProblem(SatFileModel *fileModel, string input)
{
    this->mode = this->MODE_PROBLEM;

    string satKeyword = string("sat ");
    size_t foundIndex = input.find(satKeyword);
    if(string::npos == foundIndex)
        throw string("Invalid format of problem. 'sat ' keyword is missing.");

    string problemDetail(input.substr(foundIndex + satKeyword.size()));
    int numVariables = 0;
    numVariables = strtol(problemDetail.c_str(), NULL, 10);
    if(0 == numVariables)
        throw string("Invalid format of problem. Number of variables is incorrect.");
    fileModel->setNumVariables(numVariables);
}

void SatAdapter::processExpression(SatFileModel *fileModel, string input)
{
    this->mode = this->MODE_EXPRESSION;
    input = StringUtil::trim(input);
    fileModel->setExpression(fileModel->getExpresion() + input);
}

AbstractOperationNode *SatAdapter::evaluateExpression(string input)
{
    AbstractOperationNode *result = evaluateOperation(input, 0);
    return result;
}

AbstractOperationNode *SatAdapter::evaluateOperation(string input, int nestingLevel)
{
    string dbgMark = "";
    for(int i = 0; i <= nestingLevel; i++) {
        dbgMark = dbgMark + string("-");
    }

    AbstractOperationNode *node = NULL;
    input = StringUtil::trimBrackets(input);

    int argsPosition = 0;
    node = createOperationFromString(input, &argsPosition);
    string argumentsString = input.substr(argsPosition);

    Chain<AbstractNode*> *arguments = evaluateArguments(argumentsString, nestingLevel);

    ChainIterator<AbstractNode*> *iterator = arguments->getIterator();
    while(true == iterator->hasNext()) {
        node->addChild(iterator->next());
    }
    delete iterator;
    return node;
}

AbstractOperationNode *SatAdapter::createOperationFromString(string input, int *endPosition)
{
    int endPos = 0;
    AbstractOperationNode *result = NULL;
    input = StringUtil::trim(input);

    if(StringUtil::beginsWith(input, "*")) {
        endPos = 1;
        result = new AndOperationNode();
    } else if(StringUtil::beginsWith(input, "+")) {
        endPos = 1;
        result = new OrOperationNode();
    } else if(StringUtil::beginsWith(input, "=")) {
        endPos = 1;
        result = new EquivalenceOperationNode();
    } else if(StringUtil::beginsWith(input, "xor")) {
        endPos = 3;
        result = new XorOperationNode();
    } else if(StringUtil::beginsWith(input, "-")) {
        endPos = 1;
        result = new NotOperationNode();
    }

    //Locate position of arguments
    string remaining = input.substr(endPos);

    while(remaining.size() > 0 && (StringUtil::beginsWith(remaining.substr(0, 1), " ")
          || StringUtil::beginsWith(remaining.substr(0, 1), "\t"))) {
        //Trim spaces and tabs
        remaining = remaining.substr(1);
        endPos++;
    }
    *endPosition = endPos;
    return result;
}

Chain<AbstractNode*> *SatAdapter::evaluateArguments(string input, int nestingLevel)
{
    string dbgMark = "";
    for(int i = 0; i <= nestingLevel; i++) {
        dbgMark = dbgMark + string("-");
    }

    Chain<AbstractNode*> *result = new Chain<AbstractNode*>();
    string remainingInput = StringUtil::trimBrackets(input);
    string inputBeforeCursor = "";
    string inputAfterCursor = "";
    string cursor = "";
    unsigned int cursorPosition = 0;
    int childNestingLevel = 0;

    while(remainingInput.size() > 0) {
        remainingInput = StringUtil::trim(remainingInput);

        inputBeforeCursor = remainingInput.substr(0, cursorPosition + 1);
        inputAfterCursor = remainingInput.size() < cursorPosition + 1 ?
             "" : remainingInput.substr(cursorPosition + 1);
        cursor = remainingInput.size() == cursorPosition - 1 ? "" : remainingInput.substr(cursorPosition, 1);

        if(StringUtil::equals(cursor, "("))
            childNestingLevel++;
        else if(StringUtil::equals(cursor, ")"))
            childNestingLevel--;

        if((childNestingLevel == 0)
                && (isOperation(inputAfterCursor)
                    || StringUtil::equals(cursor, " ")
                    || StringUtil::equals(cursor, ")")
                    || StringUtil::equals(cursor, ""))) {

            AbstractNode *child = NULL;
            if(isOperation(inputBeforeCursor)) {
                child = evaluateOperation(inputBeforeCursor, nestingLevel + 1);
            } else {
                int intArgument = atoi(inputBeforeCursor.c_str());
                if(0 < intArgument) {
                    child = new VariableNode(intArgument);
                }

            }
            result->add(child);
            if(!StringUtil::equals(cursor, ""))
                cursorPosition++;
            remainingInput = remainingInput.substr(cursorPosition);
            cursorPosition = 0;
        } else {
            cursorPosition++;
        }


    }
    return result;
}

bool SatAdapter::isOperation(string input)
{
    return  StringUtil::beginsWith(input, "*") ||
        StringUtil::beginsWith(input, "+") ||
        StringUtil::beginsWith(input, "=") ||
        StringUtil::beginsWith(input, "xor") ||
        StringUtil::beginsWith(input, "-")
    ;
}

void SatAdapter::checkArgumentsNumber(AbstractOperationNode *operationNode)
{
    unsigned long long numArguments = operationNode->getChildren()->getSize();
    switch(operationNode->getType()) {
        case AbstractNode::TYPE_OPERATION_EQUIVALENCE:
            if(2 != numArguments)
                throw string("Equivalence operator must contain exactly 2 arguments");
            break;
        case AbstractNode::TYPE_OPERATION_XOR:
            if(2 != numArguments)
                throw string("XOR operator must contain exactly 2 arguments");
            break;
        case AbstractNode::TYPE_OPERATION_NOT:
            if(1 != numArguments)
                throw string("NOT operator must contain exactly 1 argument");
            break;

    }
}

int SatAdapter::calculateNumVariables(AbstractNode *node)
{
    int maxNumber = 0;
    int numberIterator = 0;

    if(AbstractNode::TYPE_VARIABLE == node->getType()) {
        VariableNode *varNode = static_cast<VariableNode*>(node);
        return varNode->getVariable();
    }

    ChainIterator<AbstractNode*> *iterator = node->getChildren()->getIterator();
    while(true == iterator->hasNext()) {
        AbstractNode *child = iterator->next();
        numberIterator = calculateNumVariables(child);
        if(numberIterator > maxNumber)
            maxNumber = numberIterator;
    }
    delete iterator;
    return maxNumber;
}
