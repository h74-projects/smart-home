#ifndef AGENT_HPP
#define AGENT_HPP

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace sb {

class Agent {
public:
    virtual ~Agent() = default;
    
    virtual tcp::endpoint endpoint() const = 0;

protected:
    Agent() = default;

};

}//namespace sb

#endif // AGENT_HPP
