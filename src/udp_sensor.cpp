#include <string> 
#include <iostream>
#include <thread> //sleep_for
#include <chrono> 

// #include "udp.hpp"
#include "protocol.hpp"

#include <boost/asio.hpp>

using boost::asio::ip::udp;


int main()
{
	try{

		boost::asio::io_context io_context;
		udp::socket s(io_context, udp::endpoint(udp::v4(), 0));
		udp::resolver resolver(io_context);
		auto endpoints = resolver.resolve(udp::v4(), "", "7070");
		std::thread t([&io_context](){ io_context.run(); });

		std::string data = "40"; 
		std::string id_and_data = "100" + data; //id must to be 3 bytes
		sb::Protocol msg;
		msg.body_length(id_and_data.size());
		std::memcpy(msg.body(), id_and_data.c_str(), msg.body_length());
		msg.encode_header();

	while(true){

		std::this_thread::sleep_for(std::chrono::seconds(1));
		s.async_send_to(boost::asio::buffer(msg.data(), msg.length()), *endpoints.begin(),
    		[](const boost::system::error_code& error, std::size_t /*bytes_transferred*/) {
			if (!error) {
				std::cout << "Data sent successfully." << std::endl;
			} else {
				std::cerr << "Send error: " << error.message() << std::endl;
			}
		});
	}
	t.join();

	}catch (std::exception& e){
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}