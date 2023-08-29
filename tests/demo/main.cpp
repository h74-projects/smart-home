#include "server.hpp"

#include "agent_tempature.hpp"
#include "agent_ac.hpp"
#include "agent.hpp"
#include "subscribe_manager.hpp"

#include <iostream>
#include <exception>
#include <memory>
#include <thread>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream> //ifstream
#include <nlohmann/json.hpp> //nlohmann::json
#include <stdexcept> //runtime error

#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace sb;

typedef std::unordered_map<std::string, std::vector<std::string>> ControlersAgents; 

void set_controler_agents(ControlersAgents& a_controler_agents)
{
    std::ifstream sensors_id_file("../../assets/agents.dat");
    if(!sensors_id_file) {
        std::runtime_error("file opcode_map.dat could not be opened!");
    }
    nlohmann::json json_sendors_id;
    sensors_id_file >> json_sendors_id;
    a_controler_agents = json_sendors_id.get<ControlersAgents>();
}


int main()
{
    try{
        // ControlersAgents controler_agents;
        // set_controler_agents(controler_agents);

        SubscribeManager sm;

        std::unique_ptr<Agent> agent_ptr = std::make_unique<AgentTempature>("../../assets/sensor_id.dat");
        std::unique_ptr<Agent> agent_controler_ptr = std::make_unique<AgentAc>("../../assets/sensor_id.dat");//all the controlers

        boost::asio::io_context io_context;
        Server s_controler(io_context, *(dynamic_cast<AgentAc*>(agent_controler_ptr.get())), false, sm);
        Server s_sensor(io_context, *(dynamic_cast<AgentTempature*>(agent_ptr.get())), true, sm);

        io_context.run();
        
    }catch (std::exception& e){
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}