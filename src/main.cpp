#include "Core/application.h"

using namespace Core;

int main(int argc, char *argv[])
{
    Application *application = new Application(argc, argv);
    return application->execute();
}

