#ifndef AGENT_TEMPATURE_HPP
#define AGENT_TEMPATURE_HPP

#include "protocol.hpp"
#include "agent_sensor.hpp"

#include <unordered_map>
#include <string>

#include <boost/asio.hpp>

using boost::asio::ip::tcp;
namespace sb {

class AgentTempature : public AgentSensor{
public: 
    AgentTempature(SensorsId& a_sensors_id);
    ~AgentTempature() noexcept = default;

    unsigned short port() const override;
    ProtocolType protocol() const override;

private:
    unsigned short m_port;
};

extern "C" AgentSensor* create_agent(SensorsId& a_sensors_id) {
    return new AgentTempature(a_sensors_id);
}

}//namespace sb

#endif // AGENT_TEMPATURE_HPP
