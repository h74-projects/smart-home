#include "smart_building.hpp"
#include "udp_server.hpp"
#include "server.hpp"
#include "subscribe_manager.hpp"
#include "session_udp.hpp"

#include <exception>
#include <memory> //unique_ptr
#include <fstream> //std::ifstream
#include <stdexcept> //runtime error
#include <nlohmann/json.hpp> //nlohmann::json
#include <thread> 
#include <list> 

#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using boost::asio::ip::udp;

namespace sb {

void SmartBuilding::run()
{   
    load_sensor_agents_type("../../assets/types_libraries.dat");
    load_controlers_agents_type("../../assets/types_controlers.dat");
    load_sensors("../../assets/sensor_id.dat");

    std::list<UdpServer> udp_servers;
    std::list<Server> tcp_servers;
    boost::asio::io_context io_context;

    try{
        SubscribeManager sm;
        for(auto sensors_type : m_sensors_per_type){
            std::unique_ptr<AgentSensor> agent_ptr(make_agent<create_agent_func>(sensors_type.first, m_sensor_agents)(m_sensors_per_type[sensors_type.first])); //null check?
            if(agent_ptr->protocol() == ProtocolType::TCP){
                tcp_servers.emplace_back(io_context, std::move(agent_ptr), true, sm);
            }else{
                udp_servers.emplace_back(io_context, std::move(agent_ptr), true, sm);
            }
        }

        for(auto controler_type : m_controler_agents){
            std::unique_ptr<AgentControler> agent_controler_ptr(make_agent<create_agent_controler_func>(controler_type.first, m_controler_agents)()); 
            if(agent_controler_ptr->protocol() == ProtocolType::TCP){
                tcp_servers.emplace_back(io_context, std::move(agent_controler_ptr), false, sm);
            }else{
                udp_servers.emplace_back(io_context, std::move(agent_controler_ptr), false, sm);
            }
        }
        
        io_context.run();

    }catch (std::exception& e){
        std::cerr << "Exception: " << e.what() << "\n";
    }
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
