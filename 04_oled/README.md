# 04 - 0.96寸OLED屏幕驱动

## 实验目的
学习驱动SSD1306 0.96寸OLED屏幕

## 实验材料
- Arduino Uno 开发板
- 0.96寸OLED屏幕（SSD1306驱动，7引脚 SPI/I2C 双接口）
- 杜邦线若干

## 硬件连接（SPI模式）
按照官方示例连接：
```
OLED GND  →  Arduino GND
OLED VCC  →  Arduino 3.3V
OLED D0   →  Arduino 8  (SCL)
OLED D1   →  Arduino 9  (SDA)
OLED RES  →  Arduino 10
OLED DC   →  Arduino 11
OLED CS   →  Arduino 12
```

## 代码说明
使用官方示例代码，SPI 软件模拟驱动

## 预期效果
屏幕循环显示：
1. 图片
2. 日期、ASCII字符和编码
3. 不同大小的"中"字
4. 不同大小的"ABC"字符串
