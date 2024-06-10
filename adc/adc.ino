#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// 定义屏幕宽度和高度
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// 创建一个Adafruit_SSD1306对象。参数为复位引脚，由于许多模块没有使用，因此传递-1。
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// 定义电位器连接到的模拟输入引脚
const int potPin = A0;
// 定义LED连接到的数字引脚，需要支持PWM
const int ledPin = 9;

void refresh(float value) 
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0,25);
  String str1 = " ";
  String str2 = " V";
  String str = str1 + value + str2;
  display.println(str.c_str());
  display.display();
  Serial.println(str);
}

void setup() {
  // 初始化LED引脚为输出模式
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600); // 初始化串口

  // 初始化OLED显示屏
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  display.clearDisplay();
  display.setTextSize(1);    
  display.setTextColor(SSD1306_WHITE); 
  display.display();
}

void loop() {
  // 读取电位器的值（0到1023之间）
  int potValue = analogRead(potPin);
  float value = potValue / 1024.0 * 5.0;
  Serial.println(value);

  refresh(value);
  
  // 将读取的模拟值映射到PWM范围（0到255之间）
  int ledBrightness = map(potValue, 0, 1023, 0, 255);
  // 设置LED的亮度
  analogWrite(ledPin, ledBrightness);
  
  // 为了看到亮度变化，这里延迟100毫秒
  delay(1000);
}