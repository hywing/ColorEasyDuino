// 定义电位器连接到的模拟输入引脚
const int potPin = A0;
// 定义LED连接到的数字引脚，需要支持PWM
const int ledPin = 9;

void setup() {
  // 初始化LED引脚为输出模式
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600); // 初始化串口
}

void loop() {
  // 读取电位器的值（0到1023之间）
  int potValue = analogRead(potPin);

  Serial.println(potValue);
  // 将读取的模拟值映射到PWM范围（0到255之间）
  int ledBrightness = map(potValue, 0, 1023, 0, 255);
  // 设置LED的亮度
  analogWrite(ledPin, ledBrightness);
  
  // 为了看到亮度变化，这里延迟100毫秒
  delay(1000);
}