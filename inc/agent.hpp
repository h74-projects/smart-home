#ifndef AGENT_HPP
#define AGENT_HPP

#include "protocol.hpp"

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace sb {

class Agent {
public:
    virtual ~Agent() = default;
    
    virtual tcp::endpoint endpoint() const = 0;

    void wraper(Protocol& a_data, Protocol& a_event);

protected:
    Agent() = default;
    Agent(Agent const& a_other) = default;
    Agent& operator=(Agent const& a_other) = default;

};

}//namespace sb

#endif // AGENT_HPP
