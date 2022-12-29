//#include <SoftwareSerial.h>
//SoftwareSerial blu(1,2);
String reading;
#define lmf 7
#define lmr 8
#define rmf 9
#define rmr 10


char t;


void setup() {
  pinMode(lmf,OUTPUT);  //left motor forward 
  pinMode(lmr,OUTPUT);  //left motor reverse
  pinMode(rmf,OUTPUT);  //right motor forward
  pinMode(rmr,OUTPUT);  //right motor reverse
  Serial.begin(9600);
}

void loop() {
  if(Serial.available())
  {
    t=Serial.read();
    Serial.println(t);  
  }
  
  switch (t){
    case 'F':                         //IF F IS PRESSED MOVE FORWARD 

    digitalWrite(lmf,HIGH);
    digitalWrite(rmf,HIGH);
    digitalWrite(lmr,LOW);
    digitalWrite(rmr,LOW);

    case 'B':                       //IF B IS PRESSED MOVE BACKWARD
  
    digitalWrite(lmf,LOW);
    digitalWrite(rmf,LOW);
    digitalWrite(lmr,HIGH);
    digitalWrite(rmr,HIGH);
    
    case 'L' :                    //IF L IS PRESSED MOVE LEFT
    
    digitalWrite(lmf,LOW);
    digitalWrite(rmf,HIGH);
    digitalWrite(lmr,HIGH);
    digitalWrite(rmr,LOW);
    
    case 'R' :                   //IF R IS PRESSED MOVE RIGHT
    
    digitalWrite(lmf,HIGH); 
    digitalWrite(rmf,LOW);
    digitalWrite(lmr,LOW);
    digitalWrite(rmr,HIGH);

    case 'S' :                  //IF S IS PRESSED MOVE STOP TWO MOTORS  
    digitalWrite(lmf,LOW);
    digitalWrite(lmr,LOW);
    digitalWrite(rmf,LOW);
    digitalWrite(rmr,LOW);

}
}
