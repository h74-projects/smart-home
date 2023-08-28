#include "session.hpp"

namespace sb {

Session::Session(tcp::socket a_socket, SubscribeManager& a_subscribtion_manager, Agent& a_agent,
                bool a_type)
: m_socket(std::move(a_socket))
, m_subscription_manager(a_subscribtion_manager)
, m_subscription{}
, m_type{a_type}
, m_agent(a_agent)
{
}

void Session::start()
{
    if(m_type){ // sensor socket state
        recieve();
    }else { // controler socket state
        subscribe();
    }
}

void Session::deliver(Protocol const& a_msg)
{
    bool write_in_progress = !m_events.empty();
    m_events.push_back(a_msg);
    if (!write_in_progress)
    {
        publish();
    }
}

void Session::recieve_subscribe()
{
    auto self(shared_from_this());
    boost::asio::async_read(m_socket, boost::asio::buffer(m_incoming_event.data(), sb::header_length), 
        [this, self](boost::system::error_code ec, std::size_t /*length*/){ //length comment
            if (!ec && m_incoming_event.check_packet_length()) {
                subscribe();
            }else {
                recieve_subscribe();
            }
        });
}

void Session::subscribe()
{
    auto self(shared_from_this());
    boost::asio::async_read(m_socket, boost::asio::buffer(m_incoming_event.body(), m_incoming_event.body_length()),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (!ec){
                m_subscription_manager.join(shared_from_this(), m_incoming_event);
                recieve_subscribe();
            }else {
                m_subscription_manager.leave(shared_from_this());
            }
        });
}

void Session::recieve()
{
    auto self(shared_from_this());
    boost::asio::async_read(m_socket, boost::asio::buffer(m_incoming_event.data(), sb::header_length), 
        [this, self](boost::system::error_code ec, std::size_t /*length*/){ //length comment
            if (!ec && m_incoming_event.check_packet_length()) {
                parse_event();
            }else {
                m_subscription_manager.leave(shared_from_this());
            }
        });
}

void Session::parse_event()
{
    auto self(shared_from_this());
    boost::asio::async_read(m_socket, boost::asio::buffer(m_incoming_event.body(), m_incoming_event.body_length()),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (!ec){
                Protocol event;
                m_agent.wraper(m_incoming_event, event);
                m_subscription_manager.deliver(event);
                recieve();
            }else {
                m_subscription_manager.leave(shared_from_this());
            }
        });
}

void Session::publish()
{
    auto self(shared_from_this());
    boost::asio::async_write(m_socket, boost::asio::buffer(m_events.front().data(), m_events.front().length()),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (!ec) {
                m_events.pop_front();
            if (!m_events.empty()){
                publish();
            }
            } else {
                m_subscription_manager.leave(shared_from_this());
            }
        });
}

}// namespace sb