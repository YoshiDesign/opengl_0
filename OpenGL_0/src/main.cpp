#include <iostream>
#include <exception>
#include "Game1.h"

#define LOG(x) std::cout << x << std::endl;

int main(void)
{
    Game1 app{};

    try {

        app.run();

    }
    catch (const std::exception& e)
    {
        LOG(e.what());
        return -1;
    }

    return 0;

}
