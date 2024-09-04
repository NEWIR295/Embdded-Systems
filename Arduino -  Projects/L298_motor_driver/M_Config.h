//define esp32 pins connected to L298 state #Newir
#ifndef M_config
#define M_config

#define M_Number 6 // set n of motors

// for 1st h-bridge //new update #NEWIR
#define In1_HB1 8
#define In2_HB1 9
#define M1_speed_HB1 10 
#define In3_HB1 4
#define In4_HB1 5
#define M2_speed_HB1 7 

// for 2nd h-bridge //new update #NEWIR
#define In1_HB2 11
#define In2_HB2 12
#define M3_speed_HB2 13 
#define In3_HB2 20
#define In4_HB2 21
#define M4_speed_HB2 22

// for 3nd h-bridge //new update #NEWIR
#define In1_HB3 30
#define In2_HB3 31
#define M5_speed_HB3 38 
#define In3_HB3 34
#define In4_HB3 35
#define M6_speed_HB3 37

#endif
