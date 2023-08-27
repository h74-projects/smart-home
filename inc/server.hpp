#ifndef SERVER_HPP
#define SERVER_HPP

#include "subscribe_manager.hpp"
#include "agent_tempature.hpp"

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace sb {

class Server {
public:
    explicit Server(boost::asio::io_context& a_io_context,
        tcp::endpoint const& a_sensor_endpoint, tcp::endpoint const& a_controler_endpoint,
        AgentTempature& a_agent);
    ~Server() noexcept = default;
    
    Server(Server const& a_other) = delete;
    Server& operator=(Server const& a_other) = delete;

private:
    void accept();
    
private:
    tcp::acceptor m_sensor_acceptor;
    tcp::acceptor m_controler_acceptor;
    AgentTempature& m_agent;
    SubscribeManager m_subscribe_manager;
};

}//namespace sb

#endif // SERVER_HPP
