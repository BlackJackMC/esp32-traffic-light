#include "mqtt.h"

namespace mqtt
{
    using callback_t = std::function<void(String)>;

    std::map<String, callback_t> callback;
    PubSubClient client(net::wifi);
    int last_broker_index = 0;

    void handler(char *topic, byte *buffer, size_t length)
    {
        String temp((char *)buffer, length);
        auto loc = callback.find(String(topic));
        JsonDocument data;
        DeserializationError e = deserializeJson(data, temp);

        if (e)
        {
            Serial.print("Error while parsing incoming message: ");
            Serial.println(e.f_str());
            return;
        }

        if (data["id"] == ID)
            return;

        if (loc != callback.end())
            loc->second(data["message"]);
        else
            Serial.println("[mqtt] No callback registered for topic: " + String(topic));
    }

    void on(String topic, callback_t f)
    {
        auto loc = callback.find(topic);
        if (loc == callback.end())
        {
            client.subscribe(topic.c_str());
            callback[topic] = f;
            Serial.println("[mqtt] Subscribed to " + topic);
        }
        else
        {
            loc->second = f;
        }
    }

    void publish(String topic, String message)
    {
        JsonDocument data;
        String buffer;
        data["id"] = ID;
        data["message"] = message;
        serializeJson(data, buffer);
        client.publish(topic.c_str(), buffer.c_str());
    }

    void connect()
    {
        client.disconnect();
        while (!client.connected())
        {
            // Cycle through every mqtt broker save the last mqtt broker that was attempted to connect
            auto mqtt = MQTT_LIST[last_broker_index];
            Serial.print(mqtt.first);
            Serial.print(" ");
            client.setServer(mqtt.first, mqtt.second);

            for (int i = 0; i < 5; i++) // Try to connect for 5 attempts
            {
                if (client.connect(ID, MQTT_USERNAME, MQTT_PASS))
                    break;
                else
                    Serial.print(client.state());
                    Serial.print(" ");
                delay(5000);
            }

            

            last_broker_index = (last_broker_index + 1) % MQTT_LIST.size();
        }

        Serial.println("Connected");
    }

    void loop()
    {
        if (!client.connected()) setup();
        client.loop();
    }

    void setup()
    {
        Serial.print("[mqtt]:");
        client.setStream(Serial)
              .setCallback(handler);
        connect();
    }
}