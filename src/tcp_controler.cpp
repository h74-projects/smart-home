#include "client.hpp"
#include "protocol.hpp"

int main()
{
  try {
    boost::asio::io_context io_context;
    tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve("", "8080");
    sb::Client c(io_context, endpoints);

    std::thread t([&io_context](){ io_context.run(); });

    while(true); //fix this 

    c.close();
    t.join();
  }catch (std::exception& e){
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}