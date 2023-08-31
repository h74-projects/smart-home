#ifndef SERVER_HPP
#define SERVER_HPP

#include "subscribe_manager.hpp"
#include "agent.hpp"
// #include "agent_sensor.hpp"
// #include "agent_controler.hpp"


#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace sb {

class Server {
public:
    explicit Server(boost::asio::io_context& a_io_context, std::unique_ptr<Agent> a_agent, bool a_device_type, SubscribeManager& a_sm);
    // explicit Server(boost::asio::io_context& a_io_context, AgentControler& a_agent, bool a_device_type, SubscribeManager& a_sm);

    ~Server() noexcept = default;

private:
    void accept();
    
private:
    tcp::acceptor m_acceptor;
    Agent& m_agent;
    bool m_device_type;
    SubscribeManager& m_subscribe_manager;
};

}//namespace sb

#endif // SERVER_HPP
