#pragma once
#include <Arduino.h>
#include <array>
#include <map>

namespace State_control 
{
  using callback = std::function<void()>;
  class state
  {
  public:
    callback run;
    String name;
    uint64_t duration;

    state();
    state(callback, String, uint64_t);

    void set_callback(callback);
    void set_name(String);
    void set_duration(uint64_t);
  };

  class traffic_light
  {
  private:
    const state null_state;
    std::vector<state> state_list;
    std::vector<uint8_t> LED;
    uint64_t start_time;
    uint32_t curr_state;
    uint32_t state_count;
    String name;

  public:
    traffic_light();
    traffic_light(String,std::vector<uint8_t>,std::map<String,uint64_t>);

    bool change();
    void set_state(uint32_t);
    void set_time(uint64_t);
    String get_name();
  };
}
