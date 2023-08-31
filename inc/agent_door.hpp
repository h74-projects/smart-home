#ifndef AGENT_DOOR_HPP
#define AGENT_DOOR_HPP

#include "protocol.hpp"
#include "agent_controler.hpp"

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace sb {

class AgentDoor : public AgentControler{
public: 
    AgentDoor();

    ~AgentDoor() noexcept = default;

    tcp::endpoint endpoint() const override; //TODO change return by value?
    bool check_event(Protocol const& a_event, Protocol& a_command) override;
    int event_type() const override;
    
private:
    tcp::endpoint m_endpoint;
    int m_event_type;
};

extern "C" AgentControler* create_agent() {
    return new AgentDoor();
}


}//namespace sb

#endif // AGENT_DOOR_HPP
