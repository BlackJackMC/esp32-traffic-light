#ifndef HTTP_MANAGER_H
#define HTTP_MANAGER_H

#include <Arduino.h>
#include <HTTPClient.h>
#include <Wifi.h>

namespace Client_manager
{
    class http_manager 
    {
    private:
        WiFiClient w_client;
        String server_name;
    public:
        http_manager();
        http_manager(String);

        bool Wifi_connect(String, String);
        int send_state(String, String);
    };
}

#endif