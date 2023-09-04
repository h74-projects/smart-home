#include "agent_ac.hpp"

#include "event.hpp"

#include <iostream>
#include <cstring> //memcpy strlen

namespace sb {

AgentAc::AgentAc()
: m_port(0)
, m_sender_port(8080)
, m_event_type(1)
{
}

unsigned short AgentAc::port() const 
{
	return m_port;
}

unsigned short AgentAc::sender_port() const 
{
	return m_sender_port;
}

bool AgentAc::check_event(Protocol const& a_event, Protocol& a_command)
{
	char command_on[] = "turn  on";
	char command_off[] = "turn off";
	
	if(a_event.event_data() == "30"){
		a_command.body_length(std::strlen(command_on));
		std::memcpy(a_command.body(), command_on, a_command.body_length());
		a_command.encode_header();
		return true;

	} else if(a_event.event_data() == "25") {
		a_command.body_length(std::strlen(command_off));
		std::memcpy(a_command.body(), command_off, a_command.body_length());
		a_command.encode_header();
		return true;
	}

	return false;
}

int AgentAc::event_type() const
{
    return m_event_type;
}

ProtocolType AgentAc::protocol() const 
{
	return ProtocolType::UDP;
}

}// amespace sb