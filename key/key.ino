#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// 定义屏幕宽度和高度
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// 创建一个Adafruit_SSD1306对象。参数为复位引脚，由于许多模块没有使用，因此传递-1。
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// 按键引脚定义
static const int buttonPin1 = 2;
static const int buttonPin2 = 3;
static const int buttonPin3 = 4;
static const int buttonPin4 = 5;

// LED引脚定义
static const int ledPin1 = 13;
static const int ledPin2 = 0;
static const int ledPin3 = 1;
static const int relay = 6;

// 引脚状态
static int buttonState1 = 0;
static int buttonState2 = 0;
static int buttonState3 = 0;
static int buttonState4 = 0;

// 1.初始化引脚模式：LED引脚设为输出，按键引脚设为输入模式；2.初始化OLED显示屏
void setup() {
  // 初始化LED引脚为输出模式
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(relay, OUTPUT);

  // 初始化按钮引脚为输入模式
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);

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

void refresh(int key) 
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0,25);
  String str1 = "Key ";
  String str2 = " Pressed!";
  String str = str1 + key + str2;
  display.println(str.c_str());
  display.display();
}

// 循环检测按键状态，电平值为低时按键按下，LED1是高电平为亮，其余皆是低电平亮
void loop() {
  // 绿灯亮
  buttonState1 = digitalRead(buttonPin1);
  if (buttonState1 == LOW) {
    refresh(1);
    digitalWrite(ledPin1, HIGH);
  } else {
    digitalWrite(ledPin1, LOW);
  }

  // 黄灯亮
  buttonState2 = digitalRead(buttonPin2);
  if (buttonState2 == LOW) {
    refresh(2);
    digitalWrite(ledPin2, LOW);
  } else {
    digitalWrite(ledPin2, HIGH);
  }

  // 蓝灯亮
  buttonState3 = digitalRead(buttonPin3);
  if (buttonState3 == LOW) {
    refresh(3);
    digitalWrite(ledPin3, LOW);
  } else {
    digitalWrite(ledPin3, HIGH);
  }

  // 跑马灯模式
  buttonState4 = digitalRead(buttonPin4);
  if (buttonState4 == LOW) {
    refresh(4);

    digitalWrite(relay, HIGH);

    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
    delay(1000);

    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, HIGH);
    delay(1000);

    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, LOW);
    delay(1000);

    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, HIGH);
    delay(1000);

    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
    delay(1000);
  }
  else {
    digitalWrite(relay, LOW);
  }
}