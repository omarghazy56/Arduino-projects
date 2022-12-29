#include <Stepper.h>
const int stepsPerRevolution = 200;
Stepper hand(stepsPerRevolution, 2,3);
Stepper base(stepsPerRevolution, 4,5);

#define ldr_TL A7
#define ldr_TR A5
#define ldr_BL A6
#define ldr_BR A4
#define Sunlight_Value 500
#define Area_Light 2000

int ldr_TL_Value = 0 , ldr_TR_Value = 0 , ldr_BL_Value = 0, ldr_BR_Value =0 , sum = 0;

void setup() {
  hand.setSpeed(800);
  pinMode(ldr_TL, INPUT);
  pinMode(ldr_TR, INPUT);
  pinMode(ldr_BL, INPUT);
  pinMode(ldr_BR, INPUT);
  Serial.begin(9600);

}

void loop() {
  LDR();
  sum = ldr_TL_Value + ldr_TR_Value + ldr_BL_Value + ldr_BR_Value ;
  //TO TEST LDR OUTPUTS
  /*Serial.print("LDR_TL :");
  Serial.print(ldr_TL_Value);
  Serial.print(" , ");
  Serial.print("LDR_TR :");
  Serial.print(ldr_TR_Value);
  Serial.print(" , ");
  Serial.print("LDR_BL :");
  Serial.print(ldr_BL_Value);
  Serial.print(" , ");
  Serial.print("LDR_BR :");
  Serial.println(ldr_BR_Value);
  */
  if(sum < Area_Light)
  {
    if(ldr_TL_Value > Sunlight_Value && ldr_BL_Value > Sunlight_Value && ldr_TR_Value < Sunlight_Value && ldr_BR_Value < Sunlight_Value)
    {
      //base motor go left
      Left();
    }
    else if(ldr_TL_Value < Sunlight_Value && ldr_BL_Value < Sunlight_Value && ldr_TR_Value > Sunlight_Value && ldr_BR_Value > Sunlight_Value)
      {
        //base motor go right
        Right();
      }
    else if(ldr_TL_Value > Sunlight_Value && ldr_BL_Value < Sunlight_Value && ldr_TR_Value > Sunlight_Value && ldr_BR_Value < Sunlight_Value)
    {
      //hand motor go forward
      Forward();
    }
    else if(ldr_TL_Value < Sunlight_Value && ldr_BL_Value > Sunlight_Value && ldr_TR_Value < Sunlight_Value && ldr_BR_Value > Sunlight_Value)
    {
      //hand motor go backward
      Backward();
    }
  }
  
}

void LDR()
{
  ldr_TL_Value = analogRead(ldr_TL);
  ldr_TR_Value = analogRead(ldr_TR);
  ldr_BL_Value = analogRead(ldr_BL);
  ldr_BR_Value = analogRead(ldr_BR);
}

void Forward()
{
  hand.setSpeed(800);
  Serial.println("forward");
  hand.step(stepsPerRevolution);
}

void Backward()
{
  hand.setSpeed(800);
  Serial.println("back");
  hand.step(-stepsPerRevolution);
}

void Left()
{
  base.setSpeed(800);
  Serial.println("right");
  base.step(stepsPerRevolution); 
}

void Right()
{
  base.setSpeed(800);
  Serial.println("right");
  base.step(-stepsPerRevolution); 
}
