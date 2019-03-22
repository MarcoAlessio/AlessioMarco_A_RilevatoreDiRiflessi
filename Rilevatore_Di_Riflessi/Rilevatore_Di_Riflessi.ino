#include <LiquidCrystal_I2C.h>

//Dichiaro le variabili e le assegno
#define button_start   4
#define button_led     5
#define button_buzzer  6
#define buzzer         7
#define led            8
#define RED           10
#define GREEN         11

//Creo due variabili d'appoggio che assumeranno rispettivamente il valore in millisecondi del tempo di risposta di led e buzzer
int result1;
int result2;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup(){
  pinMode(led, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(button_start, INPUT);
  pinMode(button_led, INPUT);
  pinMode(button_buzzer, INPUT);
  lcd.init();
  lcd.backlight();
}

//Creo un unico ciclo int, così facendo posso estrapolare alla fine del primo ciclo il tempo di riflesso del led e assegnarlo a result1, nel secondo estrapolare il tempo di riflesso 
//del buzzer e assegnarlo a result2
int generic_loop(int object, int button, int row){
  delay(random(2000, 10000));
  digitalWrite(object, HIGH);
  int result = 0;
  while(digitalRead(button)== LOW){
    result++;
    delay(1);
  }
  digitalWrite(object, LOW);
  lcd.setCursor(0, row);
  lcd.print(result);
  lcd.print("ms");
  return result;
}

//Nel loop inserisco prima un if che fa partire i cicli solo se il button_start viene premuto, dopo i due cicli rispettivamente di led e buzzer inserisco un if che analizza i due
//risultati e se entrambi sono inferiori a 500ms fa accendere il led RGB di verde, altrimenti di rosso
void loop(){
  if(digitalRead(button_start)== HIGH){
    result1 = generic_loop(led, button_led, 0);
    result2 = generic_loop(buzzer, button_buzzer, 1);
    if(result1 <= 500 && result2 <= 500)
      digitalWrite(GREEN, HIGH);
    else
      digitalWrite(RED, HIGH);
    delay(3500);
    lcd.clear();
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, LOW);
  }
}
