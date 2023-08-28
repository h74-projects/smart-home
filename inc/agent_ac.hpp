#ifndef AGENT_AC_HPP
#define AGENT_AC_HPP

#include "protocol.hpp"
#include "agent.hpp"

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace sb {

class AgentAc : public Agent{
public: 
    AgentAc();

    ~AgentAc() noexcept = default;
    AgentAc(AgentAc const& a_other) = default;
    AgentAc(AgentAc&& a_other) = default;
    AgentAc& operator=(AgentAc const& a_other) = default;
    AgentAc& operator=(AgentAc&& a_other) = default;

    // void wraper(Protocol& a_data, Protocol& a_event);
    tcp::endpoint endpoint() const override;
private:
    tcp::endpoint m_endpoint;
};

}//namespace sb

#endif // AGENT_AC_HPP
