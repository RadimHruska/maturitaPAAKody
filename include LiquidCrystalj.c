#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
void setup()
{

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

  pinMode(11, INPUT); //button
  pinMode(12, INPUT); //button

}
unsigned long previousMillis1 = 0;
int interval1 = 1000; 

int diody [8] = {2,3,4,5,6,7,8,9};
int btn1 = 11;
int btn2 = 12;
int state = 0;
int diodCount = 8;
int maxState = 7;
int posledniStav = 1;
int posledniStav1 = 1;
int stav = 1;
int stav1 = 1;
int asinc = 0;
int cs1 =0; 
int cs2 = 5;

void loop() 
{
  unsigned long currentMillis = millis();
  stav = digitalRead(btn1);
  if(stav != posledniStav)
    {
     
      if(stav != HIGH)
      {
        if(state < maxState)
        {
        state++;
          
        }
        else
        {
          state = 0;
        }
      }
      posledniStav = stav;
    }

  stav1 = digitalRead(btn2);
  if(stav1 != posledniStav1)
    {
     
      if(stav1 != HIGH)
      {
        if(state >0)
        {
        state--;
          
        }
        else
        {
          state = maxState;
        }
      }
      posledniStav1 = stav1;
    }

    if(digitalRead(btn1) == 0 && digitalRead(btn2) == 0)
    {
      state = 7;
    }


    if(state == 0)
    {
      for(int i = 0; i<diodCount; i++)
      {
        digitalWrite(diody[i], 1);
      }
    }
    else if(state == 1)
    {
      for(int i = 0; i<diodCount; i++)
      {
        if(i%2)
        {
          digitalWrite(diody[i], 1);
        }
        else
        {
          digitalWrite(diody[i], 0);
        }
        
      }
    }
    else if(state == 2)
    {
      if(asinc == 0)
      {
      for(int i = 0; i<diodCount; i++)
      {
      if(i%2)
        {
            digitalWrite(diody[i], 1);
        }
        else
        {
          digitalWrite(diody[i], 0);
        }
      }
      asinc = 1;
      }
      if (currentMillis - previousMillis1 >= interval1) {
    previousMillis1 = currentMillis;
      
      for(int i = 0; i<diodCount; i++)
      {

        if(i%2)
        {
            digitalWrite(diody[i], !digitalRead(diody[i]));
        }
        else
        {
          digitalWrite(diody[i], !digitalRead(diody[i]));
        }
        
      }

      }
    
    }
        else if(state == 3)
    {
       asinc = 0;
       if(cs1 == 7)
       {
          cs1 =0; 
       }
       if(cs2 == 7)
       {
          cs2 =0; 
       }

       if (currentMillis - previousMillis1 >= interval1) {
    previousMillis1 = currentMillis;
      
      for(int i = 0; i<diodCount; i++)
      {

        if(i== cs1 || i == cs1+4)
        {
            digitalWrite(diody[i], 1);
        }
        else
        {
          digitalWrite(diody[i], 0);
        }
        
      }
      Serial.print(cs1); 
cs1 ++;
      } 
      
    
    }
            else if(state == 5)
    {
       if (currentMillis - previousMillis1 >= interval1) {
    previousMillis1 = currentMillis;
      
      for(int i = 0; i<diodCount; i++)
      {

        if(i== cs1)
        {
            digitalWrite(diody[i], 1);
        }
        else
        {
          digitalWrite(diody[i], 0);
        }
        
      }
      Serial.print(cs1); 
cs1 ++;
       }
      
    }
    else
    {
       for(int i = 0; i<diodCount; i++)
      {
        digitalWrite(diody[i], 0);
      }
    }

     lcd.setCursor(0,0);
      lcd.print("Stav:");
     lcd.setCursor(0,1);
      lcd.print(state);


}

