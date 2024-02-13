#include <iostream>
#include <thread>

#include "timer.h"
#include "watchdog_export.h"

int main(int argc, char* argv[]) {
    std::cout << "Hello, World!" << std::endl;

    const Timer timer(std::chrono::seconds(1), [] { std::cout << "Hello, Timer!" << std::endl; });
    const Timer timer1(std::chrono::seconds(0), [=] { dog_main(argc, argv); });

    timer.start();
    timer1.start();

    while (timer.is_running() || timer1.is_running()) {
        std::this_thread::sleep_for(std::chrono::seconds(60));
    }
    return 0;
}
