#include "cnfadapter.h"

using namespace Adapter;

CnfAdapter::CnfAdapter()
{
}

Chain<string> *CnfAdapter::fileModelToCnf(CnfFileModel *model)
{
    Chain<string> *result = new Chain<string>();

    //Add time of generation
    string currentTime = DateTimeUtil::getCurrentTime();
    result->add(string("c Generated at: ") + currentTime);

    unsigned long long commentsNum = model->getComments()->getSize();
    if(0 < commentsNum) {
        result->add(string("c Original comments: "));
    }
    ChainIterator<string> *iterator = model->getComments()->getIterator();
    while(true == iterator->hasNext()) {
        result->add(string("c ") + iterator->next());
    }
    delete iterator;

    //Add task description
    result->add(string("p cnf ") +
        StringUtil::intToString(model->getNumVariables()) + string(" ") +
        StringUtil::intToString(model->getNumClauses()));

    AbstractNode *conjunctionNode = model->getRootGraphElement();
    ChainIterator<AbstractNode*> *nodeIterator = conjunctionNode->getChildren()->getIterator();
    while(true == nodeIterator->hasNext()) {
        AbstractNode *disjunctionNode = nodeIterator->next();
        string resultString;
        if(disjunctionNode->isSingleVariable()) {
            //Element is variable or disjunction of a variable: just add variable to list

            string stringDisjunctionElement(""); //contains text representation of a single element (examples: x, !x)
            if(AbstractNode::TYPE_VARIABLE == disjunctionNode->getType()) {
                VariableNode *variableNode = static_cast<VariableNode*>(disjunctionNode);
                stringDisjunctionElement = StringUtil::intToString(variableNode->getVariable());
            } else { //Otherwise it is NOT element which contains some variable
                NotOperationNode *notNode = static_cast<NotOperationNode*>(disjunctionNode);
                VariableNode *variableNode = static_cast<VariableNode*>(notNode->getChildren()->getFirstElement());
                stringDisjunctionElement = string("-") + StringUtil::intToString(variableNode->getVariable());
            }

            //result->add(stringDisjunctionElement);
            resultString = stringDisjunctionElement;
        } else {
            string disjunctionsString(""); //Contains a line with disjunction variables
            //Element is array of variables (disjunction) - translate disjunction to text representation

            ChainIterator<AbstractNode*> *disjunctionIterator = disjunctionNode->getChildren()->getIterator();
            while(true == disjunctionIterator->hasNext()) {
                AbstractNode *disjunctionElement = disjunctionIterator->next();
                string stringDisjunctionElement(""); //contains text representation of a single element (examples: x, !x)
                if(AbstractNode::TYPE_VARIABLE == disjunctionElement->getType()) {
                    VariableNode *variableNode = static_cast<VariableNode*>(disjunctionElement);
                    stringDisjunctionElement = StringUtil::intToString(variableNode->getVariable());
                } else { //Otherwise it is NOT element which contains some variable
                    NotOperationNode *notNode = static_cast<NotOperationNode*>(disjunctionElement);
                    VariableNode *variableNode = static_cast<VariableNode*>(notNode->getChildren()->getFirstElement());
                    stringDisjunctionElement = string("-") + StringUtil::intToString(variableNode->getVariable());
                }
                if(true == disjunctionIterator->hasNext())
                    stringDisjunctionElement += string(" ");

                disjunctionsString += stringDisjunctionElement;
            }
            delete disjunctionIterator;

            //result->add(disjunctionsString);
            resultString = disjunctionsString;
        }
        resultString += string(" 0");
        result->add(resultString);
    }
    delete nodeIterator;

    return result;
}
