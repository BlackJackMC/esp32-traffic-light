#include "net.h"

namespace net
{
    int status = WL_IDLE_STATUS;

    WiFiClientSecure wifi;

    void read_response()
    {
        uint32_t received_data_num = 0;
        while (wifi.available())
        {
            char c = wifi.read();
            Serial.print(c);
            received_data_num++;
            if (received_data_num % 80 == 0)
            {
                Serial.println();
            }
        }
    }

    void printWifiStatus()
    {
        IPAddress ip = WiFi.localIP();

        Serial.print("SSID: ");
        Serial.println(WiFi.SSID());

        Serial.print("IP Address: ");
        Serial.println(ip);

        long rssi = WiFi.RSSI();
        Serial.print("signal strength (RSSI):");
        Serial.print(rssi);
        Serial.println(" dBm");
    }

    void setup()
    {

        Serial.print("Network: ");

        WiFi.mode(WIFI_STA);
        wifi.setCACert(CERTIFICATE);

        while (status != WL_CONNECTED)
        {
            // Try to connect to one of the wifi
            for (const auto &wifi : WIFI_LIST)
            {
                Serial.println(wifi.first);
                status = WiFi.begin(wifi.first, wifi.second);
                delay(15000);
                if (status == WL_CONNECTED)
                    break;
            }
        }

        Serial.println("Connected");
    }

    void loop()
    {
        if (!wifi.connected()) setup();
    }
}