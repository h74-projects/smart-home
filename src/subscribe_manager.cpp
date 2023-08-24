#include "subscribe_manager.hpp"

namespace sb {

void SubscribeManager::join(SubscriberPtr a_subscriber)
{
    m_subscriber_clan[a_subscriber->event_type()] = a_subscriber;
}

void SubscribeManager::leave(SubscriberPtr a_subscriber) //needed?
{
    m_subscriber_clan.erase(a_subscriber->event_type());
}

void SubscribeManager::deliver(Protocol const& a_event)
{
    m_recent_events.push_back(a_event);
    while (m_recent_events.size() > 100) //enum is here
        m_recent_events.pop_front();

    for (auto subscriber : m_subscriber_clan)
        subscriber.second->deliver(a_event);
}

  
}// namespace sb