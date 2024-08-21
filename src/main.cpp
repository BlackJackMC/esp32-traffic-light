#include "state_control.h"
#include <Arduino.h>
#include <map>

using State_control::traffic_light, State_control::state;

const uint8_t STATE_COUNT = 8;

const int buzzer = 13; // Why

std::map<String, uint64_t> duration = {
  {"red", 7000},
  {"red yellow", 3000},
  {"green", 10000},
  {"green blink1", 500},
  {"green blink2", 500},
  {"green blink3", 500},
  {"green blink4", 500},
  {"yellow", 3000}
};

std::vector<uint8_t> south_pin = {4, 16, 17}, west_pin = {5, 18, 19};

// [led][G = 0, Y = 1, R = 2]
traffic_light south("south",south_pin, duration), west("west",west_pin, duration);

// volatile unsigned long long curr_time;

void setup()
{
    for (int i=0;i<3;i++) {
        pinMode(south_pin[i],OUTPUT);
        pinMode(west_pin[i],OUTPUT);
    }
    south.set_state(0);
    west.set_state(3);
    uint64_t cur = millis();
    south.set_time(cur);
    west.set_time(cur);
    // digitalWrite(4, HIGH);
}

void loop()
{
    south.change();
    west.change();
}