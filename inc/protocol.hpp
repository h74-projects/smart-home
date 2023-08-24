#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include <boost/asio.hpp>

using boost::asio::ip::tcp;


namespace sb {

static constexpr std::size_t header_length = 4;
static constexpr std::size_t max_body_length = 512;

class Protocol {
public:
    Protocol();

    ~Protocol() noexcept = default;
    // Protocol(Protocol const& a_other);
    // Protocol(Protocol&& a_other);
    // Protocol& operator=(Protocol const& a_other);
    // Protocol& operator=(Protocol&& a_other);

    const char* data() const;
    char* data();
    const char* body() const;
    char* body();
    std::size_t length() const;
    std::size_t body_length() const;
    void body_length(std::size_t new_length);
    void encode_header();
    bool decode_header();


private:
    char m_data[header_length + max_body_length];
    std::size_t m_body_length; //size_t??
};

}//namespace sb

#endif // PROTOCOL_HPP
