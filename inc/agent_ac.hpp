#ifndef AGENT_AC_HPP
#define AGENT_AC_HPP

#include "protocol.hpp"
#include "agent_controler.hpp"

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace sb {

class AgentAc : public AgentControler{
public: 
    AgentAc();

    ~AgentAc() noexcept = default;

    tcp::endpoint endpoint() const override; //TODO change return by value?
    bool check_event(Protocol const& a_event, Protocol& a_command) override;
    int event_type() const override;
    
private:
    tcp::endpoint m_endpoint;
    int m_event_type;
};

}//namespace sb

#endif // AGENT_AC_HPP
