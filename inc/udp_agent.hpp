#ifndef UDP_AGENT_HPP
#define UDP_AGENT_HPP

#include <boost/asio.hpp>

using boost::asio::ip::udp;

namespace sb {

class UdpListner {
public: 
    UdpListner(boost::asio::io_context& io_context, unsigned short port);

    ~UdpListner() noexcept = default;
    UdpListner(UdpListner const& a_other) = default;
    UdpListner(UdpListner&& a_other) = default;
    UdpListner& operator=(UdpListner const& a_other) = default;
    UdpListner& operator=(UdpListner&& a_other) = default;

    void receive_data();

private:
    udp::socket m_socket;

};

}//namespace sb

#endif // UDP_AGENT_HPP
