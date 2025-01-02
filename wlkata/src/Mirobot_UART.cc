#include "Mirobot_UART.h"


void Mirobot_UART::init(serial::Serial *pserial, int addr)
{
    this->pserial_name = pserial;
    this->address = addr;
}
void UART::senMsg(string string_data)
{
    string message;
    if (this->address != -1)
    {
        message = "@" + std::to_string(this->address) + string_data + "\r\n";
    }
    else
    {
        message = string_data + "\r\n";
    }

    this->pserial_name->write(message);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    if (this->flag_message_io)
    {
        std::cout << "send: " << message << std::endl;
    }
}
void UART::read_data()
{
    if (this->pserial_name->available() > 0)
    {
        this->data = this->pserial_name->readline();

        if (this->flag_message_io)
        {
            std::cout << "recv: " << this->data << std::endl;
        }
    }
}
void Mirobot_UART::homing(int moda)
{
    string message = "";
    if (moda >= 0 && moda <= 10)
    {
        message = "o105=" + std::to_string(moda);
        this->senMsg(message);
    }
    else
    {
        this->senMsg("$H");
    }
    this->read_data();
}
void Mirobot_UART::runFile(string file_name, bool num)
{
    string message;
    if (num)
    {
        message = "o112" + file_name;
    }
    else
    {
        message = "o111" + file_name;
    }
    this->senMsg(message);
    this->read_data();
}
void Mirobot_UART::cancellation()
{
    this->senMsg("o117");
    this->read_data();
}
void Mirobot_UART::gripper(int num)
{
    if (num == 0)
    {
        this->senMsg("M3 S0");
    }
    else if (num == 1)
    {
        this->senMsg("M3 S40");
    }
    else if (num == 2)
    {
        this->senMsg("M3 S60");
    }
    else
    {
        this->senMsg("M3 S0");
    }
    this->read_data();
}
void Mirobot_UART::pump(int num)
{
    if (num == 0)
    {
        this->senMsg("M3 S0");
    }
    else if (num == 1)
    {
        this->senMsg("M3 S1000");
    }
    else if (num == 2)
    {
        this->senMsg("M3 S500");
    }
    else
    {
        this->senMsg("M3 S0");
    }
    this->read_data();
}
void Mirobot_UART::pwmWrite(int num)
{
    string message = "M3 S" + std::to_string(num);
    this->senMsg(message);
    this->read_data();
}
void Mirobot_UART::zero()
{
    this->senMsg("M21 G90 G00 X0 Y0 Z0 A0 B0 C00");
    this->read_data();
}
void Mirobot_UART::writecoordinate(int motion, int position, float x, float y, float z, float a, float b, float c)
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);

    oss << "X" << x << "Y" << y << "Z" << z
        << "A" << a << "B" << b << "C" << c;

    string coordinate = oss.str();

    string val_motion;
    string val_position;

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
void Mirobot_UART::speed(int num)
{
    string val_speed = "F" + std::to_string(num);
    this->senMsg(val_speed);
    this->read_data();
}
void Mirobot_UART::writeangle(int position, float x, float y, float z, float a, float b, float c)
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);

    oss << "X" << x << "Y" << y << "Z" << z
        << "A" << a << "B" << b << "C" << c;

    string val_angle = oss.str();
    string val_position;

    if (position == 0)
    {
        val_position = "G90";
    }
    else
    {
        val_position = "G91";
    }

    val_angle = "M21" + val_position + "G00" + val_angle;
    this->senMsg(val_angle);
    this->read_data();
}
void Mirobot_UART::writeexpand(int motion, int position, float d)
{
    string val_motion;
    string val_position;
    string coordinate;
    coordinate = "D" + std::to_string(d);
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
    coordinate = val_position + val_motion + coordinate;
    this->senMsg(coordinate);
    this->read_data();
}
void Mirobot_UART::restart()
{
    this->senMsg("o100");
    this->read_data();
}

Mirobot_UART::datas Mirobot_UART::getStatus()
{
    datas result;
    this->senMsg("?");
    this->read_data();
    string mess = this->data;
    std::regex e(R"(<(\w+),Angle\(ABCDXYZ\):([\d.-]+),([\d.-]+),([\d.-]+),([\d.-]+),([\d.-]+),([\d.-]+),([\d.-]+),Cartesian coordinate\(XYZ RxRyRz\):([\d.-]+),([\d.-]+),([\d.-]+),([\d.-]+),([\d.-]+),([\d.-]+),Pump PWM:([\d.-]+),Valve PWM:([\d.-]+),Motion_MODE:([\d.-]+)>)");
    std::smatch m;
    if (std::regex_search(mess, m, e))
    {
        this->data_all.data_all = m[0];
        this->data_all.state = m[1];
        this->data_all.angle_A = std::stod(m[2]);
        this->data_all.angle_B = std::stod(m[3]);
        this->data_all.angle_C = std::stod(m[4]);
        this->data_all.angle_D = std::stod(m[5]);
        this->data_all.angle_X = std::stod(m[6]);
        this->data_all.angle_Y = std::stod(m[7]);
        this->data_all.angle_Z = std::stod(m[8]);
        this->data_all.coordinate_X = std::stod(m[9]);
        this->data_all.coordinate_Y = std::stod(m[10]);
        this->data_all.coordinate_Z = std::stod(m[11]);
        this->data_all.coordinate_RX = std::stod(m[12]);
        this->data_all.coordinate_RY = std::stod(m[13]);
        this->data_all.coordinate_RZ = std::stod(m[14]);
        this->data_all.pump = std::stoi(m[15]);
        this->data_all.valve = std::stoi(m[16]);
        this->data_all.mooe = std::stoi(m[17]);
        return data_all;
    }
    else
    {
        std::cerr << "Error: Unable to parse status message." << std::endl;
        return result;
    }
}

string Mirobot_UART::getState()
{
    this->getStatus();
    return this->data_all.state;
}
float Mirobot_UART::getAngle(int num)
{
    this->getStatus();
    if (num == 1)
    {
        return this->data_all.angle_X;
    }
    else if (num == 2)
    {
        return this->data_all.angle_Y;
    }
    else if (num == 3)
    {
        return this->data_all.angle_Z;
    }
    else if (num == 4)
    {
        return this->data_all.angle_A;
    }
    else if (num == 5)
    {
        return this->data_all.angle_B;
    }
    else if (num == 6)
    {
        return this->data_all.angle_C;
    }
    else if (num == 7)
    {
        return this->data_all.angle_D;
    }
    else
    {
        return 0;
    }
}
float Mirobot_UART::getcoordinate(int num)
{
    this->getStatus();
    if (num == 1)
    {
        return this->data_all.coordinate_X;
    }
    else if (num == 2)
    {
        return this->data_all.coordinate_Y;
    }
    else if (num == 3)
    {
        return this->data_all.coordinate_Z;
    }
    else if (num == 4)
    {
        return this->data_all.coordinate_RX;
    }
    else if (num == 5)
    {
        return this->data_all.coordinate_RY;
    }
    else if (num == 6)
    {
        return this->data_all.coordinate_RZ;
    }
    else
    {
        return 0;
    }
}
int Mirobot_UART::getpump()
{
    this->getStatus();
    return this->data_all.pump;
}
int Mirobot_UART::getvalve()
{
    this->getStatus();
    return this->data_all.valve;
}
int Mirobot_UART::getmooe()
{
    this->getStatus();
    return this->data_all.mooe;
}

void UART::message_print(bool num)
{
    this->flag_message_io = num;
}