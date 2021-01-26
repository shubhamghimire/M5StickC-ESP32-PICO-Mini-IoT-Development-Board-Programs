#include <M5StickC.h>

int battery = 0;
float b = 0;
int state = 1;

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  Serial.begin(115200);
  M5.Lcd.setRotation(1);
  M5.Lcd.fillScreen(BLACK);
  M5.Axp.ScreenBreath(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  M5.Lcd.setCursor(40, 30);
  M5.Lcd.setTextSize(4);
  M5.Lcd.setTextColor(GREEN);

  b = M5.Axp.GetVbatData() * 1.1 / 1000;
  battery = ((b- 3.0) / 1.2) * 100;

  if(battery>100){
    battery = 100;
  }
  else if(battery < 100 && battery > 9){
    M5.Lcd.print(" ");
  }
  else if(battery < 9){
    M5.Lcd.print("  ");
  }
  if (battery<10){
    M5.Axp.DeepSleep();
  }
  M5.Lcd.print(battery);
  M5.Lcd.print("%");

  

}
