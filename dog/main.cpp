#include <iostream>

#include "watchdog_export.h"

int main(int argc, char* argv[]) {
    std::cout << "Hello, World!" << std::endl;
    dog_main(argc, argv);
    return 0;
}
