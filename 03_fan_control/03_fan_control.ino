/*
 * 03 - 电位器控制 PWM 风扇转速实验
 * 
 * 实验内容：通过电位器调节 Arduino 的 PWM 输出，控制风扇转速
 * 硬件连接：
 *   - 电位器：同实验 02
 *   - PWM 风扇控制信号连接 Arduino 9 号引脚（必须是支持 PWM 的引脚）
 * 
 * 注意：Arduino Uno 支持 PWM 的引脚：3, 5, 6, 9, 10, 11
 */

const int POT_PIN = A0;       // 电位器中间抽头连接 A0
const int FAN_PWM_PIN = 9;    // 风扇 PWM 控制信号连接 9 号引脚

int adcValue = 0;             // ADC 原始值 (0-1023)
int pwmValue = 0;             // PWM 输出值 (0-255)

void setup() {
  Serial.begin(9600);
  pinMode(FAN_PWM_PIN, OUTPUT);  // 设置风扇引脚为输出模式
}

void loop() {
  // 读取电位器 ADC 值
  adcValue = analogRead(POT_PIN);
  
  // 将 ADC 值 (0-1023) 映射到 PWM 范围 (0-255)
  pwmValue = map(adcValue, 0, 1023, 0, 255);
  
  // 输出 PWM 信号控制风扇
  analogWrite(FAN_PWM_PIN, pwmValue);
  
  // 串口输出
  Serial.print("ADC: ");
  Serial.print(adcValue);
  Serial.print(" | PWM: ");
  Serial.print(pwmValue);
  Serial.print(" | Speed: ");
  Serial.print(map(pwmValue, 0, 255, 0, 100));  // 转换为 0-100% 显示
  Serial.println("%");
  
  delay(100);
}
