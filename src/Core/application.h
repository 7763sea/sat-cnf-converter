#ifndef CORE_APPLICATION_H
#define CORE_APPLICATION_H

#include "../IO/inputreader.h"
#include "../IO/inputfilereader.h"
#include "../IO/outputfilewriter.h"
#include "../Adapter/satadapter.h"
#include "../Adapter/cnfadapter.h"
#include "../Model/filemodel.h"
#include "../Model/satfilemodel.h"
#include "../Model/cnffilemodel.h"
#include "../Model/Collection/chain.h"
#include "../Model/Node/Operation/abstractoperationnode.h"
#include "../Translator/sattocnftranslator.h"
#include "../Exception/expressionequalstrueexception.h"
#include "../Exception/expressionequalsfalseexception.h"

using namespace std;
using namespace Model;
using namespace Model::Collection;
using namespace Model::Node::Operation;
using namespace Translator;
using namespace Exception;

namespace Core
{

/**
 * @brief The Application class
 * Main class. Represents program
 */
class Application
{
public:
    explicit Application(int argc, char *argv[]);
    int execute();

protected:
    Chain<string> *arguments;
    bool debugMode;

    /**
     * @brief inputFileName name of input file
     */
    string *inputFileName;

    /**
     * @brief reads console input into array of strings
     * @return
     */
    Chain<string> *readInput();

    /**
     * @brief converts text input into file model with operation graph
     * @param input
     * @return
     */
    SatFileModel *convertInput(Chain<string> *input);

    /**
     * @brief translates graph into CNF
     * @return
     */
    AbstractNode *translateGraph(SatFileModel *fileModel);

    /**
     * @brief Translates processed data to CNF file model
     * @param originalFileModel
     * @param graph
     * @return
     */
    CnfFileModel *buildCnfFileModel(SatFileModel *originalFileModel, AbstractNode *graph);

    /**
     * @brief translates CNF file model to array of strings for output
     * @param cnfFileModel
     * @return
     */
    Chain<string> *translateCnfModelToStrings(CnfFileModel *cnfFileModel);

    /**
     * @brief Prints CNF file to standard output
     * @param result
     */
    void outputResult(Chain<string> *result);
};

}



#endif // CORE_APPLICATION_H
