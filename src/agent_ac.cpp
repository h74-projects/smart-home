#include "agent_ac.hpp"

#include "event.hpp"

#include <iostream>
#include <cstring> //memcpy strlen

namespace sb {

AgentAc::AgentAc()
: m_endpoint(tcp::v4(), 8080)
, m_event_type(1)
{
}

tcp::endpoint AgentAc::endpoint() const 
{
	return m_endpoint;
}

bool AgentAc::check_event(Protocol const& a_event, Protocol& a_command)
{
	std::cout << "agent_ac:event.data()" << a_event.event_data() << '\n';
	char command[] = "turn on";
	
	if(a_event.event_data() == "40"){
		a_command.body_length(std::strlen(command));
		std::memcpy(a_command.body(), command, a_command.body_length());
		a_command.encode_header();
		return true;
	}
	return false;
}

int AgentAc::event_type() const
{
    return m_event_type;
}

}// amespace sb