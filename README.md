# Arduino Uno 实验项目

这是一个用于学习 Arduino Uno 的项目，包含一系列小实验，逐步学习 Arduino 的基础功能。

## 项目简介

本项目包含 5 个基础实验，从简单到复杂，逐步学习 Arduino 的 GPIO、ADC、PWM、中断、I2C（模拟）通信和显示屏控制。

## 实验列表

### 01 - LED 闪烁
- **目录**：[01_blink](01_blink)
- **内容**：最基础的 Arduino 实验，控制板载 LED 闪烁
- **知识点**：GPIO 输出控制、delay 延时函数

### 02 - 电位器读取
- **目录**：[02_potentiometer](02_potentiometer)
- **内容**：使用模拟输入读取电位器值，通过串口显示
- **知识点**：ADC 模拟输入、串口通信

### 03 - PWM 风扇控制
- **目录**：[03_fan_control](03_fan_control)
- **内容**：使用电位器调节 PWM 值控制风扇转速，并通过 TACH 信号读取实际转速
- **知识点**：PWM 输出、外部中断、转速计算

### 04 - OLED 屏幕显示
- **目录**：[04_oled](04_oled)
- **内容**：驱动 0.96 寸 OLED 屏幕，显示文字、数字等内容
- **知识点**：模拟 I2C 通信、OLED 驱动、字库使用

### 05 - 风扇+OLED 综合控制
- **目录**：[05_fan_oled](05_fan_oled)
- **内容**：整合前面实验，用电位器控制风扇，在 OLED 上实时显示电位器值、电压、PWM、转速百分比和风扇转速
- **知识点**：项目整合、数据可视化、实时更新

## 硬件要求

- Arduino Uno 开发板
- USB 数据线
- 面包板和杜邦线
- 电位器（10KΩ）
- 4线 PWM 风扇（含 TACH 信号）
- 0.96 寸 OLED 屏幕（7针 SPI/I2C 两用）

## 软件要求

- Arduino IDE
- （可选）Arduino 中文语言包

## 使用说明

1. 克隆或下载项目到本地
2. 使用 Arduino IDE 打开对应实验目录下的 `.ino` 文件
3. 按照对应实验目录下的 README.md 连接硬件
4. 选择正确的开发板型号（Arduino Uno）和端口
5. 点击上传按钮，上传程序到开发板

## 项目结构

```
Arduino Uno/
├── 01_blink/
│   ├── 01_blink.ino
│   └── README.md
├── 02_potentiometer/
│   ├── 02_potentiometer.ino
│   └── README.md
├── 03_fan_control/
│   ├── 03_fan_control.ino
│   └── README.md
├── 04_oled/
│   ├── 04_oled.ino
│   ├── font.h
│   ├── README.md
│   └── 使用前请阅读此文档.txt
├── 05_fan_oled/
│   ├── 05_fan_oled.ino
│   ├── font.h
│   └── README.md
└── README.md (本文件)
```

## 注意事项

- 连接硬件前请先断开电源，防止短路
- 注意引脚定义，避免接错导致硬件损坏
- 风扇需要外部电源（通常是12V），但 GND 必须和 Arduino 共地
- OLED 屏幕有多种型号，注意区分引脚定义
