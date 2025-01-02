#include "MS4220_UART.h"

void MS4220_UART::init(serial::Serial *pserial, int addr)
{
    this->pserial_name = pserial;
    this->address = addr;
}  

void MS4220_UART::speed(int speed)
{
    int speed_val = speed;
    if (speed_val > 100){
        speed_val = 100;
    }
    else if (speed_val < -100){
        speed_val = -100;
    }
    std::string speed_str ="G6 F" + std::to_string(speed_val);
    this->senMsg(speed_str);
    this->read_data();
}