#include "agent_sensor.hpp"

#include "event.hpp"

#include <iostream>
#include <fstream> //ifstream
#include <nlohmann/json.hpp> //nlohmann::json
#include <stdexcept> //runtime error

namespace sb {

AgentSensor::AgentSensor(SensorsId& a_sensors_id)
: m_sensors_id{a_sensors_id}
{
}

void AgentSensor::wraper(Protocol& a_data, Protocol& a_event)
{
    std::string line(a_data.body());
    line = line.substr(0, a_data.body_length());
    std::cout << "for_test: " << line << "\n";

    std::string event = line;
    sb::Event e(m_sensors_id[a_data.id()][1], m_sensors_id[a_data.id()][0]);
    e.seprate_data(event);
    e.event_warper(event);

    a_event.body_length(event.size());
    std::memcpy(a_event.body(), event.c_str(), a_event.body_length());
    a_event.encode_header();
}

}// amespace sb
