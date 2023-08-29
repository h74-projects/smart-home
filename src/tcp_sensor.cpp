#include <string> 
#include <iostream>
#include <thread> //sleep_for
#include <chrono> 

#include "client.hpp"
#include "protocol.hpp"

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main()
{
	try
	{
		boost::asio::io_context io_context;
		tcp::resolver resolver(io_context);
		auto endpoints = resolver.resolve("", "7070");
		sb::Client c(io_context, endpoints);
		std::thread t([&io_context](){ io_context.run(); });

		std::string data = "40"; //TODO change to return randoms numbers
		std::string id_and_data = "100" + data; //id must to be 3 bytes
		sb::Protocol msg;
        msg.body_length(id_and_data.size());
        std::memcpy(msg.body(), id_and_data.c_str(), msg.body_length());
        msg.encode_header();
        

		while(true){
			std::this_thread::sleep_for(std::chrono::seconds(1));
			c.write(msg);
		}

	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}