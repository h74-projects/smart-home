#include "agent_tempature.hpp"

#include "event.hpp"

namespace sb {

AgentTempature::AgentTempature(std::string const& a_file_name)
: Agent(a_file_name)
, m_endpoint(tcp::v4(), 7070)
{
}

tcp::endpoint AgentTempature::endpoint() const
{
    return m_endpoint;
}

}// amespace sb
