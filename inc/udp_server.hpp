#ifndef UDP_SERVER_HPP
#define UDP_SERVER_HPP

#include "subscribe_manager.hpp"
#include "agent.hpp"

#include <boost/asio.hpp>

using boost::asio::ip::udp;

namespace sb {

class UdpServer {
public:
    explicit UdpServer(boost::asio::io_context& a_io_context, std::unique_ptr<Agent> a_agent, bool a_device_type,
     SubscribeManager& a_sm);

    ~UdpServer() noexcept = default;

private:
    void accept();
    
private:
    udp::socket m_socket;
    std::unique_ptr<Agent> m_agent;
    bool m_device_type;
    SubscribeManager& m_subscribe_manager;
};

}//namespace sb

#endif // UDP_SERVER_HPP
