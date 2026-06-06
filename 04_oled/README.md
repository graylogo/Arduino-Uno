# 04 - 0.96寸OLED屏幕驱动

## 实验目的
学习驱动SSD1306 0.96寸OLED屏幕

## 实验材料
- Arduino Uno 开发板
- 0.96寸OLED屏幕（SSD1306驱动，I2C接口）
- 杜邦线若干

## 硬件连接
根据官方示例接线：
```
OLED GND  ──────── Arduino GND
OLED VCC  ──────── Arduino 3.3V
OLED D0   ──────── Arduino 8  (SCL)
OLED D1   ──────── Arduino 9  (SDA)
OLED RES  ──────── Arduino 10 (RES)
```
(注：如果是原生I2C模块，RES引脚可以忽略不接)

## 代码说明
使用官方示例 `OLED.ino`，需要配套 font.h 文件。

## 预期效果
1. 显示图片
2. 显示日期、ASCII字符和编码
3. 显示不同大小的"中"字
4. 显示不同大小的"ABC"字符串
