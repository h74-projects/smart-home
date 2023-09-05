#include <string> 
#include <iostream>
#include <thread> //sleep_for
#include <chrono>
#include <sstream> //stringstream
#include <iomanip>

#include "protocol.hpp"

#include <boost/asio.hpp>

using boost::asio::ip::udp;

bool is_current_time_in_range(const std::string& startTime, const std::string& endTime) {
    // Get the current system time.
    auto now = std::chrono::system_clock::now();
    std::time_t now_tt = std::chrono::system_clock::to_time_t(now);
    std::tm tm_now = *std::localtime(&now_tt);

    std::tm tm_start = tm_now;
    std::tm tm_end = tm_now;

    std::istringstream ss_start(startTime);
    std::istringstream ss_end(endTime);

    // Parse hours and minutes for start and end times
    ss_start >> std::get_time(&tm_start, "%H:%M");
    ss_end >> std::get_time(&tm_end, "%H:%M");

    // Convert back to time_t for comparison
    std::time_t tt_start = std::mktime(&tm_start);
    std::time_t tt_end = std::mktime(&tm_end);

    return (now_tt >= tt_start && now_tt < tt_end);
}


int main()
{
    try
    {

        boost::asio::io_context io_context;
		udp::socket s(io_context, udp::endpoint(udp::v4(), 0));
		udp::resolver resolver(io_context);
		auto endpoints = resolver.resolve(udp::v4(), "", "5555");
		std::thread t([&io_context](){ io_context.run(); });

        while(true){
            std::string start_time_str;
            std::cout << "Enter start time (HH:MM): ";
            std::cin >> start_time_str;
            std::string end_time_str;
            std::cout << "Enter end time (HH:MM): ";
            std::cin >> end_time_str;
            while(true) {
                if (is_current_time_in_range(start_time_str, end_time_str)) {
                    std::string data = "open";
                    std::cout << data << "\n";
                    std::string id_and_data = "500" + data; //id must to be 3 bytes
                    sb::Protocol msg;
                    msg.body_length(id_and_data.size());
                    std::memcpy(msg.body(), id_and_data.c_str(), msg.body_length());
                    msg.encode_header();
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    s.async_send_to(boost::asio::buffer(msg.data(), msg.length()), *endpoints.begin(),
						[](const boost::system::error_code& error, std::size_t /*bytes_transferred*/) {
						if (!error) {
							std::cout << "Data sent successfully." << std::endl;
						} else {
							std::cerr << "Send error: " << error.message() << std::endl;
						}
					});
                    while(true) {
                        if (!is_current_time_in_range(start_time_str, end_time_str)) {
                            std::string data = "close";
                            std::cout << data << "\n";
                            std::string id_and_data = "500" + data; //id must to be 3 bytes
                            sb::Protocol msg;
                            msg.body_length(id_and_data.size());
                            std::memcpy(msg.body(), id_and_data.c_str(), msg.body_length());
                            msg.encode_header();
                            std::this_thread::sleep_for(std::chrono::seconds(1));
                            s.async_send_to(boost::asio::buffer(msg.data(), msg.length()), *endpoints.begin(),
								[](const boost::system::error_code& error, std::size_t /*bytes_transferred*/) {
								if (!error) {
									std::cout << "Data sent successfully." << std::endl;
								} else {
									std::cerr << "Send error: " << error.message() << std::endl;
								}
							});
                            break;
                        }
                    }
                }
            }
            
        }
        t.join();

	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}