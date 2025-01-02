#pragma once
#ifndef MT4_UART_H
#define MT4_UART_H

#include "Mirobot_UART.h"

class MT4_UART : public Mirobot_UART
{
public:
    MT4_UART() : Mirobot_UART() {}
    void writecoordinate(int motion, int position, float x, float y, float z, float a);
    void writeangle(int position, float x, float y, float z, float a);
};

#endif 