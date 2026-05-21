# Basic-C-Language-Smart-Home-Demo

使用 C 语言模拟 OOP 写法的智能家居中控系统 Demo，代码按 `BSP -> driver -> middleware -> app` 分层。

## 功能

- 客厅灯、卧室灯开关控制
- 中央空调目标温度设置，限制范围 16°C 到 30°C
- 睡眠模式：关闭灯光，空调目标温度设为 28°C
- 离家模式：关闭灯光、关闭空调、安防报警器布防
- 退出时保存状态到 `device_data.txt`，下次启动自动恢复

## 分层

- `BSP/`：板级支持层，封装控制台输入输出和文件存储。
- `driver/`：设备驱动层，封装 Light、AirConditioner、SecurityAlarm 等设备对象。
- `middleware/`：中间件层，封装基础 UI。
- `app/`：应用层，负责智能家居业务流程、菜单逻辑和场景联动。

## 编译运行

```sh
gcc -std=c99 -Wall -Wextra -Wpedantic -Iapp -IBSP -Idriver -Imiddleware app/main.c app/smart_home.c BSP/bsp_console.c BSP/bsp_storage.c driver/device.c driver/light.c driver/air_conditioner.c driver/security_alarm.c middleware/basic_ui.c -o build/smart_home
```

如果安装了 `make`：

```sh
make
make run
```
