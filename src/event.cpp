#include "event.hpp"

namespace sb {

Event::Event(std::string const& a_location, std::string const& a_event_type) noexcept
: m_event_type{a_event_type}
, m_location{a_location}
{
}

void Event::event_warper(std::string& a_data)
{
    a_data += ' ' + m_location + ' ' + m_event_type;
}

}//namespace sb