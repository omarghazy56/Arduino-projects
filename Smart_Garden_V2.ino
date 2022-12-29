#include<LiquidCrystal.h>

#define ldr A0  //Photosensor
#define lm A1 //Temprature sensor
#define moisture A2 //moisture sensor
#define led 9   //led
#define relay 3 //relay

#define Moisture_Max 85
#define Temp_Ref 40

const int en=11,rs=12,d4=4,d5=5,d6=6,d7=7;
float lm_value= 0;
int ldr_value = 0  , moisture_value = 0;
double moisture_percent = 0 , light_level = 0;

LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

void setup() {
  pinMode(ldr,INPUT);
  pinMode(lm,INPUT);
  pinMode(moisture,INPUT);
  pinMode(led,OUTPUT);
  pinMode(relay,OUTPUT);  

  //lcd setup
  lcd.begin(16 , 2); 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Computing.......");
  lcd.setCursor(0,1);

  //serial setup
  Serial.begin(9600);
  //initiate relay_value = 0;
  digitalWrite(relay,HIGH);
  delay(1000);
}

void loop() {
  //clearing lcd
  lcd.clear();
  //ldr Code
  LDR();
  

  //lm code
  LM();
  

  //moisture Code
  MOISTURE();
  
  Serial.println("---------------");


  /***********************************************SYSTEM CODE***************************************************/
  //Summer case
  if(lm_value>=Temp_Ref and (ldr_value>180 and ldr_value<550) and moisture_percent<=Moisture_Max )
  {
      for(int i=0 ; i<3 ; i++)
      {
        //relay_value=1;
        digitalWrite(relay,LOW);
        delay(2000);
        //relay_value=0;
        digitalWrite(relay,HIGH);
        delay(1000);
      }
      Serial.println("Summer Case");
  }
  //Winter case
  else if(lm_value < Temp_Ref and (ldr_value > 180 and ldr_value < 550) and moisture_percent<=Moisture_Max )
  {
    for(int i=0;i<2;i++)
      {
        //relay_value=1;
        digitalWrite(relay,LOW);
        delay(2000);
        //relay_value=0;
        digitalWrite(relay,HIGH);
        delay(1000);
      }
      Serial.println("Winter Case");
  }
  else
  //Defualt case
  {
    //relay_value=0;
    digitalWrite(relay,HIGH);
    Serial.println("Defult Case");
  }
  delay(3000);
}


void LM()
{
  lm_value=analogRead(lm);
  lm_value*=500/1023.0;
  Serial.println("lm Value: "+String(lm_value));
  lcd.setCursor(6,0);
  lcd.print("T:"+String(lm_value));
}

void LDR()
{
  ldr_value = analogRead(ldr);
  Serial.println("LDR Value: "+String(ldr_value));
  light_level = ldr_value*255/1023.0;
  analogWrite(led,light_level);
  lcd.setCursor(0,0);
  lcd.print("L:"+String(ldr_value));
}

void MOISTURE()
{
  moisture_value = analogRead(moisture);
  moisture_percent = (100-(moisture_value/1023.0)*100);
  Serial.println("moisture value: "+String(moisture_percent));
  lcd.setCursor(12,0);
  lcd.print("M:"+String(moisture_percent));
}
