#include <Keypad.h>
#include <LiquidCrystal.h>
#include<Servo.h>


#define led 6
#define trig 1
#define echo 0
#define ldr A1
#define heat_value A0
#define PASSWORD_LENGTH 6
#define ONE_SEC 1000
#define TWO_SEC 2000
#define FIVE_VOLTS 5.0
#define MAXIMUM_VALUE 255
#define LEAST_VALUE 0


Servo myservo;

const int rs = 12, en = 11, d4 = 5 , d5 = 4, d6 = 3, d7 = 2 ;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

char pen[] = {'1'};
const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
//left pins
byte rowPins[COLS] = {A5, A4, A3, A2};
//right pins
byte colPins[ROWS] = {13, 7, 8, 9};                                                             
char key = '0';
char customKey = 0;
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);



int record, angle, temp, t, dist, i = 0, counter = 0, res = 0;
float volt;
bool opened = false;
unsigned long time1 = 0;
// REQUIRED PASSWORD
char pass[PASSWORD_LENGTH] = "123456";                                                          
char EnteredPass[PASSWORD_LENGTH];

void setup() {
  lcd.begin(16, 2);
  pinMode(led, OUTPUT);
  pinMode(heat_value, INPUT);
  pinMode(ldr, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  time1 = millis();
  myservo.attach(10);
  myservo.write(0);
}

void loop() {
  key = '0';
  customKey = customKeypad.getKey();
  if (customKey > '0' && customKey != 'D' && customKey != '#')
  {
    lcd.print("*");
    //ENTERING THE PASSWORD VALUES ONE BY ONE
    EnteredPass[i] = customKey;
    i++;
  }
  //WHEN D PRESSED CHECK FOR PASS
  else if (customKey == 'D')                                                         
  {
    if (i == 6)
    {
      for (int j = 0; j < PASSWORD_LENGTH; j++)
      {
        if (EnteredPass[j] == pass[j])
        {
          //COUNTER FOR HOW MANY NUMBERS ARE TRUE IN THE ENTERED PASS
          counter++;                                                                 
        }
      }
      //PASSWORD IS TRUE
      if (counter == PASSWORD_LENGTH)                                                
      {
        lcd.setCursor(0, 0);
        lcd.print("Right pass  :)");
        delay(1000);
        while (key != '#')
        {
          key = customKeypad.getKey();

          if (millis() - time1 >= ONE_SEC)
          {
            welcome();
            ultrasonic();
            counter = 0;
            if (dist < 10)
            {
              //CALCULATING TEMP
              HeatSensor();   
              //LIGHT SENSOR                                                          
              LDR();      
              //LIGHTS                                                              
              open_lights();  
              //SERVO ANGLE MOVES FROM ZERO TO NINTY                                                          
              open_door();                                                              
              opened=true;
            }
            else
            {
              if(opened==true)
              {
                //CALCULATE ROOM TEMPRATURE
                HeatSensor();  
                //READ LDR VALUE                                                           
                LDR();      
                //IF IT'S DARK OPEN LIGHTS                                                              
                open_lights();                                                            
                myservo.write(90);                                                        
                }else{
                clear();
                close_door();
              }
            }
            time1 = millis();
          }
        }
        analogWrite(led, 0);

      } 
       //IF PASSWORD LENTGH IS NOT EQUAL SIX SO ITS ALREADY WRONG
      else                                                                         
      {
        //PRINT WRONG PASSWORD ON LCD
        Wrongpass();                                                                  
      }
    }
    //IF PASSWORD EQUAL SIX
    else                                                                              
    {
      //PRINT WRONG PASSWORD ON LCD
      Wrongpass();                                                                    
    }
  }
  //ENTER PASSWORD AGAIN IF # IS PRESSED
  else if (customKey == '#')                                                        
  {
    //CLEAR LCD 
    clear();  
    //SERVO ANGLE MOVES FROM NINTY TO ZERO TO CLOSE THE DOOR                                                                        
    close_door();                                                                     
  }

}




void HeatSensor() {
  record = analogRead(heat_value);
  volt = (FIVE_VOLTS / 1023.0) * record;
  temp = volt / 0.01;
  lcd.setCursor(0, 1);
  lcd.print(temp);
}


void LDR() {

  res = analogRead(ldr);
  //lcd.setCursor(5,1);
  // lcd.print(res);

}


void Wrongpass() {
  lcd.setCursor(0, 0);
  lcd.print("Wrong pass -_-");
  lcd.setCursor(0, 1);
  lcd.print("Thief");
  i = 0;
  delay(ONE_SEC);
  lcd.clear();

}


void clear() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  i = 0;
  lcd.clear();
}


void ultrasonic() {
  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  t = pulseIn(echo, HIGH);
  dist = t / 57;
}


void open_door() {
  for (int i = 0; i <= 90; i++)
  {
    myservo.write(i);
  }
}


void close_door() {
  for (int i = 90; i >= 0; i--)
  {
    myservo.write(i);
  }
}


void open_lights() {
  if (res > 500)
    analogWrite(led, LEAST_VALUE);
  else if (res < 100)
    analogWrite(led, MAXIMUM_VALUE);
  else if (res < 500 && res > 100)
    analogWrite(led, (MAXIMUM_VALUE - res / 2));                                      

}


void welcome(){
   lcd.setCursor(0, 0);
   lcd.print("Welcome home");
}
