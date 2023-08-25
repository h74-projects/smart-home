#ifndef SESSION_HPP
#define SESSION_HPP

#include "protocol.hpp"
#include "subscriber.hpp"
#include "subscribe_manager.hpp"

#include <boost/asio.hpp>

#include <memory> //enable_shared_from_this
#include <deque>

using boost::asio::ip::tcp;

namespace sb {

typedef std::deque<Protocol> event_queue; //change name

class Session : public Subscriber, public std::enable_shared_from_this<Session>{
public:
    using Subscriber::Subscriber;
    explicit Session(tcp::socket a_socket, SubscribeManager& a_subscribtion, bool a_type);

    ~Session() noexcept = default;
    // Session(Session const& a_other);
    // Session(Session&& a_other);
    // Session& operator=(Session const& a_other);
    // Session& operator=(Session&& a_other);

    void start();
    void deliver(Protocol const& a_msg) override;
    void subscribe();
    void recieve_subscribe();

private:
    void parse_event();
    void recieve();
    void publish();

private:
    tcp::socket m_socket;
    SubscribeManager& m_subscription_manager;
    Protocol m_incoming_event;
    event_queue m_events;
    std::vector<int> m_subscription;
    bool m_type;
};

}//namespace sb

#endif // SESSION_HPP
