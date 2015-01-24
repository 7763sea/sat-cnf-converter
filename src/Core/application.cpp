#include "application.h"

using namespace std;
using namespace Core;
using namespace IO;
using namespace Model;
using namespace Adapter;

Application::Application(int argc, char *argv[])
{
    //Initialize variables
    debugMode = false;
    inputFileName = NULL;
    //Collect arguments
    this->arguments = new Chain<string>();
    for(int i = 1; i < argc; i++) {
        string strIterator(argv[i]);
        this->arguments->add(strIterator);
    }

    //Process arguments
    ChainIterator<string> *iterator = arguments->getIterator();

    while(true == iterator->hasNext()) {
        string next = iterator->next();
        string argument(next);

        //Set debug mode
        if(0 == argument.compare("--debug"))
            this->debugMode = true;
        else
            inputFileName = new string(argument);        
    }
    delete iterator;
}

int Application::execute()
{
    try {
        Chain<string> *input = readInput();
        SatFileModel *initialModel = convertInput(input);
        AbstractNode *translatedGraph = translateGraph(initialModel);
        CnfFileModel *outputModel = buildCnfFileModel(initialModel, translatedGraph);
        Chain<string> *output = translateCnfModelToStrings(outputModel);
        outputResult(output);

        cout << "Operation complete." << endl;
    } catch(ExpressionEqualsTrueException*) {
        cout << "WARNING: The whole expression equals TRUE." << endl;
        return -1;
    } catch(ExpressionEqualsFalseException*) {
        cout << "WARNING: The whole expression equals FALSE." << endl;
        return -2;
    } catch(bad_alloc) {
        cout << "Allocation error: unable to allocate enough memory for this operation" << endl;
        return -1001;
    } catch(exception e) {
        cout << "System error occured: " << endl << e.what() << endl;
        return -1000;
    } catch(string stringException) {
        cout << "Logical error occured: " << endl << stringException << endl;
        return -2000;
    }

    return 0;
}

Chain<string> *Application::readInput()
{

    if(NULL == inputFileName)
        throw string("Usage: (executable name)[ --debug] input_file.sat");

    //InputReader *inputReader = new InputReader();
    InputFileReader *inputReader = new InputFileReader(*inputFileName);
    Chain<string> *input = inputReader->read();
    delete inputReader;    

    if(true == this->debugMode) {
        cout << "Received contents of input file:" << endl;
        ChainIterator<string> *iterator = input->getIterator();
        while(true == iterator->hasNext()) {
            string inputLine(iterator->next());
            cout << inputLine << endl;
        }
        delete iterator;
    }

    return input;
}

SatFileModel *Application::convertInput(Chain<string> *input)
{
    SatAdapter *adapter = new SatAdapter();
    SatFileModel *result = adapter->satToFileModel(input);
    delete adapter;

    if(true == this->debugMode) {
        cout << endl << "Graph structure BEFORE translation:" << endl;
        result->debugOutput();
    }


    return result;
}

AbstractNode *Application::translateGraph(SatFileModel *fileModel)
{
    SatToCnfTranslator *translator = new SatToCnfTranslator(debugMode);
    AbstractNode *result = translator->translate(fileModel->getRootGraphElement());
    delete translator;
    if(true == this->debugMode) {
        cout << endl << "Graph structure AFTER translation:" << endl;
        result->debugOutput(0);
        cout << endl << result->debugExpression() << endl;
    }
    return result;
}

CnfFileModel *Application::buildCnfFileModel(SatFileModel *originalFileModel, AbstractNode *graph)
{
    CnfFileModel *result = new CnfFileModel();

    ChainIterator<string> *iterator = originalFileModel->getComments()->getIterator();
    while(true == iterator->hasNext()) {
        result->addComment(iterator->next());
    }

    result->setNumVariables(originalFileModel->getNumVariables());
    result->setNumClauses(graph->getChildren()->getSize());
    result->setRootGraphElement(graph);

    return result;
}

Chain<string> *Application::translateCnfModelToStrings(CnfFileModel *cnfFileModel)
{
    CnfAdapter *adapter = new CnfAdapter();
    Chain<string> *result = adapter->fileModelToCnf(cnfFileModel);
    delete adapter;

    return result;
}

void Application::outputResult(Chain<string> *result)
{
    OutputFileWriter *writer = new OutputFileWriter();
    writer->write(*inputFileName, result);
    delete writer;
}
