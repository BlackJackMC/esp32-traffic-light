#include "state_control.h"
#include "http_manager.h"
#include <Arduino.h>
#include <map>

using State_control::traffic_light, State_control::state, Client_manager::http_manager;

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
  {"yellow", 3000}
};
// [led][G = 0, Y = 1, R = 2]
std::vector<uint8_t> south_pin = {4, 16, 17}, west_pin = {19, 18, 5};

traffic_light south("south",south_pin, duration), west("west",west_pin, duration);

/*==================================================*/

String ssid = "Alterlake";
String pass = "134567892";
// String server = "hhtp://lhpsc.click/";
String server = "http://192.168.105.6:3000";
String endpoint = "/";

http_manager manager(server + endpoint);

/*==================================================*/

volatile bool flag = 0;

void setup()
{
    Serial.begin(9600);
    for (int i=0;i<3;i++) {
        pinMode(south_pin[i],OUTPUT);
        pinMode(west_pin[i],OUTPUT);
    }
    south.set_state(0);
    west.set_state(3);
    uint64_t cur = millis();
    south.set_time(cur);
    west.set_time(cur);

    if (manager.Wifi_connect(ssid,pass)) 
    {
        Serial.println("Connected");
    }
    else 
    {
        Serial.println("Not connected");
    }
    // digitalWrite(4, HIGH);
}

void loop()
{
    if (south.change())
    {
        Serial.print("South ");
        Serial.println(manager.send_state(south.get_name(),south.get_state()));
    }
    if (west.change()) 
    {
        Serial.print("West ");
        Serial.println(manager.send_state(west.get_name(),west.get_state()));
    }
}