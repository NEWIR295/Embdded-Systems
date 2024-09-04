#ifndef M_interference
#define M_interference

byte H_bridge_Pins[M_Number][3]= {
  {In1_HB1,In2_HB1,M1_speed_HB1},
  {In3_HB1,In4_HB1,M2_speed_HB1},
  {In1_HB2,In2_HB2,M3_speed_HB2},
  {In3_HB2,In4_HB2,M4_speed_HB2},
  {In1_HB3,In2_HB3,M5_speed_HB3},
  {In3_HB3,In4_HB3,M6_speed_HB3}
};
enum M_number{M1=0,M2=1,M3=2,M4=3,M5=4,M6=5};
enum M_direction{clockwise,counter_clockwise,M_stop};// motor dir #Newir
void Motor_init(); //initialization for driver pins #Newir
void L298_Driver(byte Motor_number,byte Direction,int M_speed);//set L298 state #Newir
/*  Motor numلer: takes M1, M2, M3 , M4 ,M5 or M6 
    Direction: takes clockwise, counter_clockwise, or M_stop
    M_speed: takes a value from 0 to 255 
*/
//enum H_Bridge_N{HB1=1,HB2=2}; // new update #NEWIR

#endif
