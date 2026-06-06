/*
 * 02 - 电位器阻值读取实验
 * 
 * 实验内容：通过 ADC 读取电位器的模拟电压值，计算并显示阻值
 * 硬件连接：
 *   - 电位器引脚1（VCC）连接 Arduino 5V
 *   - 电位器引脚2（中间抽头）连接 Arduino A0
 *   - 电位器引脚3（GND）连接 Arduino GND
 * 
 * 注意：Arduino ADC 是 10 位精度，输出范围 0-1023
 */

const int POT_PIN = A0;       // 电位器中间抽头连接的模拟引脚
const float VCC = 5.0;        // Arduino 参考电压
const int TOTAL_RESISTANCE = 10000;  // 电位器最大阻值（10KΩ）

int adcValue = 0;             // ADC 原始值 (0-1023)
float voltage = 0.0;          // 计算得到的电压值
float resistance = 0.0;       // 计算得到的阻值

void setup() {
  Serial.begin(9600);         // 初始化串口通信，波特率 9600
  analogReference(DEFAULT);   // 使用默认参考电压（5V）
}

void loop() {
  // 读取 ADC 值
  adcValue = analogRead(POT_PIN);
  
  // 将 ADC 值转换为电压值
  // ADC 范围 0-1023 对应 0-5V
  voltage = (adcValue / 1023.0) * VCC;
  
  // 计算当前阻值
  // 电压分压公式：Vout = VCC * R2 / (R1 + R2)
  // 其中 R2 是中间抽头到 GND 的阻值
  if (adcValue > 0) {
    resistance = (voltage / VCC) * TOTAL_RESISTANCE;
  } else {
    resistance = 0;
  }
  
  // 通过串口输出显示
  Serial.print("ADC: ");
  Serial.print(adcValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 2);
  Serial.print("V | Resistance: ");
  Serial.print(resistance, 0);
  Serial.println(" Ohm");
  
  delay(200);  // 延时 200ms，更新频率约 5Hz
}
