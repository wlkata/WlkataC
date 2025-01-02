#pragma once
#ifndef MS4220_UART_H
#define MS4220_UART_H

#include "Mirobot_UART.h"

class MS4220_UART : public UART
{
public:
    MS4220_UART() : UART() {}
    void init(serial::Serial *pserial, int addr);
    void speed(int speed);
};

#endif 