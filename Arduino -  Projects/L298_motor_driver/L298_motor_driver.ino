#include "M_Config.h"
#include "M_interface.h"

//initialization for driver pins #Newir
void Motor_init()
{
  //init. all pins #Newir
  for(int i=0;i<M_Number;i++){
    for(int j=0;j<3;j++)
    {
      pinMode(H_bridge_Pins[i][j],OUTPUT);
    }
  }
}
//set L298 state #Newir
void L298_Driver(byte Motor_number,byte Direction,int INPUT_motor_speed)
{

  int Motor_speed = map(INPUT_motor_speed,0,100,0,255);
  if(Direction == clockwise)/*clockwise direction #Newir  3gbk kdah :) ?? -> spring 2023 *//* i remember you kept telling me the driver stil need more optimization 
  										 and it didn't bother me, i was very happy to just talk to you,
  										 yeah i love you until now after what you did, maybe i am angry with you. 
  										 you know me for 3 years and take this action to me without even telling me or discuss it with me ?!!,
  										 i didn't do anything wrong, just loving you with my deepest heart !! -> sep4/2024 */  
              {
                digitalWrite(H_bridge_Pins[Motor_number][0],HIGH);
                digitalWrite(H_bridge_Pins[Motor_number][1],LOW);
                analogWrite(H_bridge_Pins[Motor_number][2],Motor_speed);  
              }
  else if(Direction == counter_clockwise)//counter_clockwise direction #Newir
              {
                digitalWrite(H_bridge_Pins[Motor_number][0],LOW);
                digitalWrite(H_bridge_Pins[Motor_number][1],HIGH);
                analogWrite(H_bridge_Pins[Motor_number][2],Motor_speed);
              }
  else if(Direction == M_stop) //stop motor #Newir
              {
                digitalWrite(H_bridge_Pins[Motor_number][0],LOW);
                digitalWrite(H_bridge_Pins[Motor_number][1],LOW);
                analogWrite(H_bridge_Pins[Motor_number][2],0);                
              }
}
