#ifndef AGENT_CONTROLER_HPP
#define AGENT_CONTROLER_HPP

#include "protocol.hpp"
#include "agent.hpp"

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace sb {

class AgentControler : public Agent{
public:
    virtual ~AgentControler() = default;
    
    virtual unsigned short port() const = 0;
    virtual unsigned short sender_port() const = 0;
    virtual ProtocolType protocol() const = 0;

    virtual bool check_event(Protocol const& a_event, Protocol& a_command) = 0;
    virtual int event_type() const = 0;

protected:
    AgentControler() = default;

};

}//namespace sb

#endif // AGENT_CONTROLER_HPP
