#include "server.hpp"
#include "session.hpp"

namespace sb {

Server::Server(boost::asio::io_context& a_io_context, std::unique_ptr<Agent> a_agent, bool a_device_type, SubscribeManager& a_sm)
: m_acceptor(a_io_context, tcp::endpoint(tcp::v4(), a_agent->port()))
, m_agent(std::move(a_agent))
, m_device_type(a_device_type)
, m_subscribe_manager(a_sm)
{
    accept();
}

void Server::accept()
{
    m_acceptor.async_accept([this](boost::system::error_code ec, tcp::socket socket){
        if (!ec){
            std::make_shared<Session>(std::move(socket), m_subscribe_manager, std::move(m_agent), m_device_type)->start();
        }

        accept();
    });
}

}// namespace sb 
