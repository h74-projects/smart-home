#ifndef AGENT_HOTWATER_HPP
#define AGENT_HOTWATER_HPP

#include "protocol.hpp"
#include "agent_sensor.hpp"

#include <unordered_map>
#include <string>

#include <boost/asio.hpp>

using boost::asio::ip::tcp;
namespace sb {

class AgentHotWater : public AgentSensor{
public: 
    AgentHotWater(SensorsId& a_sensors_id);
    ~AgentHotWater() noexcept = default;

    unsigned short port() const override;
    ProtocolType protocol() const override;

private:
    unsigned short m_port;
};

extern "C" AgentSensor* create_agent(SensorsId& a_sensors_id) {
    return new AgentHotWater(a_sensors_id);
}

}//namespace sb

#endif // AGENT_HOTWATER_HPP
