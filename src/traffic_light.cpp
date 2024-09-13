#include "traffic_light.h"

traffic_light::traffic_light(){}
traffic_light::traffic_light(String name): name(name) {}

traffic_light& traffic_light::begin(uint8_t red_led_pin, uint8_t green_led_pin, uint8_t yellow_led_pin, client_manager::http_manager& client, int state = 0) 
{
    const static state_t state_table[] PROGMEM = {
        /*               ON_ENTER,        ON_LOOP, ON_EXIT,         EVT_TIMER,  ELSE*/
        /* RED */        ENT_RED,         -1,      EXT_CHANGE,      RED_YELLOW,  -1,
        /* RED_YELLOW*/  ENT_RED_YELLOW,  -1,      EXT_CHANGE,      GREEN,       -1,
        /* GREEN */      ENT_GREEN,       -1,      EXT_CHANGE,      GREEN_BLINK, -1,
        /* GREEN_BLINK*/ ENT_GREEN_BLINK, -1,      EXT_CHANGE,      YELLOW,      -1,
        /* YELLOW */     ENT_YELLOW,      -1,      EXT_CHANGE,      RED,         -1
    };

    Machine::begin(state_table, ELSE);

    this->client = client;
    this->red.begin(red_led_pin, true);
    this->green.begin(green_led_pin, true);
    this->yellow.begin(yellow_led_pin, true);
    this->state(state); //Start the event loop with a particular state (default: 0)
    return *this;
}

int traffic_light::event(int id)
{
    switch (id)
    {
        case EVT_TIMER:
            return timer.expired(this);
    }

    return 0;
}

void traffic_light::action(int id)
{
    switch (id)
    {
        case ENT_RED:
            red.on();
            green.off();
            yellow.off();
            timer.set(7000);
        case ENT_RED_YELLOW:
            red.on();
            green.off();
            yellow.on();
            timer.set(3000);
        case ENT_GREEN:
            red.off();
            green.on();
            yellow.off();
            timer.set(10000);
        case ENT_GREEN_BLINK:
            red.off();
            green.blink(500, 500, 2);
            yellow.off();
            timer.set(2000);
        case ENT_YELLOW:
            red.off();
            green.off();
            yellow.on();
            timer.set(3000);
        case EXT_CHANGE:
            client.send_state(name, event_name[state()]);
    }
}

traffic_light& traffic_light::cycle()
{
    red.cycle();
    green.cycle();
    yellow.cycle();

    return *this;
}