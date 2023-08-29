#include "subscribe_manager.hpp"

#include <iostream>
#include <algorithm>

namespace sb {

// SubscribeManager::SubscribeManager(ControlersAgents& a_controler_agents)
// : m_controler_agents(a_controler_agents)
// {
// }

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
        Protocol command;
        if(subscriber->signal_controler(a_event, command)){
            std::cout << command.data();
            std::cout << a_event.data();
            subscriber->deliver(command);
        }
    }
}
  
}// namespace sb