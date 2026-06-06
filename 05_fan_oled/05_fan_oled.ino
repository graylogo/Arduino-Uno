// 05 - 电位器控制风扇+OLED实时显示
#include "font.h"

// ================== OLED引脚定义 ==================
int scl=8;  // OLED SCL
int sda=6;  // OLED SDA (从9改成6，避免冲突)
int res=10; // OLED RES
int dc=11;  // OLED DC
int cs=12;  // OLED CS

// ================== 风扇和电位器引脚定义 ==================
const int POT_PIN = A0;      // 电位器
const int FAN_PWM_PIN = 3;   // 风扇PWM (从9改成3)
const int FAN_TACH_PIN = 2;  // 风扇TACH

// ================== 变量定义 ==================
volatile unsigned int tachCount = 0; // 转速脉冲计数
unsigned long lastTachTime = 0;      // 上次转速计算时间
unsigned long lastOledUpdate = 0;    // 上次OLED更新时间
int adcValue = 0;
int pwmValue = 0;
int fanRpm = 0;
int speedPercent = 0;

uint8_t OLED_GRAM[128][8]; // OLED显存

// ================== OLED驱动宏定义 ==================
#define OLED_SCLK_Clr() digitalWrite(scl,LOW)
#define OLED_SCLK_Set() digitalWrite(scl,HIGH)
#define OLED_SDIN_Clr() digitalWrite(sda,LOW)
#define OLED_SDIN_Set() digitalWrite(sda,HIGH)
#define OLED_RST_Clr() digitalWrite(res,LOW)
#define OLED_RST_Set() digitalWrite(res,HIGH)
#define OLED_DC_Clr()  digitalWrite(dc,LOW)
#define OLED_DC_Set()  digitalWrite(dc,HIGH)
#define OLED_CS_Clr()  digitalWrite(cs,LOW)
#define OLED_CS_Set()  digitalWrite(cs,HIGH)
#define OLED_CMD  0
#define OLED_DATA 1

// ================== 简易幂函数替代 ==================
int pow10(int n) {
  int result = 1;
  for(int i=0; i&lt;n; i++) result *= 10;
  return result;
}

// ================== 中断处理函数 ==================
void tachISR() {
  tachCount++;
}

// ================== OLED驱动函数 ==================
void OLED_WR_Byte(uint8_t dat,uint8_t cmd) {
  uint8_t i;
  if(cmd) OLED_DC_Set();
  else OLED_DC_Clr();
  OLED_CS_Clr();
  for(i=0;i&lt;8;i++) {
    OLED_SCLK_Clr();
    if(dat&amp;0x80) OLED_SDIN_Set();
    else OLED_SDIN_Clr();
    OLED_SCLK_Set();
    dat&lt;&lt;=1;
  }
}

void OLED_Refresh(void) {
  uint8_t i,n;
  for(i=0;i&lt;8;i++) {
     OLED_WR_Byte(0xb0+i,OLED_CMD);
     OLED_WR_Byte(0x00,OLED_CMD);
     OLED_WR_Byte(0x10,OLED_CMD);
     for(n=0;n&lt;128;n++)
     OLED_WR_Byte(OLED_GRAM[n][i],OLED_DATA);
  }
}

void OLED_Clear(void) {
  uint8_t i,n;
  for(i=0;i&lt;8;i++) {
     for(n=0;n&lt;128;n++) {
       OLED_GRAM[n][i]=0;
     }
  }
  OLED_Refresh();
}

void OLED_DrawPoint(uint8_t x,uint8_t y) {
  uint8_t i,m,n;
  i=y/8;
  m=y%8;
  n=1&lt;&lt;m;
  OLED_GRAM[x][i]|=n;
}

void OLED_ClearPoint(uint8_t x,uint8_t y) {
  uint8_t i,m,n;
  i=y/8;
  m=y%8;
  n=1&lt;&lt;m;
  OLED_GRAM[x][i]=~OLED_GRAM[x][i];
  OLED_GRAM[x][i]|=n;
  OLED_GRAM[x][i]=~OLED_GRAM[x][i];
}

void OLED_ShowChar(uint8_t x,uint8_t y,const char chr,uint8_t size1) {
  uint8_t i,m,temp,size2,chr1;
  uint8_t y0=y;
  size2=(size1/8+((size1%8)?1:0))*(size1/2);
  chr1=chr-' ';
  for(i=0;i&lt;size2;i++) {
    if(size1==12) { temp=pgm_read_byte(&amp;asc2_1206[chr1][i]); }
    else if(size1==16) { temp=pgm_read_byte(&amp;asc2_1608[chr1][i]); }
    else if(size1==24) { temp=pgm_read_byte(&amp;asc2_2412[chr1][i]); }
    else return;
    for(m=0;m&lt;8;m++) {
      if(temp&amp;0x80)OLED_DrawPoint(x,y);
      else OLED_ClearPoint(x,y);
      temp&lt;&lt;=1;
      y++;
      if((y-y0)==size1) { y=y0; x++; break; }
    }
  }
}

void OLED_ShowString(uint8_t x,uint8_t y,const char *chr,uint8_t size1) {
  while((*chr&gt;=' ')&amp;&amp;(*chr&lt;='~')) {
    OLED_ShowChar(x,y,*chr,size1);
    x+=size1/2;
    if(x&gt;128-size1/2) { x=0; y+=size1; }
    chr++;
  }
}

