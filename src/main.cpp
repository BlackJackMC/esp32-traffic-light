#include <Arduino.h>
#include <Automaton.h>
#include "http_manager.h"
#include "traffic_light.h"


traffic_light south("south");
traffic_light west("west");

client_manager::http_manager client;

void setup()
{
    south.begin(17, 4, 16, client, 0);
    west.begin(5, 19, 18, client, 3);

    automaton.add(south);
    automaton.add(west);
}

void loop()
{
    automaton.run();
}