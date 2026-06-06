# 04 - 0.96寸OLED屏幕驱动

## 实验目的
学习使用I2C驱动SSD1306 0.96寸OLED屏幕

## 实验材料
- Arduino Uno 开发板
- 0.96寸OLED屏幕（SSD1306驱动，I2C接口）
- 杜邦线若干

## 硬件连接
7个排针的OLED常见引脚定义，从左到右（通常顺序）：
```
OLED GND  ──────── Arduino GND
OLED VCC  ──────── Arduino 5V 或 3.3V
OLED SCL  ──────── Arduino A5 (SCL)
OLED SDA  ──────── Arduino A4 (SDA)
```
(注意：不同型号可能引脚顺序不同，需根据屏幕背面标识确认)

## 安装库
在Arduino IDE库管理器中搜索并安装：
- Adafruit SSD1306
- Adafruit GFX Library

## 代码说明
- `display.begin()` 初始化屏幕，I2C地址通常是0x3C或0x3D
- `display.setTextSize()` 设置字体大小
- `display.println()` 输出文本
- `display.display()` 将缓冲区内容显示到屏幕

## 预期效果
1. 屏幕先显示"Arduino Uno"、"OLED Test"、"Hello, World!"
2. 然后显示计数器，每0.5秒加1

## 常见问题
- 如果屏幕没反应，尝试修改I2C地址为0x3D
- 检查SCL/SDA引脚连接是否正确
- 确认屏幕供电电压（3.3V或5V）
