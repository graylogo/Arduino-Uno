# 05 - 电位器控制风扇+OLED实时显示

## 实验目的
整合电位器、风扇和OLED，在屏幕上实时显示电阻值、电压、PWM、转速百分比和风扇转速

## 硬件连接
| 设备       | 引脚  | Arduino引脚 |
|------------|-------|-------------|
| 电位器 GND | GND   | GND         |
| 电位器 VCC | VCC   | 5V          |
| 电位器抽头 | OUT   | A0          |
| 风扇 VCC   | VCC   | 外部12V     |
| 风扇 GND   | GND   | GND         |
| 风扇 PWM   | PWM   | 5           |
| 风扇 TACH  | TACH  | 2           |
| OLED GND   | GND   | GND         |
| OLED VCC   | VCC   | 3.3V        |
| OLED D0    | SCL   | 8           |
| OLED D1    | SDA   | 9           |
| OLED RES   | RES   | 10          |
| OLED DC    | DC    | 11          |
| OLED CS    | CS    | 12          |

## 说明
- 为了OLED接线方便，保持OLED D1在9不变，风扇PWM改到5
- 风扇需要外部电源（通常是12V），但GND必须和Arduino共地
- 电位器保持和原来一样连接A0

## 预期效果
OLED屏幕实时显示：
- 第一行：标题 "=Fan Monitor="
- 第二行：ADC值和电压（例如 ADC:0512 V:2.5）
- 第三行：PWM值和转速百分比（例如 PWM:153 Spd:50%）
- 第四行：风扇实际转速（例如 RPM:01500）
