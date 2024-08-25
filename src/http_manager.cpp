#include "http_manager.h"
// #include <HTTPClient>

using namespace Client_manager;

http_manager::http_manager() {}
http_manager::http_manager(String server) : server_name(server) {}

bool http_manager::Wifi_connect(String ssid, String pass)
{
    WiFi.begin(ssid, pass);

    for (int i = 0; i < 10 and WiFi.status() != WL_CONNECTED; i++)
    {
        Serial.println(".");
        delay(500);
    }

    return (WiFi.status() == WL_CONNECTED);
    // {
    //     Serial.println("No wifi connection");
    //     return;
    // }

    // Serial.println("Wifi connected");
    // Serial.print("Address: ");
    // Serial.println(WiFi.localIP());
}

int http_manager::send_state(String light_name, String state_name)
{
    if (WiFi.status() == WL_CONNECTED) 
    {
        HTTPClient http;
        
        http.begin(w_client, server_name);

        http.addHeader("Content-Type", "application/json");

        String http_request_data = "{\"name\":\"" + light_name + "\",\"status\":\"" + state_name + "\"}";

        int http_response_code = http.POST(http_request_data);

        return http_response_code;
    }
    return false;
}
