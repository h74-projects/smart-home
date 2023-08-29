#include "client.hpp"
#include "protocol.hpp"

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 3)
    {
      std::cerr << "Usage: chat_client <port> <type>\n";
      return 1;
    }
    boost::asio::io_context io_context;
    tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve("", argv[1]);
    sb::Client c(io_context, endpoints);

    std::thread t([&io_context](){ io_context.run(); });
    std::string port = argv[1];
    std::string type = argv[2];

    // char line[chat_message::max_body_length + 1];
    if (port == "7070") {
      std::string line;
      while (std::getline(std::cin, line))
      {
        std::cout << "din\n";
        sb::Event e("room_1", type);
        e.event_warper(line);

        sb::Protocol msg;
        msg.body_length(line.size());
        std::memcpy(msg.body(), line.c_str(), msg.body_length());
        msg.encode_header();
        c.write(msg);
      }
    }

    if (port == "8080") {
      std::string line = "x";

      sb::Event e("subscribe", type);
      e.event_warper(line);

      sb::Protocol msg;
      msg.body_length(line.size());
      std::memcpy(msg.body(), line.c_str(), msg.body_length());
      msg.encode_header();
      std::this_thread::sleep_for(std::chrono::seconds(1));
      c.write(msg);

      while(true);
    }

    c.close();
    t.join();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}


// #include <string> 
// #include <iostream>
// #include <thread> //sleep_for
// #include <chrono> 

// #include "client.hpp"
// #include "protocol.hpp"

// #include <boost/asio.hpp>

// using boost::asio::ip::tcp;

// int main()
// {
// 	try
// 	{
// 		boost::asio::io_context io_context;
// 		tcp::resolver resolver(io_context);
// 		auto endpoints = resolver.resolve("", "8080");
// 		sb::Client c(io_context, endpoints);
// 		std::thread t([&io_context](){ io_context.run(); });

// 		// std::string data = "40";
// 		// std::string id_and_data = "100" + data; //id must to be 3 bytes
// 		// sb::Protocol msg;
//     // msg.body_length(id_and_data.size());
//     // std::memcpy(msg.body(), id_and_data.c_str(), msg.body_length());
//     // msg.encode_header();
        

// 		while(true){
// 			std::this_thread::sleep_for(std::chrono::seconds(1));
// 			c.do_read_header();
// 		}

// 	}
// 	catch (std::exception& e)
// 	{
// 		std::cerr << "Exception: " << e.what() << "\n";
// 	}

// 	return 0;
// }