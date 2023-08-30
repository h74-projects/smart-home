#ifndef AGENT_SENSOR_HPP
#define AGENT_SENSOR_HPP

#include "protocol.hpp"
#include "agent.hpp"

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace sb {

class AgentSensor : public Agent{
public:
    virtual ~AgentSensor() = default;
    
    virtual tcp::endpoint endpoint() const = 0;

    AgentSensor(std::string const& a_file_name);

    void wraper(Protocol& a_data, Protocol& a_event);
    void set_sensors_id();

private:
    std::string const& m_file_name;
    std::unordered_map<std::string, std::vector<std::string>> m_sensors_id;

};

}//namespace sb

#endif // AGENT_SENSOR_HPP
