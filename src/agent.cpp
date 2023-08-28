#include "agent.hpp"

#include "event.hpp"

#include <iostream>
#include <fstream> //ifstream
#include <nlohmann/json.hpp> //nlohmann::json
#include <stdexcept> //runtime error

namespace sb {

Agent::Agent(std::string const& a_file_name)
: m_file_name(a_file_name)
, m_sensors_id{}
{
    set_sensors_id();
}

void Agent::wraper(Protocol& a_data, Protocol& a_event)
{
    // std::string type = "1";
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

void Agent::set_sensors_id()
{
    std::ifstream sensors_id_file(m_file_name);
    if(!sensors_id_file) {
        std::runtime_error("file opcode_map.dat could not be opened!");
    }
    nlohmann::json json_sendors_id;
    sensors_id_file >> json_sendors_id;
    m_sensors_id = json_sendors_id.get<std::unordered_map<std::string, std::vector<std::string>>>();
}

}// amespace sb
