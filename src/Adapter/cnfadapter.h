#ifndef ADAPTER_CNFADAPTER_H
#define ADAPTER_CNFADAPTER_H

#include <string>

#include "../Model/cnffilemodel.h"
#include "../Model/Collection/chain.h"
#include "../Model/Node/variablenode.h"
#include "../Model/Node/Operation/notoperationnode.h"
#include "../Utils/stringutil.h"
#include "../Utils/datetimeutil.h"

using namespace std;
using namespace Model;
using namespace Model::Collection;
using namespace Model::Node;
using namespace Model::Node::Operation;
using namespace Utils;

namespace Adapter
{

class CnfAdapter
{
public:
    CnfAdapter();
    Chain<string> *fileModelToCnf(CnfFileModel *model);
};

}

#endif // ADAPTER_CNFADAPTER_H
