#ifndef SUBSCRIBER_HPP
#define SUBSCRIBER_HPP

#include "protocol.hpp"

namespace sb {

struct Subscriber {
    Subscriber(int a_event_type = 1);

    virtual ~Subscriber() {}
    virtual void deliver(Protocol const& msg) = 0; //add delete for all the 5
    virtual bool signal_controler(Protocol const& a_event, Protocol& a_command) = 0;

    int event_type() const;

private:
    int m_event_type; //enum
};

}//namespace sb

#endif // SUBSCRIBER_HPP