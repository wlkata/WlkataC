#include "E4_UART.h"

void E4_UART::writecoordinate(int motion, int position, float x, float y, float z, float a)
{
    string val_motion;
    string val_position;
    string coordinate;
    coordinate = "X" + std::to_string(x) + "Y" + std::to_string(y) + "Z" + std::to_string(z) + "A" + std::to_string(a) ;
    if (motion == 0)
    {
        val_motion = "G00";
    }
    else if (motion == 1)
    {
        val_motion = "G01";
    }
    else if (motion == 2)
    {
        val_motion = "G05";
    }
    else
    {
        val_motion = "G00";
    }

    if (position == 0)
    {
        val_position = "G90";
    }
    else if (position == 1)
    {
        val_position = "G91";
    }
    else
    {
        val_position = "G90";
    }
    coordinate = "M20" + val_position + val_motion + coordinate;
    this->senMsg(coordinate);
    this->read_data();
}

void E4_UART::writeangle(int position, float x, float y, float z, float a)
{
    string val_position;
    string val_angle;

    val_angle = "X" + std::to_string(x) + "Y" + std::to_string(y) + "Z" + std::to_string(z) + "A" + std::to_string(a) ;
    if (position == 0)
    {
        val_position = "G90";
    }
    else if (position == 0)
    {
        val_position = "G91";
    }
    else
    {
        val_position = "G90";
    }
    val_angle = "M21" + val_position + "G00" + val_angle;
    this->senMsg(val_angle);
    this->read_data();
}