#include "server.hpp"

#include "session.hpp"
// #include "agent_tempature.hpp"


namespace sb {

Server::Server(boost::asio::io_context& a_io_context, Agent& a_agent, bool a_device_type, SubscribeManager& a_sm)
: m_acceptor(a_io_context, a_agent.endpoint())
// , m_sensor_acceptor(a_io_context, a_agent_sensor.endpoint())
, m_agent(a_agent)
, m_device_type(a_device_type)
// , m_agent_controler(a_agent_controler)
, m_subscribe_manager(a_sm)
{
    accept();
}

void Server::accept()
{
    m_acceptor.async_accept([this](boost::system::error_code ec, tcp::socket socket){
        if (!ec){
            std::make_shared<Session>(std::move(socket), m_subscribe_manager, m_agent, m_device_type)->start();
        }//sensor state

        accept();});

    // m_acceptor.async_accept([this](boost::system::error_code ec, tcp::socket socket){
    //     if (!ec){
    //         std::make_shared<Session>(std::move(socket), m_subscribe_manager, m_agent, false)->start();
    //     }//controller state

    //     accept(); });
}

}// namespace sb 
