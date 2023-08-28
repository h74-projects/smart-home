#include "server.hpp"

#include "agent_tempature.hpp"
#include "agent_ac.hpp"
#include "agent.hpp"
#include "subscribe_manager.hpp"

#include <iostream>
#include <exception>
#include <memory>
#include <thread>

#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace sb;

int main()
{
    try{
        SubscribeManager sm;
        // sb::AgentTempature at;
        std::unique_ptr<Agent> agent_ptr = std::make_unique<AgentTempature>();
        std::unique_ptr<Agent> agent_controler_ptr = std::make_unique<AgentAc>();

        // boost::asio::io_context io_context_controler;
        boost::asio::io_context io_context;
        // tcp::endpoint controler_endpoint(tcp::v4(), 8080); // controler -> false
        // tcp::endpoint sensor_endpoint(dynamic_cast<AgentTempature*>(agent_ptr.get())->endpoint());
        
        Server s_controler(io_context, *(dynamic_cast<AgentAc*>(agent_controler_ptr.get())), false, sm);
        Server s_sensor(io_context, *(dynamic_cast<AgentTempature*>(agent_ptr.get())), true, sm);


        // std::thread t_sensor([&io_context_sensor](){ io_context_sensor.run(); });
        // std::thread t_controler([&io_context_controler](){ io_context_controler.run(); });
        io_context.run();
        // io_context_sensor.run();
        // t_sensor.join();
        // t_controler.join();
        
    }catch (std::exception& e){
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}