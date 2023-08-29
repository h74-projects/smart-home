#include "server.hpp"
#include "agent_tempature.hpp"
#include "agent_ac.hpp"
#include "agent_sensor.hpp"
#include "agent_controler.hpp"
#include "agent.hpp"
#include "subscribe_manager.hpp"

#include <exception>
#include <memory> //unique_ptr
#include <iostream> //std::cerr
#include <fstream> //ifstream
#include <nlohmann/json.hpp> //nlohmann::json
#include <stdexcept> //runtime error

#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace sb;

int main()
{
    try{
        SubscribeManager sm;

        std::unique_ptr<AgentSensor> agent_ptr = std::make_unique<AgentTempature>("../../assets/sensor_id.dat");
        std::unique_ptr<AgentControler> agent_controler_ptr = std::make_unique<AgentAc>();//TODO controlers for agent?

        boost::asio::io_context io_context;
        Server s_controler(io_context, *(dynamic_cast<AgentAc*>(agent_controler_ptr.get())), false, sm);
        Server s_sensor(io_context, *(dynamic_cast<AgentTempature*>(agent_ptr.get())), true, sm);

        io_context.run();
        
    }catch (std::exception& e){
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}