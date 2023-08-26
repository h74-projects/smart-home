#include "udp.server.hpp"

#include <cstdlib>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

namespace sb {

enum { max_length = 1024 };

UdpListner::UdpListner(boost::asio::io_context& io_context, unsigned short port)
:m_socket(io_context, udp::endpoint(udp::v4(), port))
{
}

std::string UdpListner::receive_data()
{
    char data[max_length];
    udp::endpoint sender_endpoint;
    std::stringstream buffer;
    std::string res;
    for (;;){
        size_t length =  m_socket.receive_from(boost::asio::buffer(data, max_length), sender_endpoint);   
        std::string line(data);
        line = line.substr(0, length);
        // std::cout << line << "\n";
        // buffer << line;
        // buffer >> res;
        // std::cout << res << "\n";
        return line;
    }
}

}// namespace sb


// int main()
// {
//   try
//   {
//     // if (argc != 2)
//     // {
//     //      ::cerr << "Usage: blocking_udp_echo_server <port>\n";
//     //   return 1;
//     // }

//     boost::asio::io_context io_context;

//     sb::UdpListner ul(io_context, 9090);
//     std::stringstream buffer;
//     ul.receive_data();
//   }
// catch (std::exception& e)
//   {
//     std::cerr << "Exception: " << e.what() << "\n";
//   }

//   return 0;
// }