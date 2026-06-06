# 01 - 小灯闪烁

## 实验目的
学习 Arduino 基本编程控制 GPIO 输出

## 实验材料
- Arduino Uno 开发板
- 面包板
- LED 灯（可选，使用板载 LED 可省略）
- 220Ω 电阻（可选）

## 硬件连接

### 方式一：使用板载 LED（无需额外连接）
大多数 Arduino Uno 板子上有一个内置 LED，连接在 13 号引脚，直接使用即可。

### 方式二：外接 LED
```
Arduino 13号引脚 --- [LED] --- [220Ω电阻] --- GND
```

## 代码说明
- `pinMode(LED_PIN, OUTPUT)` - 设置引脚为输出模式
- `digitalWrite(LED_PIN, HIGH)` - 向引脚写入高电平，点亮 LED
- `digitalWrite(LED_PIN, LOW)` - 向引脚写入低电平，熄灭 LED
- `delay(1000)` - 延时函数，单位毫秒

## 上传步骤
1. 用 USB 线连接 Arduino 开发板
2. 在 Arduino IDE 中打开 `01_blink.ino` 文件
3. 选择正确的板卡和端口
4. 点击上传按钮

## 预期效果
LED 灯会亮 1 秒，然后灭 1 秒，不断循环。
