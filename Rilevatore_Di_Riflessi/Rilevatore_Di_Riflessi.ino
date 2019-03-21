#include <LiquidCrystal_I2C.h>
#define led 8
#define pulsante1 4
#define pulsante2 5
#define pulsante3 6
#define buzzer 7
#define VERDE 10
#define ROSSO 11
#define BLU 12
int counter = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup(){
  pinMode(led, OUTPUT);
  pinMode(VERDE, OUTPUT);
  pinMode(ROSSO, OUTPUT);
  pinMode(BLU, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(pulsante1, INPUT);
  pinMode(pulsante2, INPUT);
  pinMode(pulsante3, INPUT);
  lcd.init();
  lcd.backlight();
}

void ciclo(int oggetto, int pulsante, int riga){
  delay(random(2000, 15000));
  digitalWrite(oggetto, HIGH);
  if(oggetto == buzzer)
    counter = 0;
  while(digitalRead(pulsante)== LOW){
    counter++;
    delay(1);
  }
  digitalWrite(buzzer, LOW);
  lcd.setCursor(0, riga);
  lcd.print(counter);
  lcd.print("ms");
  if(counter <= 500)
    digitalWrite(ROSSO, HIGH);
  else
    digitalWrite(VERDE, HIGH);
}

void loop(){
  if(digitalRead(pulsante1)== HIGH){
     ciclo(led, pulsante2, 0);
     ciclo(buzzer, pulsante3, 1);
  }
}
