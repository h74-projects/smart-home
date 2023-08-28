// #include <string> 
// #include <iostream>
// #include <thread> //sleep_for
// #include <chrono> 

// #include <boost/asio.hpp>

// using boost::asio::ip::udp;

// int main()
// {
// 	try
// 	{
// 		boost::asio::io_context io_context;
// 		udp::socket s(io_context, udp::endpoint(udp::v4(), 0));
// 		udp::resolver resolver(io_context);
// 		udp::resolver::results_type endpoints = resolver.resolve(udp::v4(), "", "7070");

// 		while(true){
// 			std::this_thread::sleep_for(std::chrono::seconds(1));
// 			std::string data = "40";
// 			s.send_to(boost::asio::buffer(data.c_str(), data.size()), *endpoints.begin());
// 		}

// 	}
// 	catch (std::exception& e)
// 	{
// 		std::cerr << "Exception: " << e.what() << "\n";
// 	}

// 	return 0;
// }


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

		std::string data = "40";
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

// #include <cstdlib>
// #include <cstring>
// #include <iostream>
// #include <boost/asio.hpp>

// using boost::asio::ip::tcp;

// enum { max_length = 1024 };

// int main()
// {
//   try
//   {

//     boost::asio::io_context io_context;

//     tcp::socket s(io_context);
//     tcp::resolver resolver(io_context);
//     boost::asio::connect(s, resolver.resolve("", "7070"));

// 	while(true){

		
// 		char request[max_length] = "40";
// 		size_t request_length = std::strlen(request);
// 		boost::asio::write(s, boost::asio::buffer(request, request_length));
// 	}

    
//   }
//   catch (std::exception& e)
//   {
//     std::cerr << "Exception: " << e.what() << "\n";
//   }

//   return 0;
// }
