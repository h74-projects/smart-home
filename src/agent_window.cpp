#include "agent_window.hpp"

#include "event.hpp"

#include <iostream>
#include <cstring> //memcpy strlen

namespace sb {

AgentWindow::AgentWindow()
: m_port(9595)
, m_sender_port(0)
, m_event_type(1)
{
}

unsigned short AgentWindow::port() const 
{
	return m_port;
}

unsigned short AgentWindow::sender_port() const 
{
	return m_sender_port;
}

bool AgentWindow::check_event(Protocol const& a_event, Protocol& a_command)
{
	char command[] = "close window";
	
	if(a_event.event_data() == "40"){
		a_command.body_length(std::strlen(command));
		std::memcpy(a_command.body(), command, a_command.body_length());
		a_command.encode_header();
		return true;
	}
	return false;
}

int AgentWindow::event_type() const
{
    return m_event_type;
}

ProtocolType AgentWindow::protocol() const 
{
	return ProtocolType::TCP;
}

}// amespace sb