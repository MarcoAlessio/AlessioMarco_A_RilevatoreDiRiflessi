#include <LiquidCrystal_I2C.h>
#define led 8
#define pulsante1 2
#define pulsante2 4
#define pulsante3 6
#define verde 10
#define rosso 12

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup(){
  pinMode(led, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(rosso, OUTPUT);
  pinMode(pulsante1, INPUT);
  pinMode(pulsante2, INPUT);
  pinMode(pulsante3, INPUT);
  lcd.init();
  lcd.backlight();
}

void loop(){
  while (digitalRead(pulsante1) == HIGH) {
    lcd.setCursor(0, 0);
    lcd.print(millis());
    lcd.print("ms");
    delay(1000);
  }
  while (digitalRead(pulsante2) == HIGH){
    lcd.setCursor(0, 1);
    lcd.print(millis());
    lcd.print("ms");
    delay(1000);
  }
}
