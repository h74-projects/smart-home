#ifndef AGENT_SENSOR_HPP
#define AGENT_SENSOR_HPP

#include "protocol.hpp"
#include "agent.hpp"

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace sb {

typedef std::unordered_map<std::string, std::vector<std::string>> SensorsId;

class AgentSensor : public Agent{
public:
    virtual ~AgentSensor() = default;
    
    virtual unsigned short port() const = 0;
    virtual ProtocolType protocol() const = 0;

    AgentSensor(SensorsId& a_sensors_id);

    void wraper(Protocol& a_data, Protocol& a_event);

private:
    SensorsId& m_sensors_id;

};

}//namespace sb

#endif // AGENT_SENSOR_HPP
