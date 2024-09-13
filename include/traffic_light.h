#pragma once

#include <Automaton.h>
#include <vector>
#include "http_manager.h"

class traffic_light : public Machine
{
public:
    traffic_light();
    traffic_light(String name);
    traffic_light& begin(uint8_t red_led_pin, uint8_t green_led_pin, uint8_t yellow_led_pin, client_manager::http_manager& client, int state);
    int event(int id);
    void action(int id);
    traffic_light& cycle();
    String name;
private:
    enum STATES { RED, RED_YELLOW, GREEN, GREEN_BLINK, YELLOW }; //States
    enum EVENTS { EVT_TIMER, ELSE }; //Events
    enum ACTION { ENT_RED, ENT_RED_YELLOW, ENT_GREEN, ENT_GREEN_BLINK, ENT_YELLOW, EXT_CHANGE };  //Action for states
    Atm_led red;
    Atm_led green;
    Atm_led yellow;
    atm_timer_millis timer;
    client_manager::http_manager client;
    const std::vector<String> event_name = {"red", "red yellow", "green", "blink", "yellow"}; //Need to dependency injection
};