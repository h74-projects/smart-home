#ifndef SESSION_UDP_HPP
#define SESSION_UDP_HPP

#include "protocol.hpp"
#include "subscriber.hpp"
#include "subscribe_manager.hpp"
#include "agent.hpp"

#include <boost/asio.hpp>

#include <memory> //enable_shared_from_this
#include <deque>

using boost::asio::ip::udp;

namespace sb {

typedef std::deque<Protocol> event_queue; //change name

class SessionUdp : public Subscriber, public std::enable_shared_from_this<SessionUdp> {
public:
    using Subscriber::Subscriber;
    explicit SessionUdp(udp::socket a_socket, SubscribeManager& a_subscribtion, std::unique_ptr<Agent> a_agent, bool a_type);

    ~SessionUdp() noexcept = default;

    void deliver(Protocol const& a_msg) override;
    bool signal_controler(Protocol const& a_event, Protocol& a_command) override;
    int event_type() const override;

    void start();

private:
    void parse_event();
    void recieve();
    void publish();

private:
    udp::socket m_socket;
    SubscribeManager& m_subscription_manager;
    Protocol m_incoming_event;
    event_queue m_events;
    std::vector<int> m_subscription;
    bool m_type;
    std::unique_ptr<Agent> m_agent;
};

}//namespace sb

#endif // SESSION_UDP_HPP
