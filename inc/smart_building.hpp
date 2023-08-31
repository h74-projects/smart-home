#ifndef SMART_HOME_HPP
#define SMART_HOME_HPP

#include "agent_sensor.hpp"
#include "agent_controler.hpp"

#include <string>
#include <unordered_map>
#include <vector>
#include <string>
#include <tuple>

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
    create_agent_func* make_agent_sensor(std::string a_event_type);
    create_agent_controler_func* make_agent_controler(std::string a_event_type);

private:
    std::unordered_map<std::string, std::string> m_sensor_agents;
    std::unordered_map<std::string, std::string> m_controler_agents;
    EventType m_sensors_per_type;
};

} //namespace sb

#endif // SMART_HOME_HPP
