#include <iostream>
#include <chrono>
#include <thread>
#include "serial/serial.h"
#include "wlkataC.h"

void waitForIdle(Mirobot_UART &Mirobot, const std::string &message) {
    while (Mirobot.getState() != "Idle") {
        std::cout << message << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
}

int main() {
    serial::Serial my_serial("com13", 38400);

    Mirobot_UART Mirobot;
    Mirobot.init(&my_serial, 1);
    // Mirobot.message_print(true);

    Mirobot.restart();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    Mirobot.homing();
    waitForIdle(Mirobot, "Homing...");

    for (int i = 0; i < 5; i++) {
        Mirobot.writecoordinate(0, 0, 255, 0, 200, 0, 0, 0);
        waitForIdle(Mirobot, "Waiting for run1...");

        Mirobot.writecoordinate(0, 0, 255, 0, 100, 0, 0, 0);
        waitForIdle(Mirobot, "Waiting for run2...");
    }

    my_serial.close(); 
    system("pause");
    return 0;
}
