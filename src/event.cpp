#include "event.hpp"

static constexpr std::size_t id_legnth_ = 3;

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

void Event::seprate_data(std::string& a_data)
{
    a_data = a_data.substr(id_legnth_, a_data.size() - id_legnth_);
}

}//namespace sb
