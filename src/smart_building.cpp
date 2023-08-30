#include "smart_building.hpp"
#include "server.hpp"
#include "agent_sensor.hpp"
#include "agent_ac.hpp"
#include "subscribe_manager.hpp"

#include <exception>
#include <memory> //unique_ptr
#include <iostream> //std::cerr
#include <fstream> //std::ifstream
#include <stdexcept> //runtime error
#include <nlohmann/json.hpp> //nlohmann::json
#include <vector>
#include <dlfcn.h> //dlsym, dlerror, dlopen

#include <boost/asio.hpp>

typedef std::unordered_map<std::string, std::vector<std::string>> SensorsId;
typedef std::unordered_map<std::string, SensorsId> EventType;
typedef sb::AgentSensor* (create_agent_func)(SensorsId&);
using boost::asio::ip::tcp;
namespace sb {


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
        // load the triangle library
        void* agent = dlopen("../libraries/agent_tempature.so", RTLD_LAZY);
        if (!agent) {
            std::cerr << "Cannot load library: " << dlerror() << '\n';
            return;
        }
        // reset errors
        dlerror();
        // load the symbols
        create_agent_func* create_agent_lll  = (create_agent_func*)dlsym(agent, "create_agent");
        if (const char* dlsym_error = dlerror(); !dlsym_error) {
            std::cerr << "Cannot load symbol create: " << dlsym_error << '\n';
            return;
        }
        // create an instance of the class
        std::unique_ptr<AgentSensor> agent_ptr(create_agent_lll(sensors_per_type["1"]));
        // unload the triangle library

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
