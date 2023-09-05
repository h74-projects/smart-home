#include "subscribe_manager.hpp"

#include <iostream>
#include <algorithm>

namespace sb {

SubscribeManager::SubscribeManager()
{
    m_event_type["1"] = "TEMPATURE_EVENT";
    m_event_type["2"] = "ACCESS_DOOR_EVENT";
    m_event_type["3"] = "BOILER_EVENT";
}

void SubscribeManager::join(SubscriberPtr a_subscriber)
{
    std::string type(std::to_string(a_subscriber->event_type()));
    if (type != "") {
        m_subscriber_clan[type].push_back(a_subscriber);
        std::cout <<"subscribed to " << m_event_type[type] << "\n";
    }
}

void SubscribeManager::leave(SubscriberPtr a_subscriber) 
{
    for (auto type_subscribers : m_subscriber_clan) {
        type_subscribers.second.erase(std::find(type_subscribers.second.begin(), type_subscribers.second.end(), a_subscriber));
    }
}

void SubscribeManager::deliver(Protocol const& a_event) 
{
    std::string type = a_event.event_type();

    for (auto subscriber : m_subscriber_clan[type]) {
        Protocol command;
        if(subscriber->signal_controler(a_event, command)){ 
            subscriber->deliver(command);
        }
    }
}
  
}// namespace sb