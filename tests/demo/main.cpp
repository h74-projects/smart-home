#include "server.hpp"

#include "agent_tempature.hpp"

#include <iostream>
#include <exception>

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main()
{
    try{
        
        sb::AgentTempature at;

        boost::asio::io_context io_context;
        tcp::endpoint controler_endpoint(tcp::v4(), 8080); // controler -> false
        tcp::endpoint sensor_endpoint(at.endpoint());
        sb::Server s(io_context, sensor_endpoint, controler_endpoint, at);

        io_context.run();
        
    }catch (std::exception& e){
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}