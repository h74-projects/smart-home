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
        std::unique_ptr<Agent> agent_ptr = std::make_unique<AgentTempature>("../../assets/sensor_id.dat");
        std::unique_ptr<Agent> agent_controler_ptr = std::make_unique<AgentAc>("../../assets/sensor_id.dat");

        boost::asio::io_context io_context;
        Server s_controler(io_context, *(dynamic_cast<AgentAc*>(agent_controler_ptr.get())), false, sm);
        Server s_sensor(io_context, *(dynamic_cast<AgentTempature*>(agent_ptr.get())), true, sm);

        io_context.run();
        
    }catch (std::exception& e){
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}