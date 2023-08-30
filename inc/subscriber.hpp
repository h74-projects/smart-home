#ifndef SUBSCRIBER_HPP
#define SUBSCRIBER_HPP

#include "protocol.hpp"

namespace sb {

struct Subscriber {
    Subscriber() = default;

    virtual ~Subscriber() {}
    virtual void deliver(Protocol const& msg) = 0; 
    virtual bool signal_controler(Protocol const& a_event, Protocol& a_command) = 0;
    virtual int event_type() const = 0;

};

}//namespace sb

#endif // SUBSCRIBER_HPP