#include "agent_log_tempature.hpp"

#include "event.hpp"

#include <iostream>
#include <cstring> //memcpy strlen

namespace sb {

AgentLogTempature::AgentLogTempature()
: m_port(9898)
, m_sender_port(0)
, m_event_type(1)
{
}

unsigned short AgentLogTempature::port() const 
{
	return m_port;
}

unsigned short AgentLogTempature::sender_port() const 
{
	return m_sender_port;
}

bool AgentLogTempature::check_event(Protocol const& a_event, Protocol& a_command)
{
	a_command.body_length(a_event.event_data().length());
	std::memcpy(a_command.body(), a_event.event_data().c_str(), a_command.body_length());
	a_command.encode_header();
	return true;
}

int AgentLogTempature::event_type() const
{
    return m_event_type;
}

ProtocolType AgentLogTempature::protocol() const 
{
	return ProtocolType::TCP;
}

}// amespace sb