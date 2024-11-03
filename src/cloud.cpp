#include "cloud.h"

namespace cloud
{
    std::vector<CloudVarBase *> variable;

    void _add(String name, int &v, Permission permission, Priority priority, Update_Policy update_policy, callback_t on_sync, callback_t on_receive)
    {
        variable.push_back(new CloudVarInt(name, v, permission, priority, update_policy, on_receive, on_sync));
    }

    void _add(String name, float &v, Permission permission, Priority priority, Update_Policy update_policy, callback_t on_sync, callback_t on_receive)
    {
        variable.push_back(new CloudVarFloat(name, v, permission, priority, update_policy, on_receive, on_sync));
    }

    void _add(String name, double &v, Permission permission, Priority priority, Update_Policy update_policy, callback_t on_sync, callback_t on_receive)
    {
        variable.push_back(new CloudVarDouble(name, v, permission, priority, update_policy, on_receive, on_sync));
    }

    void _add(String name, bool &v, Permission permission, Priority priority, Update_Policy update_policy, callback_t on_sync, callback_t on_receive)
    {
        variable.push_back(new CloudVarBool(name, v, permission, priority, update_policy, on_receive, on_sync));
    }

    void _add(String name, String &v, Permission permission, Priority priority, Update_Policy update_policy, callback_t on_sync, callback_t on_receive)
    {
        variable.push_back(new CloudVarString(name, v, permission, priority, update_policy, on_receive, on_sync));
    }

    void setup()
    {
        for (const auto i : variable)
        {
            if (i->permission > Permission::Read)
                mqtt::on(i->name, [i](String message){ i->update_from_cloud(message); });
            i->set_cloud_update_callback([i](){ 
                // Serial.println("[cloud]: Update callback");
                mqtt::publish(i->name, i->stringify()); 
            });
            i->cloud_update_callback(); //For debugging
        }

        mqtt::publish(EVENT_TOPIC"/variable_update", "required");
    }

    void loop()
    {
        for (const auto i : variable)
            i->update();
    }
}