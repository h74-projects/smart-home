#ifndef AGENT_HPP
#define AGENT_HPP

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace sb {

enum class ProtocolType {   UDP,
                            TCP
                        };

class Agent {
public:
    virtual ~Agent() = default;
    
    virtual unsigned short port() const = 0;
    virtual ProtocolType protocol() const = 0;

protected:
    Agent() = default;

};

}//namespace sb

#endif // AGENT_HPP
