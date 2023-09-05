#include <string> 
#include <iostream>
#include <thread> //sleep_for
#include <chrono> 

#include "protocol.hpp"

#include <boost/asio.hpp>

using boost::asio::ip::udp;


int main(int argc, char* argv[])
{
	try{
	
		if(argc != 2){
			return 0;
		}
		boost::asio::io_context io_context;
		udp::socket s(io_context, udp::endpoint(udp::v4(), std::atoi(argv[1])));
		std::thread t([&io_context](){ io_context.run(); });
		sb::Protocol msg;
    	udp::endpoint sender_endpoint;

		while(true){
			std::this_thread::sleep_for(std::chrono::seconds(1));
			s.receive_from(boost::asio::buffer(msg.data(), 100), sender_endpoint);
    		std::cout <<  msg.body() <<  "\n";
		}

		t.join();

	}catch (std::exception& e){
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}




