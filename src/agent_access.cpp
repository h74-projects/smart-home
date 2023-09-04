#include "agent_access.hpp"

#include "event.hpp"

namespace sb {

AgentAccess::AgentAccess(SensorsId& a_sensors_id)
: AgentSensor(a_sensors_id)
, m_port(6060)
{
}

unsigned short AgentAccess::port() const
{
    return m_port;
}

ProtocolType AgentAccess::protocol() const 
{
	return ProtocolType::TCP;
}

}// namespace sb
