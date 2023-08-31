#include "agent_window.hpp"

#include "event.hpp"

#include <iostream>
#include <cstring> //memcpy strlen

namespace sb {

AgentWindow::AgentWindow()
: m_endpoint(tcp::v4(), 9595)
, m_event_type(1)
{
}

tcp::endpoint AgentWindow::endpoint() const 
{
	return m_endpoint;
}

bool AgentWindow::check_event(Protocol const& a_event, Protocol& a_command)
{
	std::cout << "agent_ac:event.data()" << a_event.event_data() << '\n';
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

}// amespace sb