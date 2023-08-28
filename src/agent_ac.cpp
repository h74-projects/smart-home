#include "agent_ac.hpp"

#include "event.hpp"

#include <iostream>

namespace sb {

AgentAc::AgentAc()
: m_endpoint(tcp::v4(), 8080)
{
}

tcp::endpoint AgentAc::endpoint() const 
{
	return m_endpoint;
}

}// amespace sb
