#include <cstdlib>
#include <cstring>
#include <iostream>
#include <thread> 
#include <chrono>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

int main()
{
  try
  {
    boost::asio::io_context io_context;
    udp::socket s(io_context, udp::endpoint(udp::v4(), 0));
    udp::resolver resolver(io_context);
    udp::resolver::results_type endpoints = resolver.resolve(udp::v4(), "", "9090");
    
    while(true){
        std::this_thread::sleep_for(std::chrono::seconds(1));
        char request[] = "40";
        size_t request_length = std::strlen(request);
        s.send_to(boost::asio::buffer(request, request_length), *endpoints.begin());
    }

  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}