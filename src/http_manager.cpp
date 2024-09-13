#include "http_manager.h"
#include "env.h"
// #include <HTTPClient>

using namespace client_manager;

http_manager::http_manager() {}
http_manager::http_manager(String server) : server_name(server) {}

bool http_manager::Wifi_connect(String ssid, String pass)
{
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    for (int i = 0; i < 10 and WiFi.status() != WL_CONNECTED; i++)
    {
        Serial.println(".");
        delay(500);
    }

    // w_client.setCACert(certificate);

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
    WiFiClientSecure *w_client = new WiFiClientSecure;
    w_client->setCACert(CERTIFICATE);
    if (WiFi.status() == WL_CONNECTED) 
    {
        HTTPClient http;
        
        // Serial.println(server_name);
        // http.addHeader("Content-Type", "application/x-www-form-urlencoded");
        // http.addHeader()
        state_name.replace(" ", "+");
        String http_request_data = "key=" KEY "&name=" + light_name + "&state=" + state_name; 
        http.begin(*w_client, server_name + "?" + http_request_data);
        Serial.println(server_name + "?" + http_request_data);

        int http_response_code = http.POST(http_request_data);

        return http_response_code;
    }
    return false;
}
