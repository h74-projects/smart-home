#include "udp_server.hpp"
#include "session_udp.hpp"
#include "session.hpp"

namespace sb {

UdpServer::UdpServer(boost::asio::io_context& a_io_context, std::unique_ptr<Agent> a_agent, bool a_device_type,
                     SubscribeManager& a_sm)
: m_socket(a_io_context, udp::endpoint(udp::v4(), a_agent->port()))
, m_agent(std::move(a_agent))
, m_device_type(a_device_type)
, m_subscribe_manager(a_sm)
{
    accept();
}

void UdpServer::accept()
{
    std::make_shared<SessionUdp>(std::move(m_socket), m_subscribe_manager, std::move(m_agent), m_device_type)->start();
}

}// namespace sb 