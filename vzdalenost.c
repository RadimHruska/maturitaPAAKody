
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int trigPin = 11;
const int echoPin = 10;
unsigned long previousMillis = 0;
const int buzzer = 13;
int btn1 = 12;
int posledniStav = 1;
bool jedu = true;
bool stav = true;
int nevimco = 1;
int diody [8] = {2,3,4,5,6,7,8,9};
float duration, distance;
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(btn1, INPUT);
    lcd.init();
  lcd.clear();
  lcd.backlight();
  Serial.begin(9600);
  pinMode(2, OUTPUT); //dioda
  pinMode(3, OUTPUT); //dioda
  pinMode(4, OUTPUT); //dioda
  pinMode(5, OUTPUT); //dioda
  pinMode(6, OUTPUT); //dioda
  pinMode(7, OUTPUT); //dioda
  pinMode(8, OUTPUT); //dioda
  pinMode(9, OUTPUT); //dioda
}
void loop() {
  unsigned long currentMillis = millis();
  stav = digitalRead(btn1);
  if(stav != posledniStav)
    {
            if(stav != HIGH)
      {
      jedu = !jedu;
      }
      posledniStav = stav;
    }
if(jedu)
{    
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
   lcd.setCursor(0, 0);
  lcd.print("Distance:");
    lcd.setCursor(10, 0);
   lcd.print(distance);
  Serial.println(digitalRead(stav));
if (currentMillis - previousMillis >= distance * 10) {
  previousMillis = currentMillis;
    tone(buzzer, 1000);
    nevimco = distance/5;
    for(int i = 0; i<8; i++)
      {
        if(i < nevimco)
          digitalWrite(diody[i], 0); 
          else
          digitalWrite(diody[i], 1); 
      }
    }
    else
    {
       noTone(buzzer);
    }
}
else
{
  for(int i = 0; i<8; i++)
      {
          digitalWrite(diody[i], 0); 
      }
  noTone(buzzer);
}
}
