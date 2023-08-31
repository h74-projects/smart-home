#include "agent_access.hpp"

#include "event.hpp"

namespace sb {

AgentAccess::AgentAccess(SensorsId& a_sensors_id)
: AgentSensor(a_sensors_id)
, m_endpoint(tcp::v4(), 6060)
{
}

tcp::endpoint AgentAccess::endpoint() const
{
    return m_endpoint;
}

}// namespace sb
