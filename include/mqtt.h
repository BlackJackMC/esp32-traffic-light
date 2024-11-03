#pragma once

#include <functional>
#include <map>

#include <Arduino.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>


#include "env.h"
#include "net.h"

namespace mqtt
{
    using callback_t = std::function<void(String)>;
    
    extern std::map<String, callback_t> callback;
    extern PubSubClient client;
    extern int last_broker_index;

    void handler(char *topic, byte *buffer, size_t length);
    void on(String topic, callback_t f);
    void publish(String topic, String message);
    void setup();
    void loop();
}