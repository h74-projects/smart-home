#include "session_udp.hpp"

#include "agent_sensor.hpp"
#include "agent_controler.hpp"
#include <iostream>

namespace sb {

SessionUdp::SessionUdp(udp::socket a_socket, SubscribeManager& a_subscribtion_manager, std::unique_ptr<Agent> a_agent,
                       bool a_type)
: m_socket(std::move(a_socket))
, m_subscription_manager(a_subscribtion_manager)
, m_subscription{}
, m_type{a_type}
, m_agent(std::move(a_agent))
{
}

void SessionUdp::start()
{
    if(m_type){ // sensor socket state
        parse_event();
    }else { // controler socket state
        m_subscription_manager.join(shared_from_this());
    }
}

void SessionUdp::deliver(Protocol const& a_msg)
{
    bool write_in_progress = !m_events.empty();
    m_events.push_back(a_msg);
    if (!write_in_progress)
    {
        publish();
    }
}

void SessionUdp::parse_event()
{
    auto self(shared_from_this());
    m_socket.async_receive(boost::asio::buffer(m_incoming_event.data(), 1000),
    [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (!ec && m_incoming_event.check_packet_length()){
                Protocol event;
                dynamic_cast<AgentSensor&>(*m_agent).wraper(m_incoming_event, event);
                m_subscription_manager.deliver(event);
                parse_event();
            }else {
                m_subscription_manager.leave(shared_from_this());
            }
        });
}

void SessionUdp::publish()
{
    auto self(shared_from_this());
    udp::endpoint sender_endpoint(udp::v4(), dynamic_cast<AgentControler&>(*m_agent).sender_port());
    m_socket.async_send_to(boost::asio::buffer(m_events.front().data(), m_events.front().length()), sender_endpoint,
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



bool SessionUdp::signal_controler(Protocol const& a_event, Protocol& a_command)
{
    return dynamic_cast<AgentControler&>(*m_agent).check_event(a_event, a_command);
}

int SessionUdp::event_type() const
{
    return dynamic_cast<AgentControler&>(*m_agent).event_type();
}

}// namespace sb