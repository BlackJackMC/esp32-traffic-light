#pragma once

#include "cloud_var.h"
#include "mqtt.h"
#include "env.h"

#include <map>
#include <vector>

namespace cloud
{
    extern std::vector<CloudVarBase *> variable;

#define add(v, ...) _add(VARIABLE_TOPIC"/"#v, v, __VA_ARGS__)

    void _add(String name, int &v, Permission permission = Permission::ReadWrite, Priority priority = Priority::Cloud, Update_Policy update_policy = Update_Policy::Change, callback_t on_sync = []() {}, callback_t on_receive = []() {});
    void _add(String name, double &v, Permission permission = Permission::ReadWrite, Priority priority = Priority::Cloud, Update_Policy update_policy = Update_Policy::Change, callback_t on_sync = []() {}, callback_t on_receive = []() {});
    void _add(String name, float &v, Permission permission = Permission::ReadWrite, Priority priority = Priority::Cloud, Update_Policy update_policy = Update_Policy::Change, callback_t on_sync = []() {}, callback_t on_receive = []() {});
    void _add(String name, bool &v, Permission permission = Permission::ReadWrite, Priority priority = Priority::Cloud, Update_Policy update_policy = Update_Policy::Change, callback_t on_sync = []() {}, callback_t on_receive = []() {});
    void _add(String name, String &v, Permission permission = Permission::ReadWrite, Priority priority = Priority::Cloud, Update_Policy update_policy = Update_Policy::Change, callback_t on_sync = []() {}, callback_t on_receive = []() {});
    void setup();
    void loop();
}