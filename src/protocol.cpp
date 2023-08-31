#include "protocol.hpp"

#include <cstdio> //sprintf
#include <cstring> //strncat
#include <iostream> //strncat
#include <sstream> //strncat

namespace sb {

const std::size_t id_length = 3;

Protocol::Protocol() noexcept
: m_body_length(0)
{
}

const char* Protocol::data() const 
{
    return m_data;
}

char* Protocol::data()
{
    return m_data;
}

std::size_t Protocol::length() const
{
    return header_length + m_body_length;
}

const char* Protocol::body() const
{
    return m_data + header_length;
}

char* Protocol::body()
{
    return m_data + header_length;
}

std::string Protocol::id()
{
    std::string id(m_data + header_length);
    id = id.substr(0, id_length);
    return id;
}

std::size_t Protocol::body_length() const
{
    return m_body_length;
}

void Protocol::body_length(std::size_t new_length)
{
    m_body_length = new_length;
    if (m_body_length > max_body_length){
        m_body_length = max_body_length;
    }
}

bool Protocol::check_packet_length() //limit the packet length
{
    char header[header_length + 1] = "";
    std::strncat(header, m_data, header_length);
    m_body_length = std::atoi(header);
    if (m_body_length > max_body_length){
        m_body_length = 0;
        return false;
    }
    return true;
}

void Protocol::encode_header()
{
    char header[header_length + 1] = "";
    std::sprintf(header, "%4d", static_cast<int>(m_body_length));
    std::memcpy(m_data, header, header_length);
}

std::string Protocol::event_type() const
{
    std::string event_string(this->data(), this->length());
    size_t found = event_string.find_last_of(' ');
    event_string = event_string.substr(found + 1);
    return event_string;
}

std::string Protocol::event_location() const
{
    std::string event_string(this->data());//this-.length??
    std::stringstream ss;
    std::string location;
    for(size_t i = 0; i < 2; ++i){
        ss << event_string;
        ss >> location;
    }
    return location;
}

std::string Protocol::event_data() const
{
    std::string event_string(this->data());//this-.length??
    std::stringstream ss;
    std::string data;
    ss << event_string;
    ss >> data;
    data = data.substr(header_length - 2);
    return data;
}

}// namespace sb