void OLED_ShowNum(uint8_t x,uint8_t y,int num,uint8_t len,uint8_t size1) {
  uint8_t t,temp;
  for(t=0;t&lt;len;t++) {
    temp=(num/pow10(len-t-1))%10;
    if(temp==0 &amp;&amp; t&gt;0) OLED_ShowChar(x+(size1/2)*t,y,' ',size1);
    else if(temp==0 &amp;&amp; t==0) OLED_ShowChar(x+(size1/2)*t,y,'0',size1);
    else OLED_ShowChar(x+(size1/2)*t,y,temp+'0',size1);
  }
}

void OLED_Init(void) {
  pinMode(scl,OUTPUT);
  pinMode(sda,OUTPUT);
  pinMode(res,OUTPUT);
  pinMode(dc,OUTPUT);
  pinMode(cs,OUTPUT);

  OLED_RST_Set();
  delay(100);
  OLED_RST_Clr();
  delay(200);
  OLED_RST_Set();

  OLED_WR_Byte(0xAE,OLED_CMD);
  OLED_WR_Byte(0x00,OLED_CMD);
  OLED_WR_Byte(0x10,OLED_CMD);
  OLED_WR_Byte(0x40,OLED_CMD);
  OLED_WR_Byte(0x81,OLED_CMD);
  OLED_WR_Byte(0xCF,OLED_CMD);
  OLED_WR_Byte(0xA1,OLED_CMD);
  OLED_WR_Byte(0xC8,OLED_CMD);
  OLED_WR_Byte(0xA6,OLED_CMD);
  OLED_WR_Byte(0xA8,OLED_CMD);
  OLED_WR_Byte(0x3f,OLED_CMD);
  OLED_WR_Byte(0xD3,OLED_CMD);
  OLED_WR_Byte(0x00,OLED_CMD);
  OLED_WR_Byte(0xd5,OLED_CMD);
  OLED_WR_Byte(0x80,OLED_CMD);
  OLED_WR_Byte(0xD9,OLED_CMD);
  OLED_WR_Byte(0xF1,OLED_CMD);
  OLED_WR_Byte(0xDA,OLED_CMD);
  OLED_WR_Byte(0x12,OLED_CMD);
  OLED_WR_Byte(0xDB,OLED_CMD);
  OLED_WR_Byte(0x40,OLED_CMD);
  OLED_WR_Byte(0x20,OLED_CMD);
  OLED_WR_Byte(0x02,OLED_CMD);
  OLED_WR_Byte(0x8D,OLED_CMD);
  OLED_WR_Byte(0x14,OLED_CMD);
  OLED_WR_Byte(0xA4,OLED_CMD);
  OLED_WR_Byte(0xA6,OLED_CMD);
  OLED_WR_Byte(0xAF,OLED_CMD);
  OLED_Clear();
}

// ================== 主程序 ==================
void setup() {
  Serial.begin(9600);

  // 初始化OLED
  OLED_Init();

  // 初始化风扇和电位器引脚
  pinMode(FAN_PWM_PIN, OUTPUT);
  pinMode(FAN_TACH_PIN, INPUT_PULLUP);

  // 绑定中断
  attachInterrupt(digitalPinToInterrupt(FAN_TACH_PIN), tachISR, FALLING);

  // 显示欢迎界面
  OLED_ShowString(0,0," Fan Control ",16);
  OLED_ShowString(0,20," System Ready! ",12);
  OLED_Refresh();
  delay(1000);
}

void loop() {
  unsigned long now = millis();

  // 1. 读取电位器并控制风扇
  adcValue = analogRead(POT_PIN);
  pwmValue = map(adcValue, 0, 1023, 50, 255); // 50是最小启动PWM
  analogWrite(FAN_PWM_PIN, pwmValue);
  speedPercent = map(pwmValue, 50, 255, 0, 100);

  // 2. 每秒计算一次转速
  if (now - lastTachTime &gt;= 1000) {
    fanRpm = (tachCount / 2) * 60; // 每转2脉冲
    tachCount = 0;
    lastTachTime = now;
  }

  // 3. 每200ms更新一次OLED
  if (now - lastOledUpdate &gt;= 200) {
    OLED_Clear();

    // 标题
    OLED_ShowString(0,0,"=Fan Monitor=",12);

    // 第一行：ADC和电压
    OLED_ShowString(0,16,"ADC:",12);
    OLED_ShowNum(36,16,adcValue,4,12);
    int voltInt = adcValue * 50 / 1023; // *10计算
    OLED_ShowString(76,16,"V:",12);
    OLED_ShowNum(96,16,voltInt/10,1,12);
    OLED_ShowString(104,16,".",12);
    OLED_ShowNum(110,16,voltInt%10,1,12);

    // 第二行：PWM和百分比
    OLED_ShowString(0,32,"PWM:",12);
    OLED_ShowNum(36,32,pwmValue,3,12);
    OLED_ShowString(64,32,"Spd:",12);
    OLED_ShowNum(96,32,speedPercent,3,12);
    OLED_ShowString(116,32,"%",12);

    // 第三行：转速
    OLED_ShowString(0,48,"RPM:",12);
    OLED_ShowNum(36,48,fanRpm,5,12);

    OLED_Refresh();
    lastOledUpdate = now;
  }
}
