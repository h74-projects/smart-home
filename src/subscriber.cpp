#include "subscriber.hpp"

namespace sb {

Subscriber::Subscriber(int a_event_type)
: m_event_type{a_event_type}
{
}

int Subscriber::event_type() const
{
    return m_event_type;
}

}// namespace sb