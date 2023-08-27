#include "subscribe_manager.hpp"

#include <iostream>
#include <algorithm>

namespace sb {

void SubscribeManager::join(SubscriberPtr a_subscriber, Protocol const& a_event)
{
    if (std::string type(a_event.event_type()); type != "") {
        m_subscriber_clan[type].push_back(a_subscriber);
        std::cout << "subscribed to " << type << "\n";
    }
}

void SubscribeManager::leave(SubscriberPtr a_subscriber) //check if not end
{
    for (auto type_subscribers : m_subscriber_clan) {
        type_subscribers.second.erase(std::find(type_subscribers.second.begin(), type_subscribers.second.end(), a_subscriber));
    }
}

void SubscribeManager::deliver(Protocol const& a_event) 
{
    m_recent_events.push_back(a_event);
    std::string type = a_event.event_type();

    for (auto subscriber : m_subscriber_clan[type]) {
        subscriber->deliver(a_event);
    }
}
  
}// namespace sb