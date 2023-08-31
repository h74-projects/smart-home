#ifndef SMART_HOME_HPP
#define SMART_HOME_HPP

#include "agent_sensor.hpp"
#include "agent_controler.hpp"

#include <string>
#include <unordered_map>
#include <vector>
#include <string>
#include <tuple>
#include <dlfcn.h> //dlsym, dlerror, dlopen
#include <iostream> //std::cerr

namespace sb {     

typedef std::unordered_map<std::string, std::vector<std::string>> SensorsId; 
typedef std::unordered_map<std::string, SensorsId> EventType;
typedef AgentSensor* create_agent_func(SensorsId&);
typedef AgentControler* create_agent_controler_func();
typedef std::tuple<create_agent_func*, create_agent_controler_func*> Agents;

class SmartBuilding {
public:
    SmartBuilding() = default;
    ~SmartBuilding() = default;

    void run();
    void configure(std::string a_path);
    
private:
    void load_sensor_agents_type(std::string const& a_path);
    void load_controlers_agents_type(std::string const& a_path);
    void load_sensors(std::string const& a_path);

    template <typename Agent>
    Agent* make_agent(std::string a_event_type, std::unordered_map<std::string, std::string>& a_map);

private:
    std::unordered_map<std::string, std::string> m_sensor_agents;
    std::unordered_map<std::string, std::string> m_controler_agents;
    EventType m_sensors_per_type;
};

template <typename Agent>
Agent* SmartBuilding::make_agent(std::string a_event_type, std::unordered_map<std::string, std::string>& a_map)
{
    void* agent = dlopen(a_map[a_event_type].c_str(), RTLD_LAZY);

    if (!agent) {
        std::cerr << "Cannot load library: " << dlerror() << '\n';
        return nullptr;
    }

    dlerror();
    Agent* create_agent_lib  = (Agent*)dlsym(agent, "create_agent");
    const char* dlsym_error = dlerror();

    if (dlsym_error) {
        std::cerr << "Cannot load symbol create: " << dlsym_error << '\n';
        return nullptr;
    }

    return create_agent_lib;
}

} //namespace sb

#endif // SMART_HOME_HPP
