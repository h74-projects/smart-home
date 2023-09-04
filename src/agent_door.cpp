#include "agent_door.hpp"

#include "event.hpp"

#include <iostream>
#include <cstring> //memcpy strlen

namespace sb {

AgentDoor::AgentDoor()
: m_port(9090)
, m_sender_port(0)
, m_event_type(2)
{
}

unsigned short AgentDoor::port() const 
{
	return m_port;
}

unsigned short AgentDoor::sender_port() const 
{
	return m_sender_port;
}

bool AgentDoor::check_event(Protocol const& a_event, Protocol& a_command)
{
	static bool locked = true;

	std::cout << "agent_ac:event.data()" << a_event.event_data() << '\n';
	char open[] = "open door";
	char lock[] = "lock door";
	char wrong[] = "incorrect password";
	
	if(a_event.event_data() == "1234"){
		a_command.body_length(std::strlen(locked ? open : lock));
		std::memcpy(a_command.body(), locked ? open : lock, a_command.body_length());
		a_command.encode_header();
		locked = !locked;
	} else {
		a_command.body_length(std::strlen(wrong));
		std::memcpy(a_command.body(), wrong, a_command.body_length());
		a_command.encode_header();
	}
	return true;
}

int AgentDoor::event_type() const
{
    return m_event_type;
}

ProtocolType AgentDoor::protocol() const 
{
	return ProtocolType::TCP;
}

}// amespace sb