#include "agent_tempature.hpp"

#include "event.hpp"

namespace sb {

AgentTempature::AgentTempature(SensorsId& a_sensors_id)
: AgentSensor(a_sensors_id)
, m_endpoint(tcp::v4(), 7070)
{
}

tcp::endpoint AgentTempature::endpoint() const
{
    return m_endpoint;
}

}// namespace sb
