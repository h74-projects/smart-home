#include "agent_hotwater.hpp"

#include "event.hpp"

namespace sb {

AgentHotWater::AgentHotWater(SensorsId& a_sensors_id)
: AgentSensor(a_sensors_id)
, m_port(5555)
{
}

unsigned short AgentHotWater::port() const
{
    return m_port;
}

ProtocolType AgentHotWater::protocol() const 
{
	return ProtocolType::UDP;
}

}// namespace sb
