#include "udp_agent.hpp"

#include "client.hpp"
#include "event.hpp"

#include <cstdlib> //size_t
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

namespace sb {

enum { max_length = 1024 }; 

UdpListner::UdpListner(boost::asio::io_context& io_context, unsigned short port)
: m_socket(io_context, udp::endpoint(udp::v4(), port))
{
}

void UdpListner::receive_data()
{
    char data[max_length];
    udp::endpoint sender_endpoint;
    boost::asio::io_context send_io_context;

    tcp::resolver resolver(send_io_context);
    auto endpoints = resolver.resolve("", "7070");
    sb::Client c(send_io_context, endpoints);

    std::thread t([&send_io_context](){ send_io_context.run(); });
    std::string type = "1";

    for (;;){
        size_t length =  m_socket.receive_from(boost::asio::buffer(data, max_length), sender_endpoint);   
        std::string line(data);
        line = line.substr(0, length);
        std::cout << "for_test: " << line << "\n";

        std::string event = line;
        sb::Event e("room_1", type);
        e.event_warper(event);

        sb::Protocol msg;
        msg.body_length(event.size());
        std::memcpy(msg.body(), event.c_str(), msg.body_length());
        msg.encode_header();
        c.write(msg);
    }

    c.close();
    t.join();
}


}// namespace sb

int main()
{
    try{
        boost::asio::io_context io_context;

        sb::UdpListner ul(io_context, 9090);
        ul.receive_data();
    } catch (std::exception& e){
        std::cerr << "Exception: " << e.what() << "\n";
    }
}

