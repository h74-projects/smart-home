#include "smart_building.hpp"
#include "server.hpp"
#include "agent_tempature.hpp"
#include "agent_ac.hpp"
#include "subscribe_manager.hpp"

#include <exception>
#include <memory> //unique_ptr
#include <iostream> //std::cerr
#include <fstream> //std::ifstream
#include <stdexcept> //runtime error
#include <nlohmann/json.hpp> //nlohmann::json
#include <vector>

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace sb {

typedef std::unordered_map<std::string, std::vector<std::string>> SensorsId;
typedef std::unordered_map<std::string, SensorsId> EventType;

void SmartBuilding::run()
{   
    std::ifstream configure("../../assets/sensor_id.dat");
    if(!configure) {
        std::runtime_error("configuration file could not be loaded!");
    }
    nlohmann::json json_configure;
    configure >> json_configure;
    auto sensors_per_type = json_configure.get<EventType>();

    try{
        SubscribeManager sm;

        std::unique_ptr<AgentSensor> agent_ptr = std::make_unique<AgentTempature>(sensors_per_type["1"]);
        std::unique_ptr<AgentControler> agent_controler_ptr = std::make_unique<AgentAc>();//TODO controlers for agent?

        boost::asio::io_context io_context;
        Server s_controler(io_context, *agent_controler_ptr, false, sm);
        Server s_sensor(io_context, *agent_ptr, true, sm);

        io_context.run();

    }catch (std::exception& e){
        std::cerr << "Exception: " << e.what() << "\n";
    }
}

void SmartBuilding::load_types(std::string a_path)
{
    std::ifstream configure(a_path);
    if(!configure) {
        std::runtime_error("configuration file could not be loaded!");
    }
    nlohmann::json json_configure;
    configure >> json_configure;
    m_libraries = json_configure.get<std::unordered_map<std::string, std::string>>();
}

} // namespace sb