#include "agent_tempature.hpp"

#include "event.hpp"

#include <iostream>

namespace sb {

AgentTempature::AgentTempature(unsigned short a_port)
: m_port(a_port)
{
}

void AgentTempature::wraper(Protocol& a_data, Protocol& a_event)
{
        std::string type = "1";
        std::string line(a_data.body());
        line = line.substr(0, a_data.body_length());
        std::cout << "for_test: " << line << "\n";

        std::string event = line;
        sb::Event e("room_1", type);
        e.event_warper(event);

        a_event.body_length(event.size());
        std::memcpy(a_event.body(), event.c_str(), a_event.body_length());
        a_event.encode_header();
}

}// amespace sb