#include "protocol.hpp"

#include <cstdio> //sprintf
#include <cstdlib> //size_t
#include <cstring> //strncat

namespace sb {

Protocol::Protocol() noexcept
: m_body_length(0)
{
}

const char* Protocol::data() const //replace with &
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

}// namespace sb