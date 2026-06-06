/*
 * 01 - 小灯闪烁实验
 * 
 * 实验内容：让 LED 灯闪烁
 * 硬件连接：LED 正极连接 Arduino 的 13 号引脚，负极通过 220Ω 电阻连接到 GND
 * 
 * 大多数 Arduino 开发板都有一个内置 LED 连接在 13 号引脚，
 * 可以直接使用，无需额外连接外部 LED。
 */

const int LED_PIN = 13;  // 定义 LED 引脚

void setup() {
  pinMode(LED_PIN, OUTPUT);  // 设置引脚为输出模式
}

void loop() {
  digitalWrite(LED_PIN, HIGH);  // 点亮 LED
  delay(1000);                  // 等待 1 秒
  digitalWrite(LED_PIN, LOW);   // 关闭 LED
  delay(1000);                  // 等待 1 秒
}
