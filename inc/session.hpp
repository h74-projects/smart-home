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

typedef std::deque<Protocol> chat_message_queue; //change name

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

private:
    void do_read_header();
    void do_read_body();
    void do_write();

private:
    tcp::socket m_socket;
    SubscribeManager& m_subscribtion;
    Protocol m_read_msg;
    chat_message_queue m_write_msgs;
    bool m_type;
};

}//namespace sb

#endif // SESSION_HPP
