#include "agent_tempature.hpp"

#include "event.hpp"

namespace sb {

AgentTempature::AgentTempature(SensorsId& a_sensors_id)
: AgentSensor(a_sensors_id)
, m_port(7070)
{
}

unsigned short AgentTempature::port() const
{
    return m_port;
}

ProtocolType AgentTempature::protocol() const 
{
	return ProtocolType::TCP;
}

}// namespace sb
