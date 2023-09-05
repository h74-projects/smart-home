#include "agent_boiler.hpp"

#include "event.hpp"

#include <iostream>
#include <cstring> //memcpy strlen

namespace sb {

AgentBoiler::AgentBoiler()
: m_port(0)
, m_sender_port(10100)
, m_event_type(3)
{
}

unsigned short AgentBoiler::port() const 
{
	return m_port;
}

unsigned short AgentBoiler::sender_port() const 
{
	return m_sender_port;
}

bool AgentBoiler::check_event(Protocol const& a_event, Protocol& a_command)
{
	char command_on[] = "boiler turn  on";
	char command_off[] = "boiler turn off";
	
	if(a_event.event_data() == "open"){
		a_command.body_length(std::strlen(command_on));
		std::memcpy(a_command.body(), command_on, a_command.body_length());
		a_command.encode_header();
		return true;

	} else if(a_event.event_data() == "close") {
		a_command.body_length(std::strlen(command_off));
		std::memcpy(a_command.body(), command_off, a_command.body_length());
		a_command.encode_header();
		return true;
	}

	return false;
}

int AgentBoiler::event_type() const
{
    return m_event_type;
}

ProtocolType AgentBoiler::protocol() const 
{
	return ProtocolType::UDP;
}

}// amespace sb