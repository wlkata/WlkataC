[EN](README.md)|[中文](README_zh-CN.md)|[한국어](README_ko-KR.md)

# WlkataC

#### wlkataC 版本 0.1.0

#### 许可证: MIT

## 重要提示!!!

**&nbsp;&nbsp;&nbsp;&nbsp;这是一个使用 C++ 控制 Mirobot 机械臂、E4 机械臂、MT4 机械臂、MS4220步进电机控制器，Haro380机械臂及其他产品的软件包。该软件包主要通过串口和 G 代码协议进行通信。目前支持 RS485 或 UART 通信。需要注意的是，使用此软件包时需要一个多功能控制器，因为修改后的软件包中的某些功能需要使用多功能控制器。如果直接连接机械臂，某些功能可能无效。**

## 描述

**&nbsp;&nbsp;&nbsp;&nbsp;WlkataC 是一个用于控制 Mirobot 机械臂、E4 机械臂、MT4 机械臂、MS4220步进电机控制器，Haro380机械臂及其他产品的 C++ 软件包。**

**&nbsp;&nbsp;&nbsp;&nbsp;该组件使用 G 代码协议通过串口与 Mirobot 进行通信。**

**&nbsp;&nbsp;&nbsp;&nbsp;官方 G 代码指令集和驱动程序下载可以在 [WLkata 下载页面](https://cn.wlkata.com/cn_downloads_wlkata.php) 找到。**

## 支持设备

- Mirobot（UART/RS485）
- MT4（UART/RS485）
- E4（UART/RS485）
- Haro380（UART/RS485）
- MS4220 步进电机控制器（RS485）

## 构建与依赖

- **依赖**:
  - CMake ≥ 3.22
  - C++23 编译器
  - 串口库位于仓库 `serial/` 目录中（无需单独安装）
- **Windows** 需链接 `SetupAPI`（项目已在 `CMakeLists.txt` 中通过 `target_link_libraries(wlkata SetupAPI)` 指定）。
- **Linux** 请在 `CMakeLists.txt` 中注释掉 `SetupAPI` 链接行（文件内已给出注释指引）。

构建示例：

```bash
mkdir build && cd build
cmake ..
# 方式一（通用，跨平台）：
cmake --build . -j
# 方式二（若生成器是 Makefiles）：
make -j
# 方式三（Windows 使用 VS 生成器）：
# cmake --build . --config Release -j
```

生成的可执行程序为 `build/wlkata`（Windows 为 `wlkata.exe`）。

## 串口与地址说明

- 串口名：Windows 使用 `COMx`，Linux 使用 `/dev/ttyUSBx` 或 `/dev/ttyACMx`。
- 波特率：
  - RS485 示例通常为 `38400`
  - UART 示例通常为 `115200`
- 设备地址：
  - RS485 多机通信使用从站地址（整数，如 `1`、`2`、`10` 等）
  - 直连 UART 单机可使用 `-1` 代表直连
  - `init(serial, addr, block_flag, message_flag)`：
    - `block_flag=true` 常用命令会阻塞等待空闲态
    - `message_flag=true` 输出底层通讯日志

## Mirobot 接线图 (RS485)

<div style="text-align: center;">
  <img src="./img/img1.png" style="width: 50%;">
</div>

## Mirobot 示例用法 (RS485)

```C++
#include <iostream>
#include <chrono>
#include <thread>
#include "serial/serial.h"
#include "wlkataC.h"

int main() {
    serial::Serial my_serial("com13", 38400);

    Mirobot_UART Mirobot;
    Mirobot_UART Mirobot_2;
    Mirobot.init(&my_serial, 1,true,true);
    Mirobot_2.init(&my_serial, 2,true,true);
    // Mirobot.message_print(true);
    // Mirobot_2.message_print(true);

    Mirobot.homing();
    Mirobot_2.homing();
    Mirobot_UART::CoordinateParams params;
    params.x = 255;
    params.y = 50;
    params.z = 200;
    params.a = 20;
    params.b = 0;
    params.c = 0;
        // 设置为true表示更新坐标信息，为false则表示位置原来的数据
    params.set_x = params.set_y = params.set_z = true;
    params.set_a = params.set_b = params.set_c = false;
    Mirobot.writecoordinate(0, 0, params);

    for (int i = 0; i < 5; i++) {
        Mirobot.writecoordinate(0, 0, 255, 0, 200, 0, 0, 0);
        Mirobot.writecoordinate(0, 0, 255, 0, 100, 0, 0, 0);
        Mirobot_2.writecoordinate(0, 0, 255, 0, 200, 0, 0, 0);
        Mirobot_2.writecoordinate(0, 0, 255, 0, 100, 0, 0, 0);
    }
    my_serial.close();
    // system("pause");
    return 0;
}
```

## Mirobot 接线图 (UART)

<div style="text-align: center;">
  <img src="./img/img2.png" style="width: 30%;">
  <img src="./img/img3.png" style="width: 50%;">
</div>

## Mirobot 示例用法 (UART)

```C++
#include <iostream>
#include <chrono>
#include <thread>
#include "serial/serial.h"
#include "wlkataC.h"

int main() {
    serial::Serial my_serial("COM13", 115200);

    Mirobot_UART Mirobot;
    Mirobot.init(&my_serial, -1, true, true);
    // Mirobot.message_print(true);
    Mirobot.homing();

    Mirobot_UART::CoordinateParams params;
    params.x = 255;
    params.y = 50;
    params.z = 200;
    params.a = 20;
    params.b = 0;
    params.c = 0;
    params.set_x = params.set_y = params.set_z = true;
    params.set_a = params.set_b = params.set_c = false;
    Mirobot.writecoordinate(0, 0, params);

    for (int i = 0; i < 5; i++) {
        Mirobot.writecoordinate(0, 0, 255, 0, 200, 0, 0, 0);
        Mirobot.writecoordinate(0, 0, 255, 0, 100, 0, 0, 0);
    }

    my_serial.close();
    return 0;
}
```

## MT4 接线图 (RS485)

<div style="text-align: center;">
  <img src="./img/MT4_RS485.png" style="width: 50%;">
</div>

## MT4 示例用法 (RS485)

```C++
#include <iostream>
#include <chrono>
#include <thread>
#include "serial/serial.h"
#include "wlkataC.h"

int main() {
    serial::Serial my_serial("com13", 38400);

    MT4_UART MT4_1;
    MT4_1.init(&my_serial, 1,true,true);
    // MT4_1.message_print(true);
    MT4_1.homing();
    MT4_UART::CoordinateParams params;
    params.x = 255;
    params.y = 50;
    params.z = 200;
    params.a = 20;
    // 设置所有坐标标志为true
    params.set_x = params.set_y = params.set_z = true;
    params.set_a  = false;
    MT4_1.writecoordinate(0, 0, params);
    for (int i = 0; i < 5; i++) {
        MT4_1.writecoordinate(0, 0, 255, 0, 200, 0);
        MT4_1.writecoordinate(0, 0, 255, 0, 100, 0);
    }
    my_serial.close();
    // system("pause");
    return 0;
}
```

## MT4 接线图 (UART)

<div style="text-align: center;">
  <img src="./img/MT4_UART.png" style="width: 50%;">
</div>

## MT4 示例用法 (UART)

```C++
#include <iostream>
#include <chrono>
#include <thread>
#include "serial/serial.h"
#include "wlkataC.h"

int main() {
    serial::Serial my_serial("com13", 115200);

    MT4_UART MT4_1;
    MT4_1.init(&my_serial, -1, true, true);
    // MT4_1.message_print(true);
    MT4_1.homing();

    for (int i = 0; i < 5; i++) {
        MT4_1.writecoordinate(0, 0, 255, 0, 200, 0);
        MT4_1.writecoordinate(0, 0, 255, 0, 100, 0);
    }
    my_serial.close();
    // system("pause");
    return 0;
}
```

## MS4220 接线图 (RS485)

<div style="text-align: center;">
  <img src="./img/MS4220.png" style="width: 50%;">
</div>

## MS4220 示例用法 (RS485)

```C++
#include <iostream>
#include <chrono>
#include <thread>
#include "serial/serial.h"
#include "wlkataC.h"

int main() {
    serial::Serial my_serial("com13", 38400);
    MS4220_UART MS4220_1;
    MS4220_1.init(&my_serial, 10,true,true);
    for (int i = 0; i < 5; i++) {
        MS4220_1.move_speed(100);
        MS4220_1.move_speed(-100);
        MS4220_1.move_speed(0);
        }
    my_serial.close();
    // system("pause");
    return 0;
}
```
## Harobot 接线图 (UART)

<div style="text-align: center;">
  <img src="./img/Haro380-UART.png" style="width: 50%;">
</div>
## Harobot 示例用法 (UART)

```C++
#include <iostream>
#include <chrono>
#include <thread>
#include "serial/serial.h"
#include "wlkataC.h"

int main() {
    serial::Serial my_serial("COM4", 115200);

    Harobot_UART Harobot;
    Harobot.init(&my_serial, -1, true, true);
    Harobot.homing();

    for (int i = 0; i < 5; i++) {
        Harobot_UART::CoordinateParams params;
        params.x = 255;
        params.y = 50;
        params.z = 200;
        params.a = 20;
        params.set_x = params.set_y = params.set_z = true;
        Harobot.writecoordinate(0, 0, params);
        Harobot.writecoordinate(0, 0, 255, 0, 200, 0, 0, 0);
        Harobot.writecoordinate(0, 0, 255, 0, 100, 0, 0, 0);
    }

    my_serial.close();
    return 0;
}
```

## API 速览

- 公共串口基类：`UART`
  - `init(serial, addr, block_flag=false, message_flag=false)`（派生类实现）
  - `message_print(bool)`、`block_flag(bool)`、`senMsg(string)`、`read_data()`
- Mirobot/Harobot：`Mirobot_UART`、`Harobot_UART`
  - 运动：`homing(int)`, `writecoordinate(motion, position, ...)`, `writeangle(...)`, `speed(int)`, `zero()`
  - 状态：`getStatus()`, `getState()`, `getAngle(int)`, `getcoordinate(int)`
  - IO：`gpio_init()` 及 `gpio_*` 读写函数
  - 其他：`pump(int)`, `gripper(int)`, `restart()`, `runFile(string,bool)`
- MT4/E4：`MT4_UART`、`E4_UART`
  - 坐标/角度接口同 Mirobot，但为 4 轴参数版本
  - `homing(int)`, `zero()`，以及 `getAngle(int)`, `getcoordinate(int)`
- MS4220：`MS4220_UART`
  - 运动：`move_position(position, steps, speed)`, `move_speed(int)`
  - 状态：`get_Status()`, `get_State()`, `get_position()`, `get_sensor(string)`

## API 参考（表格）

### 串口基类 UART（派生类实现 init）

| 方法 | 签名 | 说明 |
| - | - | - |
| message_print | `void message_print(bool enable=false)` | 打印底层通讯日志 |
| block_flag | `void block_flag(bool enable=false)` | 设置阻塞行为（等待空闲） |
| senMsg | `void senMsg(std::string data)` | 发送原始指令（高级/内部使用） |
| read_data | `void read_data()` | 读取原始串口数据（高级/内部使用） |

### Mirobot_UART / Harobot_UART（6 轴接口）

| 类别 | 方法/结构 | 签名 | 说明 |
| - | - | - | - |
| 初始化 | init | `void init(serial::Serial* p,int addr,bool block=false,bool msg=false)` | `addr=-1` 为直连（UART）；RS485 用从站地址 |
| 运动 | homing | `void homing(int mode=8)` | 归位 |
| 运动 | writecoordinate | `void writecoordinate(int motion,int position,float x,float y,float z,float a,float b,float c)` | 直参版本 |
| 运动 | CoordinateParams | `{x,y,z,a,b,c; set_x..set_c}` | 只设置需要的坐标标志 |
| 运动 | writecoordinate | `void writecoordinate(int motion,int position,const CoordinateParams& p)` | 结构体版本 |
| 运动 | writeangle | `void writeangle(int position,float x,float y,float z,float a,float b,float c)` | 角度直参 |
| 运动 | AngleParams | `{x,y,z,a,b,c; set_x..set_c}` | 只设置需要的角度标志 |
| 运动 | writeangle | `void writeangle(int position,const AngleParams& p)` | 角度结构体版本 |
| 运动 | speed | `void speed(int v)` | 设置速度（设备定义） |
| 其他 | zero | `void zero()` | 清零 |
| 其他 | pump/gripper | `void pump(int on)` / `void gripper(int v)` | 气泵/夹爪 |
| 其他 | restart/runFile | `void restart()` / `void runFile(std::string,bool)` | 重启/运行文件 |
| 状态 | getStatus/getState | `datas getStatus()` / `std::string getState()` | 获取状态数据/状态字符串 |
| 状态 | getAngle/getcoordinate | `float getAngle(int)` / `float getcoordinate(int)` | 单项读取 |
| IO | gpio_* | `gpio_init/mode/output/input/enable/threshold` 等 | GPIO 相关接口 |

注：Harobot_UART 继承自 Mirobot_UART，接口相同，增加 Harobot 适配。

### MT4_UART / E4_UART（4 轴接口）

| 类别 | 方法/结构 | 签名 | 说明 |
| - | - | - | - |
| 初始化 | init | `void init(serial::Serial* p,int addr,bool block=false,bool msg=false)` | 同上 |
| 运动 | writecoordinate | `void writecoordinate(int motion,int position,float x,float y,float z,float a)` | 直参版本（4 轴） |
| 运动 | CoordinateParams | `{x,y,z,a; set_x..set_a}` | 坐标结构体 |
| 运动 | writecoordinate | `void writecoordinate(int motion,int position,const CoordinateParams& p)` | 结构体版本 |
| 运动 | writeangle | `void writeangle(int position,float x,float y,float z,float a)` | 角度直参 |
| 运动 | AngleParams | `{x,y,z,a; set_x..set_a}` | 角度结构体 |
| 运动 | writeangle | `void writeangle(int position,const AngleParams& p)` | 角度结构体版本 |
| 运动 | homing/zero | `void homing(int mode=8)` / `void zero()` | 归位/清零 |
| 状态 | getAngle/getcoordinate | `float getAngle(int)` / `float getcoordinate(int)` | 单项读取 |

E4_UART 继承自 MT4_UART，接口相同。

### MS4220_UART（步进控制）

| 类别 | 方法 | 签名 | 说明 |
| - | - | - | - |
| 初始化 | init | `void init(serial::Serial* p,int addr,bool block=false,bool msg=false)` | RS485 从站地址必填 |
| 控制 | restart/homing | `void restart()` / `void homing()` | 重启/回零 |
| 控制 | move_position | `void move_position(int position,int steps,int speed=50)` | 指定点位/步数/速度 |
| 控制 | move_speed | `void move_speed(int v)` | 速度模式（正负方向） |
| 状态 | get_Status/get_State | `datas get_Status()` / `std::string get_State()` | 状态结构/字符串 |
| 状态 | get_position/get_sensor | `int get_position()` / `int get_sensor(std::string)` | 位置与传感器 |

---

## 最小可运行示例

### Mirobot（UART，直连）

```C++
#include <chrono>
#include <thread>
#include "serial/serial.h"
#include "wlkataC.h"

int main() {
    serial::Serial serial("COM13", 115200);
    Mirobot_UART bot;
    bot.init(&serial, -1, true, true);
    bot.homing();
    Mirobot_UART::CoordinateParams p; 
    p.x=200; 
    p.z=150; 
    p.set_x=p.set_z=true;
    bot.writecoordinate(0, 0, p);
    serial.close();
}
```

### MS4220（RS485，从站地址 10）

```C++
#include <chrono>
#include <thread>
#include "serial/serial.h"
#include "wlkataC.h"

int main() {
    serial::Serial serial("COM13", 38400);
    MS4220_UART drv; 
    drv.init(&serial, 10, true, true);
    drv.homing();
    drv.move_speed(100);
    drv.move_speed(0);
    serial.close();
}
```

### 枚举串口（诊断辅助）

```C++
#include <iostream>
#include "serial/serial.h"
int main(){
    for (auto &p : serial::list_ports()) {
        std::cout << p.port << " " << p.description << "\n";
    }
}
```

---

### [0.1.0] - 2025-10-30
- 该版本：支持 Mirobot、MT4、E4、Haro380、MS4220 基础控制。
- 提供 RS485 与 UART 通讯示例。

## 联系方式

**&nbsp;&nbsp;&nbsp;&nbsp;请联系 WLkata 人员获取进一步说明 [WLkata 下载页面](https://cn.wlkata.com/index.php?pageid=137631)。**
