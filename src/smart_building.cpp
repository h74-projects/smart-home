#include "smart_building.hpp"
#include "server.hpp"
// #include "agent_sensor.hpp"
// #include "agent_ac.hpp"
#include "subscribe_manager.hpp"

#include <exception>
#include <memory> //unique_ptr
#include <iostream> //std::cerr
#include <fstream> //std::ifstream
#include <stdexcept> //runtime error
#include <nlohmann/json.hpp> //nlohmann::json
#include <dlfcn.h> //dlsym, dlerror, dlopen
#include <thread> 
#include <vector> 

#include <boost/asio.hpp>


using boost::asio::ip::tcp;

namespace sb {

Agents SmartBuilding::make_agent(std::pair<const std::string, SensorsId>& a_sensors_type)
{
    void* agent_sensor = dlopen(m_sensor_agents[a_sensors_type.first].c_str(), RTLD_LAZY);
    void* agent_controler = dlopen(m_controler_agents[a_sensors_type.first].c_str(), RTLD_LAZY);

    if (!agent_sensor || !agent_controler) {
        std::cerr << "Cannot load library: " << dlerror() << '\n';
        return std::make_tuple(nullptr, nullptr);
    }

    dlerror();
    create_agent_func* create_agent_sensor_lib  = (create_agent_func*)dlsym(agent_sensor, "create_agent");
    create_agent_controler_func* create_agent_controler_lib  = (create_agent_controler_func*)dlsym(agent_controler, "create_agent");
    const char* dlsym_error = dlerror();

    if (dlsym_error) {
        std::cerr << "Cannot load symbol create: " << dlsym_error << '\n';
        return std::make_tuple(nullptr, nullptr);
    }

    return std::make_tuple(create_agent_sensor_lib, create_agent_controler_lib);
}

void func(boost::asio::io_context& io_context, std::unique_ptr<AgentSensor>  agent_ptr,
          std::unique_ptr<AgentSensor>  agent_controler_ptr, SubscribeManager& sm)
{
    Server s_controler(io_context, *agent_controler_ptr, false, sm);
    Server s_sensor(io_context, *agent_ptr, true, sm); 
    io_context.run();
}

void SmartBuilding::run()
{   
    load_sensor_agents_type("../../assets/types_libraries.dat");
    load_controlers_agents_type("../../assets/types_controlers.dat");
    load_sensors("../../assets/sensor_id.dat");

    boost::asio::io_context io_context;
    std::vector<Server> servers;
    // std::thread t([&io_context](){ io_context.run(); });
    // t.detach();
    for(auto sensors_type : m_sensors_per_type){

        try{
            SubscribeManager sm;
            
            std::unique_ptr<AgentSensor> agent_ptr(std::get<0>(make_agent(sensors_type))((m_sensors_per_type[sensors_type.first]))); //null check?
            std::unique_ptr<AgentControler> agent_controler_ptr(std::get<1>(make_agent(sensors_type))()); //null check?

            // std::thread t([](auto io_context, auto agent_controler_ptr, auto agent_ptr, auto sm)
            // { 
            //     Server s_controler(io_context, *agent_controler_ptr, false, sm);
            //     Server s_sensor(io_context, *agent_ptr, true, sm); 
            //     io_context.run();
            // });

            // std::thread thread([&io_context, agent_controler_ptr = std::move(agent_controler_ptr), agent_ptr = std::move(agent_ptr), sm]() {
            // Server s_controler(io_context, *agent_controler_ptr, false, sm);
            // Server s_sensor(io_context, *agent_ptr, true, sm);
            // io_context.run();
            //  });

            // thread.detach(); // Detach the thread

            // std::thread thread(func,io_context, std::move(agent_ptr), std::move(agent_controler_ptr), sm);
            // thread.detach(); // Detach the thread
            servers.emplace_back(io_context, *agent_controler_ptr, false, sm);
            servers.emplace_back(io_context, *agent_ptr, true, sm);


            // Server s_controler(io_context, *agent_controler_ptr, false, sm);
            // Server s_sensor(io_context, *agent_ptr, true, sm);
            

        }catch (std::exception& e){
            std::cerr << "Exception: " << e.what() << "\n";
        }
    }
    io_context.run();
    // t.join();
}

namespace {
void load_json(nlohmann::json& a_json, std::string const& a_path)
{
    std::ifstream configure(a_path);
    if(!configure) {
        std::runtime_error("configuration file could not be loaded!");
    }
    configure >> a_json;
}

}// namespace

void SmartBuilding::load_sensor_agents_type(std::string const& a_path)
{
    nlohmann::json json_configure;
    load_json(json_configure, a_path);
    m_sensor_agents = json_configure.get<std::unordered_map<std::string, std::string>>();
}

void SmartBuilding::load_controlers_agents_type(std::string const& a_path)
{
    nlohmann::json json_configure;
    load_json(json_configure, a_path);
    m_controler_agents = json_configure.get<std::unordered_map<std::string, std::string>>();
}

void SmartBuilding::load_sensors(std::string const& a_path)
{
    nlohmann::json json_configure;
    load_json(json_configure, a_path);
    m_sensors_per_type = json_configure.get<EventType>();
}

} // namespace sb
