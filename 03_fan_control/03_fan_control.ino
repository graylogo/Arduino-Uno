/*
 * 03 - 电位器控制 PWM 风扇转速实验
 *
 * 实验内容：通过电位器调节 Arduino 的 PWM 输出，控制风扇转速
 * 硬件连接：
 *   - 电位器：同实验 02
 *   - PWM 风扇控制信号连接 Arduino 9 号引脚
 *   - 风扇转速信号（Tach）连接 Arduino 2 号引脚（中断0）
 *
 * 注意：Arduino Uno 支持 PWM 的引脚：3, 5, 6, 9, 10, 11
 */

const int POT_PIN = A0;       // 电位器中间抽头连接 A0
const int FAN_PWM_PIN = 9;   // 风扇 PWM 控制信号连接 9 号引脚
const int FAN_TACH_PIN = 2;  // 风扇转速信号连接 2 号引脚（中断0）

const int PWM_MIN = 50;      // 风扇最小启动 PWM 值（约 20%，确保能启动）
const int PWM_OFF = 30;       // 低于此值认为风扇关闭，不计转速

volatile unsigned int tachCount = 0;  // 转速脉冲计数
unsigned long lastTime = 0;           // 上次计算时间

int adcValue = 0;             // ADC 原始值 (0-1023)
int pwmValue = 0;             // PWM 输出值 (0-255)
int fanRpm = 0;               // 风扇转速（RPM）

void tachISR() {
  // 只有 PWM 值大于 OFF 阈值时才计数，防止干扰
  if (pwmValue > PWM_OFF) {
    tachCount++;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(FAN_PWM_PIN, OUTPUT);
  pinMode(FAN_TACH_PIN, INPUT_PULLUP);

  // 绑定中断处理函数，下降沿触发
  attachInterrupt(digitalPinToInterrupt(FAN_TACH_PIN), tachISR, FALLING);

  lastTime = millis();
}

void loop() {
  // 读取电位器 ADC 值
  adcValue = analogRead(POT_PIN);

  // 将 ADC 值 (0-1023) 映射到 PWM 范围 (PWM_MIN-255)
  // 确保旋钮在最低位置时风扇也能启动
  pwmValue = map(adcValue, 0, 1023, PWM_MIN, 255);

  // 输出 PWM 信号控制风扇
  analogWrite(FAN_PWM_PIN, pwmValue);

  // 每秒计算一次转速
  if (millis() - lastTime >= 1000) {
    // 只有 PWM 值大于 OFF 阈值时才计算转速
    if (pwmValue > PWM_OFF) {
      // 风扇每转一般输出 2 个脉冲（Tach 信号）
      // RPM = 脉冲数 / 2 / 时间(秒)
      fanRpm = (tachCount / 2) * (1000.0 / (millis() - lastTime)) * 60;
    } else {
      fanRpm = 0;
    }

    Serial.print("ADC: ");
    Serial.print(adcValue);
    Serial.print(" | PWM: ");
    Serial.print(pwmValue);
    Serial.print(" | Speed: ");
    Serial.print(map(pwmValue, PWM_MIN, 255, 0, 100));
    Serial.print("% | RPM: ");
    Serial.println(fanRpm);

    tachCount = 0;
    lastTime = millis();
  }
}
