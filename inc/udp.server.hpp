#ifndef UDP_LISTNER_HPP
#define UDP_LISTNER_HPP

#include <boost/asio.hpp>

using boost::asio::ip::udp;


namespace sb {

class UdpListner {
public:
    UdpListner(boost::asio::io_context& io_context, unsigned short port);

    std::string receive_data();

private:
    udp::socket m_socket;

};

}//namespace sb

#endif // UDP_LISTNER_HPP
