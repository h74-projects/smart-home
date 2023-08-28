#ifndef SERVER_HPP
#define SERVER_HPP

#include "subscribe_manager.hpp"
#include "agent.hpp"

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace sb {

class Server {
public:
    explicit Server(boost::asio::io_context& a_io_context, Agent& a_agent, bool a_device_type, SubscribeManager& a_sm);
    ~Server() noexcept = default;
    
    Server(Server const& a_other) = delete;
    Server& operator=(Server const& a_other) = delete;

private:
    void accept();
    
private:
    tcp::acceptor m_acceptor;
    // tcp::acceptor m_sensor_acceptor;
    Agent& m_agent;
    // Agent& m_agent_controler;
    bool m_device_type;
    SubscribeManager& m_subscribe_manager;
};

}//namespace sb

#endif // SERVER_HPP
