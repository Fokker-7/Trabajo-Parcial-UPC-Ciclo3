#include "Console.h"
#include <iostream>

#ifdef _WIN32
    #include <cstdlib>
#else
    #include <cstdlib>
#endif

namespace Console {

    void clear() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    }

    void pause() {
        std::cout << "Presiona Enter para continuar...";
        std::cin.get();
    }
}