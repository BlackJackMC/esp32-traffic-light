#include <Arduino.h>

import state_control;

// [led][G = 0, Y = 1, R = 2]
traffic_light south({4, 16, 17}), west({5, 18, 19});


volatile unsigned long long curr_time;

void setup()
{
}

void loop()
{
}