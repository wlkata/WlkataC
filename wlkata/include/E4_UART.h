#pragma once
#ifndef E4_UART_H
#define E4_UART_H

#include "Mirobot_UART.h"


class E4_UART : public Mirobot_UART
{
public:
    E4_UART() : Mirobot_UART() {}
    void writecoordinate(int motion, int position, float x, float y, float z, float a);
    void writeangle(int position, float x, float y, float z, float a);
};

#endif 