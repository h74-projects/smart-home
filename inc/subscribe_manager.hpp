#ifndef SUBSCRIBE_MANAGER_HPP
#define SUBSCRIBE_MANAGER_HPP

#include "subscriber.hpp"
#include "protocol.hpp"

#include <boost/asio.hpp>

#include <map>
#include <string>
#include <deque>

using boost::asio::ip::tcp;

namespace sb {

typedef std::deque<Protocol> ProtocolQueue; //replace name also for protocol
typedef std::shared_ptr<Subscriber> SubscriberPtr;

class SubscribeManager {
public:
    SubscribeManager() noexcept = default;

    ~SubscribeManager() noexcept = default;
    // SubscribeManager(SubscribeManager const& a_other);
    // SubscribeManager(SubscribeManager&& a_other);
    // SubscribeManager& operator=(SubscribeManager const& a_other);
    // SubscribeManager& operator=(SubscribeManager&& a_other);

    void join(SubscriberPtr a_subscriber, Protocol const& a_event);
    void leave(SubscriberPtr a_subscriber);
    void deliver(Protocol const& a_event);

private:
    std::map<std::string, std::vector<SubscriberPtr>> m_subscriber_clan;
    ProtocolQueue m_recent_events;
};

}//namespace sb

#endif // SUBSCRIBE_MANAGER_HPP
