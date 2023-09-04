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

typedef std::shared_ptr<Subscriber> SubscriberPtr;

class SubscribeManager {
public:
    explicit SubscribeManager();

    ~SubscribeManager() noexcept = default;

    void join(SubscriberPtr a_subscriber);
    void leave(SubscriberPtr a_subscriber);
    void deliver(Protocol const& a_event);

private:
    std::map<std::string, std::vector<SubscriberPtr>> m_subscriber_clan;
    std::map<std::string, std::string> m_event_type;
};

}//namespace sb

#endif // SUBSCRIBE_MANAGER_HPP
