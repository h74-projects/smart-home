#ifndef AGENT_TEMPATURE_HPP
#define AGENT_TEMPATURE_HPP

#include "protocol.hpp"

#include <boost/asio.hpp>

using boost::asio::ip::udp;

namespace sb {

class AgentTempature {
public: 
    AgentTempature(unsigned short port);

    ~AgentTempature() noexcept = default;
    AgentTempature(AgentTempature const& a_other) = default;
    AgentTempature(AgentTempature&& a_other) = default;
    AgentTempature& operator=(AgentTempature const& a_other) = default;
    AgentTempature& operator=(AgentTempature&& a_other) = default;

    void wraper(Protocol& a_data, Protocol& a_event);

private:
    unsigned short m_port;

};

}//namespace sb

#endif // AGENT_TEMPATURE_HPP
