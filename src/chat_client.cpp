#include "client.hpp"

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
        sb::Event e("room_1", type);
        e.event_warper(line);

        chat_message msg;
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

      chat_message msg;
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