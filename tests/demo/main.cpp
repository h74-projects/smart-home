#include "server.hpp"

#include <iostream>
#include <exception>

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main()
{
  try
  {
    // if (argc < 2)
    // {
    //   std::cerr << "Usage: chat_server <port> [<port> ...]\n";
    //   return 1;
    // }

    boost::asio::io_context io_context;


    // for (int i = 1; i < argc; ++i)
    // {
    tcp::endpoint endpoint1(tcp::v4(), 7070); //sensor ->true
    tcp::endpoint endpoint2(tcp::v4(), 8080); // controler -> false
    sb::Server s(io_context, endpoint1, endpoint2);
    // }

    io_context.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}