#ifndef AGENT_CONTROLER_HPP
#define AGENT_CONTROLER_HPP

#include "protocol.hpp"

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace sb {

class AgentControler {
public:
    virtual ~AgentControler() = default;
    
    virtual tcp::endpoint endpoint() const = 0;
    virtual bool check_event(Protocol const& a_event, Protocol& a_command) = 0;
    virtual int event_type() const = 0;

protected:
    AgentControler() = default;

};

}//namespace sb

#endif // AGENT_CONTROLER_HPP
