#include "agent_door.hpp"

#include "event.hpp"

#include <iostream>
#include <cstring> //memcpy strlen

namespace sb {

AgentDoor::AgentDoor()
: m_endpoint(tcp::v4(), 9090)
, m_event_type(2)
{
}

tcp::endpoint AgentDoor::endpoint() const 
{
	return m_endpoint;
}

bool AgentDoor::check_event(Protocol const& a_event, Protocol& a_command)
{
	std::cout << "agent_ac:event.data()" << a_event.event_data() << '\n';
	char command[] = "open door";
	
	if(a_event.event_data() == "open"){
		a_command.body_length(std::strlen(command));
		std::memcpy(a_command.body(), command, a_command.body_length());
		a_command.encode_header();
		return true;
	}
	return false;
}

int AgentDoor::event_type() const
{
    return m_event_type;
}

}// amespace sb