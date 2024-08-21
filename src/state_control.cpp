#include "state_control.h"

using namespace State_control;

state::state() {}
state::state(callback run, String name, uint64_t duration) : run(run), name(name), duration(duration) {}
void state::set_callback(callback run) { this -> run = run; }
void state::set_name(String name) { this->name = name; }
void state::set_duration(uint64_t duration) { this->duration = duration; }

traffic_light::traffic_light() {}
traffic_light::traffic_light(String name,std::vector<uint8_t> led,std::map<String,uint64_t> duration): name(name), start_time(0), curr_state(-1), LED(led), state_count(duration.size()),
                                        null_state([this](){
                                          for (const auto &i: LED) digitalWrite(i, LOW);
                                        }, "null", 0) 
{
  state_list = {
    state([this](){digitalWrite(LED[2], HIGH);}, "red", duration["red"]),
    state([this](){digitalWrite(LED[1], HIGH); digitalWrite(LED[2], HIGH);}, "red yellow", duration["red yellow"]),
    state([this](){digitalWrite(LED[0], HIGH);}, "green", duration["green"]),
    state([this](){digitalWrite(LED[0], HIGH);}, "green blink1", duration["green blink1"]),
    state([this](){}, "green blink2", duration["green blink2"]),
    state([this](){digitalWrite(LED[0], HIGH);}, "green blink3", duration["green blink3"]),
    state([this](){}, "green blink4", duration["green blink4"]),
    state([this](){digitalWrite(LED[1], HIGH);}, "yellow", duration["yellow"]),
  };
}

bool traffic_light::change() 
{
  uint64_t curr = millis();

  if (traffic_light::curr_state == -1 or curr - traffic_light::start_time >= state_list[curr_state].duration)
  {
    start_time = curr;
    traffic_light::null_state.run();
    curr_state = (curr_state + 1) % state_count;
    state_list[curr_state].run();
    traffic_light::name = state_list[curr_state].name;
    return true;
  }
  return false;
}

void traffic_light::set_state(uint32_t start_state) {  curr_state = start_state; }
void traffic_light::set_time(uint64_t start_time) { this->start_time = start_time; }
String traffic_light::get_name() { return this->name; }

