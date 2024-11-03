#include "state_control.h"
#include "env.h"
#include "cloud.h"
#include "net.h"
#include "mqtt.h"
#include <WiFi.h>
#include <Arduino.h>
#include <map>

using State_control::traffic_light, State_control::state;

/*==================================================*/

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
    {"yellow", 3000}};
// [led][G = 0, Y = 1, R = 2]
std::vector<uint8_t> south_pin = {4, 16, 17}, west_pin = {19, 18, 5};

traffic_light south("south", south_pin, duration), west("west", west_pin, duration);

String south_state, west_state;

void setup()
{
    Serial.begin(9600);
    for (int i = 0; i < 3; i++)
    {
        pinMode(south_pin[i], OUTPUT);
        pinMode(west_pin[i], OUTPUT);
    }
    south.set_state(0);
    west.set_state(3);
    uint64_t cur = millis();
    south.set_time(cur);
    west.set_time(cur);

    net::setup();
    mqtt::setup();

    cloud::add(south_state, Permission::Read, Priority::Local, Update_Policy::Change);
    cloud::setup();
}

void loop()
{
    net::loop();
    mqtt::loop();
    if (south.change())
        Serial.print("South ");
    if (west.change())
        Serial.print("West ");
    south_state = south.get_state();
    west_state = west.get_state();
}