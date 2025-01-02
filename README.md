[EN](README.md)|[中文](README_zh-CN.md)|[한국어](README_ko-KR.md)

# WlkataC

#### wlkataC version 0.0.1

#### License: MIT

## IMPORTANT!!!

**&nbsp;&nbsp;&nbsp;&nbsp;This is a package that uses C++ to control Mirobot robotic arms, E4 robotic arms, MT4 robotic arms, sliders, conveyor belts, and other products. This package mainly communicates through serial and G-code protocols. Currently, it supports RS485 or UART communication. It should be noted that a multifunctional controller is required when using this software package, as some functions of the modified software package use a multifunctional controller. If the robotic arm is directly connected, some functions may be ineffective.**

## Description

**&nbsp;&nbsp;&nbsp;&nbsp;WlkataC is a C++package used to control Mirobot robotic arms, E4 robotic arms, MT4 robotic arms, slides, conveyors, and other products.**

**&nbsp;&nbsp;&nbsp;&nbsp;This component uses the G code protocol to communicate with the Mirobot over a serial connection.**

**&nbsp;&nbsp;&nbsp;&nbsp; The official G code instruction set and driver download can be found at the [WLkata Download Page](https://www.wlkata.com/pages/download-center).**

## Mirobot Wiring diagram(RS485)

<div style="text-align: center;">
  <img src="./img/img1.png" style="width: 50%;">
</div>

## Mirobot Example Usage(RS485)

```C++
#include <iostream>
#include <chrono>
#include <thread>
#include "serial/serial.h"
#include "wlkataC.h"

void waitForIdle(Mirobot_UART &Mirobot, const std::string &message) {
    while (Mirobot.getState() != "Idle") {
        std::cout << message << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main() {
    serial::Serial my_serial("com13", 38400);

    Mirobot_UART Mirobot;
    Mirobot_UART Mirobot_2;
    Mirobot.init(&my_serial, 1);
    Mirobot_2.init(&my_serial, 2);
    // Mirobot.message_print(true);
    // Mirobot_2.message_print(true);

    Mirobot.restart();
    Mirobot_2.restart();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    Mirobot.homing();
    Mirobot_2.homing();
    waitForIdle(Mirobot, "Homing...");
    waitForIdle(Mirobot_2, "Homing...");

    for (int i = 0; i < 5; i++) {
        Mirobot.writecoordinate(0, 0, 255, 0, 200, 0, 0, 0);
        waitForIdle(Mirobot, "Waiting for run1...");
   
        Mirobot.writecoordinate(0, 0, 255, 0, 100, 0, 0, 0);
        waitForIdle(Mirobot, "Waiting for run2...");

        Mirobot_2.writecoordinate(0, 0, 255, 0, 200, 0, 0, 0);
        waitForIdle(Mirobot_2, "Waiting for run3...");

        Mirobot_2.writecoordinate(0, 0, 255, 0, 100, 0, 0, 0);
        waitForIdle(Mirobot_2, "Waiting for run4...");
   
    }

    my_serial.close();
    // system("pause");
    return 0;
}
```

## Mirobot Wiring diagram(UART)

<div style="text-align: center;">
  <img src="./img/img2.png" style="width: 30%;">
  <img src="./img/img3.png" style="width: 50%;">
</div>

## Mirobot Example Usage(UART)

```C++
#include <iostream>
#include <chrono>
#include <thread>
#include "serial/serial.h"
#include "wlkataC.h"

void waitForIdle(Mirobot_UART &Mirobot, const std::string &message) {
    while (Mirobot.getState() != "Idle") {
        std::cout << message << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main() {
    serial::Serial my_serial("com13", 115200);

    Mirobot_UART Mirobot;
    Mirobot.init(&my_serial, -1);
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
    // system("pause");
    return 0;
}

```

## MT4 Wiring diagram(RS485)

<div style="text-align: center;">
  <img src="./img/MT4_RS485.png" style="width: 50%;">
</div>

## MT4 Example Usage(RS485)

```C++
#include <iostream>
#include <chrono>
#include <thread>
#include "serial/serial.h"
#include "wlkataC.h"

void waitForIdle(MT4_UART &MT4_1, const std::string &message) {
    while (MT4_1.getState() != "Idle") {
        std::cout << message << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
}

int main() {
    serial::Serial my_serial("com13", 38400);

    MT4_UART MT4_1;
    MT4_1.init(&my_serial, 1);
    // MT4_1.message_print(true);

    MT4_1.restart();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    MT4_1.homing();
    waitForIdle(MT4_1, "Homing...");

    for (int i = 0; i < 5; i++) {

        MT4_1.writecoordinate(0, 0, 255, 0, 200, 0);
        waitForIdle(MT4_1, "Waiting for run1...");

        MT4_1.writecoordinate(0, 0, 255, 0, 100, 0);
        waitForIdle(MT4_1, "Waiting for run2...");

    }

    my_serial.close();
    // system("pause");
    return 0;
}

```

## MT4 Wiring diagram(UART)

<div style="text-align: center;">
  <img src="./img/MT4_UART.png" style="width: 50%;">
</div>

## MT4 Example Usage(UART)

```C++
#include <iostream>
#include <chrono>
#include <thread>
#include "serial/serial.h"
#include "wlkataC.h"

void waitForIdle(MT4_UART &MT4_1, const std::string &message) {
    while (MT4_1.getState() != "Idle") {
        std::cout << message << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
}

int main() {
    serial::Serial my_serial("com13", 115200);

    MT4_UART MT4_1;
    MT4_1.init(&my_serial, -1);
    // MT4_1.message_print(true);

    MT4_1.restart();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    MT4_1.homing();
    waitForIdle(MT4_1, "Homing...");

    for (int i = 0; i < 5; i++) {
        MT4_1.writecoordinate(0, 0, 255, 0, 200, 0);
        waitForIdle(MT4_1, "Waiting for run1...");

        MT4_1.writecoordinate(0, 0, 255, 0, 100, 0);
        waitForIdle(MT4_1, "Waiting for run2...");
    }

    my_serial.close();
    // system("pause");
    return 0;
}
```

## MS4220 Wiring diagram(RS485)

<div style="text-align: center;">
  <img src="./img/MS4220.png" style="width: 50%;">
</div>

## MS4220 Example Usage(RS485)

```C++
#include <iostream>
#include <chrono>
#include <thread>
#include "serial/serial.h"
#include "wlkataC.h"

int main() {
    serial::Serial my_serial("com13", 115200);

    MS4220_UART MS4220_1;
    MS4220_1.init(&my_serial, -1);
    for (int i = 0; i < 5; i++) {
        MS4220_1.speed(100);
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        MS4220_1.speed(-100);
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        MS4220_1.speed(0);
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        }
    my_serial.close();
    // system("pause");
    return 0;
}
```

## Communication Methods

**&nbsp;&nbsp;&nbsp;&nbsp;Please contact wlkata personnel for further instructions [WLkata Download Page](https://www.wlkata.com/pages/download-center).**
