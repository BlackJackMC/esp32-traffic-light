#pragma once

#include <functional>
#include <Arduino.h>

enum class Permission
{
    Read,     // Read-only from cloud
    ReadWrite // Read/write from cloud
};

enum class Priority
{
    Cloud, // If different from cloud, then update local
    Local, // If different from cloud, then update cloud
};

enum class Update_Policy
{
    None, // Cant update, read-only from local
    Change, // Update if cloud and local are different
    Demand, //Update when demand
};

using callback_t = std::function<void(void)>;


class CloudVarBase
{
public:

    CloudVarBase() = default;
    CloudVarBase(
        const String name, 
        Permission permission = Permission::ReadWrite, 
        Priority priority = Priority::Cloud, 
        Update_Policy update_policy = Update_Policy::Change, 
        callback_t on_sync = []() {}, 
        callback_t on_receive = []() {}) 
    : name(name), permission(permission), priority(priority), update_policy(update_policy), on_receive(on_receive), on_sync(on_sync) {}

    virtual ~CloudVarBase() = default;

    CloudVarBase &set_name(String name)
    {
        this->name = name;
        return *this;
    }
    CloudVarBase &set_callback_on_receive(callback_t on_receive)
    {
        this->on_receive = on_receive;
        return *this;
    }
    CloudVarBase &set_callback_on_sync(callback_t on_sync)
    {
        this->on_sync = on_sync;
        return *this;
    }
    CloudVarBase &set_permission(Permission permission)
    {
        this->permission = permission;
        return *this;
    }
    CloudVarBase &set_priority(Priority priority)
    {
        this->priority = priority;
        return *this;
    }
    CloudVarBase &set_cloud_update_callback(callback_t cloud_update_callback)
    {
        this->cloud_update_callback = cloud_update_callback;
        return *this;
    }
    virtual void update_from_cloud(String message) = 0;
    virtual void update_to_cloud() = 0;
    virtual void update_to_local() = 0;
    virtual bool different_from_cloud() = 0;
    virtual String stringify() const = 0;

    void update_on_different()
    {
        if (!different_from_cloud()) return;
        update_on_demand();
    }

    void update_on_demand()
    {
        if (priority == Priority::Cloud)
            update_to_local();
        else
        {
            update_to_cloud();
            cloud_update_callback();
        }
    }

    void update()
    {
        switch (update_policy)
        {
            case Update_Policy::Change:
                update_on_different();
                break;
            case Update_Policy::Demand:
                update_on_demand();
                break;
            default:
                break;
        }

        if (on_sync) on_sync();
    }
    
    String name;
    Priority priority;
    Permission permission;
    Update_Policy update_policy;
    callback_t on_receive, on_sync, cloud_update_callback;

};

class CloudVarString : public CloudVarBase
{
public:
    String &local, cloud;

    CloudVarString(
        const String name, 
        String &local, 
        Permission permission = Permission::ReadWrite, 
        Priority priority = Priority::Cloud, 
        Update_Policy update_policy = Update_Policy::Change, 
        callback_t on_sync = []() {}, 
        callback_t on_receive = []() {}) : CloudVarBase(name, permission, priority, update_policy, on_receive, on_sync), local(local), cloud(local) {}

    void update_from_cloud(String message) override
    {
        cloud = message;

        if (on_receive) on_receive();
    }
    void update_to_local() override { local = cloud; }
    void update_to_cloud() override { cloud = local; }
    bool different_from_cloud() override { return local != cloud; }
    String stringify() const override { return local; }
};

class CloudVarInt : public CloudVarBase
{
public:
    int &local, cloud;

    CloudVarInt(
        const String name, 
        int &local, 
        Permission permission = Permission::ReadWrite, 
        Priority priority = Priority::Cloud, 
        Update_Policy update_policy = Update_Policy::Change, 
        callback_t on_sync = []() {}, 
        callback_t on_receive = []() {}) 
        : CloudVarBase(name, permission, priority, update_policy, on_receive, on_sync), local(local), cloud(local) {}

    void update_from_cloud(String message) override
    {
        cloud = message.toInt();

        if (on_receive) on_receive();
    }

    void update_to_local() override { local = cloud; }
    void update_to_cloud() override { cloud = local; }
    bool different_from_cloud() override { return local != cloud; }
    String stringify() const override { return String(local); }
};

class CloudVarFloat : public CloudVarBase
{
public:
    float &local, cloud;

    CloudVarFloat(
        const String name, 
        float &local, 
        Permission permission = Permission::ReadWrite, 
        Priority priority = Priority::Cloud, 
        Update_Policy update_policy = Update_Policy::Change, 
        callback_t on_sync = []() {}, 
        callback_t on_receive = []() {}) 
        : CloudVarBase(name, permission, priority, update_policy, on_receive, on_sync), local(local), cloud(local) {}

    void update_from_cloud(String message) override
    {
        cloud = message.toFloat();

        if (on_receive) on_receive();
    }

    void update_to_local() override { local = cloud; }
    void update_to_cloud() override { cloud = local; }
    bool different_from_cloud() override { return local != cloud; }
    String stringify() const override { return String(local); }
};

class CloudVarDouble : public CloudVarBase
{
public:
    double &local, cloud;

    CloudVarDouble(
        const String name, 
        double &local, 
        Permission permission = Permission::ReadWrite, 
        Priority priority = Priority::Cloud, 
        Update_Policy update_policy = Update_Policy::Change, 
        callback_t on_sync = []() {}, 
        callback_t on_receive = []() {}) 
        : CloudVarBase(name, permission, priority, update_policy, on_receive, on_sync), local(local), cloud(local) {}

    void update_from_cloud(String message) override
    {
        cloud = message.toDouble();

        if (on_receive) on_receive();
    }

    void update_to_local() override { local = cloud; }
    void update_to_cloud() override { cloud = local; }
    bool different_from_cloud() override { return local != cloud; }
    String stringify() const override { return String(local); }
};

class CloudVarBool : public CloudVarBase
{
public:
    bool &local, cloud;

    CloudVarBool(
        const String name, 
        bool &local, 
        Permission permission = Permission::ReadWrite, 
        Priority priority = Priority::Cloud, 
        Update_Policy update_policy = Update_Policy::Change, 
        callback_t on_sync = []() {}, 
        callback_t on_receive = []() {}) 
        : CloudVarBase(name, permission, priority, update_policy, on_receive, on_sync), local(local), cloud(local) {}

    void update_from_cloud(String message) override
    {
        cloud = message.toInt();

        if (on_receive) on_receive();
    }

    void update_to_local() override { local = cloud; }
    void update_to_cloud() override { cloud = local; }
    bool different_from_cloud() override { return local != cloud; }
    String stringify() const override { return String(local); }
};