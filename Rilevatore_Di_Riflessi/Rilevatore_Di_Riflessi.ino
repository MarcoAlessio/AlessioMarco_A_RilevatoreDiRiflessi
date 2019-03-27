#include <LiquidCrystal_I2C.h>

//Dichiaro le variabili globali
int button_start;
int button_led;
int button_buzzer;
int buzzer;
int led;
int RED;
int GREEN;

//Creo due variabili d'appoggio che assumeranno rispettivamente il valore in millisecondi del tempo di risposta di led e buzzer
int result_led;
int result_buzzer;

LiquidCrystal_I2C lcd(0x27, 16, 2);

//Assegno le variabili nel setup
void setup(){
  button_start   = 4;
  button_led     = 5;
  button_buzzer  = 6;
  buzzer         = 7;
  led            = 8;
  RED            = 10;
  GREEN          = 11;
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
int generic_loop(int object, int button, int row, String test_number){
  delay(random(2000, 8500));
  digitalWrite(object, HIGH);
  int result = 0;
  while(digitalRead(button)== LOW){
    result++;
    delay(1);
  }
  digitalWrite(object, LOW);
  lcd.setCursor(0, row);
  lcd.print(test_number);
  lcd.print(result);
  lcd.print("ms");
  return result;
}

//Creo il metodo per l'esito finale del test di riflessi
void outcome(){
    if(result_led <= 500 && result_buzzer <= 500){
      digitalWrite(GREEN, HIGH);
      delay(2500);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("TEST PASSATO CON");
      lcd.setCursor(0, 1);
      lcd.print("SUCCESSO");
    }
    else{
      digitalWrite(RED, HIGH);
      delay(2500);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("TEST NON PASSATO");
      lcd.setCursor(0, 1);
      lcd.print("   !RIPROVA!");
    }
    delay(3500);
    lcd.clear();
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, LOW);
}

//Metodo del messaggio d'errore
void error_message(String type_test){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TEST ");
  lcd.print(type_test);
  lcd.setCursor(0, 1);
  lcd.print("NON VALIDO");
  delay(3500);
  lcd.clear();
}

//Nel loop inserisco prima un if che fa partire i cicli solo se il button_start viene premuto, dopo il primo ciclo per il led e subito dopo il controllo che convalida il test.
//Ripeto lo stesso ciclo anche per il buzzer e solo se entrambi i test sono validi subentra il ciclo per l'esito
void loop(){
  lcd.setCursor(0, 0);
  lcd.print("INIZIA IL TEST");
  if(digitalRead(button_start)== HIGH){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("TEST INIZIATO");
    delay(2000);
    lcd.clear();
    result_led = generic_loop(led, button_led, 0, "TEMPO 1: ");
    if(result_led <= 100)
      error_message("DEL LED");
    else{
      result_buzzer = generic_loop(buzzer, button_buzzer, 1, "TEMPO 2: ");
      if(result_buzzer <= 100)
        error_message("DEL BUZZER");
      else
        outcome(); 
    }
  }
}
