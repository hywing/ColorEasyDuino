#include <Adafruit_MLX90614.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// 定义屏幕宽度和高度
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// 创建一个Adafruit_SSD1306对象。参数为复位引脚，由于许多模块没有使用，因此传递-1。
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("Adafruit MLX90614 test");

  if (!mlx.begin()) {
    Serial.println("Error connecting to MLX sensor. Check wiring.");
    while (1);
  };

  // 初始化OLED显示屏
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  display.clearDisplay();
  display.setTextSize(1);    
  display.setTextColor(SSD1306_WHITE); 
  display.display();

  Serial.print("Emissivity = "); Serial.println(mlx.readEmissivity());
  Serial.println("================================================");
}

void refresh(double value) 
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0,25);
  String str1 = " ";
  String str2 = " `C";
  String str = str1 + value + str2;
  display.println(str.c_str());
  display.display();
  Serial.println(str);
}


void loop() {
  // Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC());
  double temp = mlx.readObjectTempC();
  refresh(temp);
  Serial.print("*C\tObject = "); Serial.print(temp); Serial.println("*C");
  // Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF());
  Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");

  Serial.println();
  delay(500);
}