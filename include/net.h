#ifndef NET_H
#define NET_H

#include <WiFiClientSecure.h>
#include "env.h"

namespace net
{
    extern int status;

    extern WiFiClientSecure wifi;

    void read_response();
    void printWifiStatus();
    void loop();
    void setup();
}

#endif