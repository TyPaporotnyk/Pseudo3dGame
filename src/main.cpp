#include "Core/Engine.h"

#include "Managers.h"


int main()
{
    Core::Managers::initialize();

    Engine engine;
    engine.run();

    return 0;
}
