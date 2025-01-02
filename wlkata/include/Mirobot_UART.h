#pragma once
#ifndef Mirobot_UART_H
#define Mirobot_UART_H

#include "serial/serial.h"

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <regex>

#include <sstream>
#include <iomanip>

using std::string;

class UART
{
protected:
    serial::Serial *pserial_name;
    int address;
    string data;
    bool flag_message_io;
public:
    UART() : pserial_name(nullptr), address(0), data(), flag_message_io(false) {}
    void message_print(bool num = false);
    void senMsg(string string_data);
    void read_data();

};

class Mirobot_UART : public UART
{
private:
    struct datas
    {
        string data_all;
        string state;
        float angle_A;
        float angle_B;
        float angle_C;
        float angle_D;
        float angle_X;
        float angle_Y;
        float angle_Z;
        float coordinate_X;
        float coordinate_Y;
        float coordinate_Z;
        float coordinate_RX;
        float coordinate_RY;
        float coordinate_RZ;
        int pump;
        int valve;
        int mooe;
    } data_all;

public:
    Mirobot_UART() : UART() {}

    void init(serial::Serial *pserial, int addr);
    void homing(int moda = 8);
    void runFile(string file_name, bool num = false);
    void cancellation();
    void gripper(int num);
    void pump(int num);
    void pwmWrite(int num);
    void zero();
    void writecoordinate(int motion, int position, float x, float y, float z, float a, float b, float c);
    void speed(int num);
    void writeangle(int position, float x, float y, float z, float a, float b, float c);
    void writeexpand(int motion, int position, float d);
    void restart();
    datas getStatus();
    string getState();
    float getAngle(int num);
    float getcoordinate(int num);
    int getpump();
    int getvalve();
    int getmooe();
};

#endif