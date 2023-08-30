#ifndef EVENT_HPP
#define EVENT_HPP

#include <string>

namespace sb {

class Event{
public:
    explicit Event(std::string const& a_location, std::string const& a_event_type) noexcept;
    ~Event() noexcept = default;

    void event_warper(std::string& a_data);
    void seprate_data(std::string& a_data);

private:
    std::string m_event_type;
    std::string m_location;
};

}//namespace sb

#endif // EVENT_HPP
