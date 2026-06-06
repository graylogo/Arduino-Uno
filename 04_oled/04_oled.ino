/*
 * 04 - 0.96寸OLED屏幕驱动实验
 *
 * 实验内容：驱动SSD1306 0.96寸OLED屏幕，显示文字和图形
 * 硬件连接：
 *   - OLED GND  ──────── Arduino GND
 *   - OLED VCC  ──────── Arduino 5V 或 3.3V
 *   - OLED SCL  ──────── Arduino A5 (SCL)
 *   - OLED SDA  ──────── Arduino A4 (SDA)
 *
 * 依赖库：
 *   - Adafruit SSD1306 (库管理器搜索 "SSD1306" 安装)
 *   - Adafruit GFX (库管理器搜索 "GFX" 安装)
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128   // OLED屏幕宽度
#define SCREEN_HEIGHT 64   // OLED屏幕高度
#define OLED_RESET    -1   // 不使用复位引脚

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);

  // 初始化OLED屏幕，地址通常是 0x3C 或 0x3D
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // 初始化失败，死循环
  }

  // 清屏并显示
  display.clearDisplay();
  display.display();
  delay(1000);

  // 显示文字
  display.setTextSize(1);              // 设置字体大小
  display.setTextColor(SSD1306_WHITE); // 设置文本颜色
  display.setCursor(0, 0);             // 设置光标位置
  display.println(F("Arduino Uno"));
  display.println(F("OLED Test"));
  display.println(F(""));
  display.println(F("Hello, World!"));
  display.display();
  delay(2000);
}

void loop() {
  // 显示计数器
  static int counter = 0;

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("Counter:"));
  display.setTextSize(2);
  display.setCursor(0, 20);
  display.println(counter);

  display.display();
  counter++;
  delay(500);
}
