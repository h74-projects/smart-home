#include <cstdlib>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

enum { max_length = 1024 };

class UdpListner {
public:
    UdpListner(boost::asio::io_context& io_context, unsigned short port)
    :m_socket(io_context, udp::endpoint(udp::v4(), port))
    {
    }

    void receive_data(std::stringstream& a_buffer)
    {
        char data[max_length];
        udp::endpoint sender_endpoint;
        for (;;){
            size_t length =  m_socket.receive_from(boost::asio::buffer(data, max_length), sender_endpoint);   
            std::string line(data);
            line = line.substr(0, length);
            std::cout << line << "\n";
            a_buffer << line;
        }
    }

private:
    udp::socket m_socket;

};


int main()
{
  try
  {
    // if (argc != 2)
    // {
    //      ::cerr << "Usage: blocking_udp_echo_server <port>\n";
    //   return 1;
    // }

    boost::asio::io_context io_context;

    UdpListner ul(io_context, 9090);
    std::stringstream buffer;
    ul.receive_data(buffer);
  }
catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}