# 03 - 电位器控制 PWM 风扇转速

## 实验目的
学习 Arduino PWM（脉冲宽度调制）输出，通过电位器控制风扇转速

## 实验材料
- Arduino Uno 开发板
- 面包板
- 10KΩ 电位器 1个
- PWM 风扇 1个
- 杜邦线若干
- 电源适配器（根据风扇电压要求，一般 12V，需与风扇电源独立供电）

## 硬件连接

### 电位器（同实验 02）
```
Arduino 5V  ──────── 电位器 引脚1
Arduino A0  ──────── 电位器 引脚2（中间抽头）
Arduino GND ──────── 电位器 引脚3
```

### PWM 风扇
```
风扇 VCC  ──────── 外部电源正极（如 12V）
风扇 GND  ──────── Arduino GND 和外部电源负极
风扇 PWM  ──────── Arduino 9 号引脚
```

⚠️ **重要提示**：
1. 风扇电源必须与 Arduino **共地**（GND 连在一起）
2. 大多数 PWM 风扇是 12V 供电，需要独立电源，不能直接接 Arduino 5V
3. Arduino PWM 引脚输出 0-5V PWM 信号用于控制
4. 确保风扇的 PWM 控制线与 Arduino 引脚匹配

## 代码说明
- `map(value, fromLow, fromHigh, toLow, toHigh)` - 数值映射函数
- `analogWrite(pin, value)` - 输出 PWM 信号，value 范围 0-255
- PWM 引脚（Uno）：3, 5, 6, 9, 10, 11（带有 ~ 标记）

## 预期效果
旋转电位器旋钮：
- 旋钮逆时针到底 → 风扇停转（PWM 0）
- 旋钮顺时针到底 → 风扇全速（PWM 255）
- 中间位置 → 不同转速

串口监视器显示：
```
ADC: 0 | PWM: 0 | Speed: 0%
ADC: 512 | PWM: 127 | Speed: 50%
ADC: 1023 | PWM: 255 | Speed: 100%
```
