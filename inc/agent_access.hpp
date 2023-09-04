#ifndef AGENT_ACCESS_HPP
#define AGENT_ACCESS_HPP

#include "protocol.hpp"
#include "agent_sensor.hpp"

#include <unordered_map>
#include <string>

#include <boost/asio.hpp>

using boost::asio::ip::tcp;
namespace sb {

class AgentAccess : public AgentSensor{
public: 
    AgentAccess(SensorsId& a_sensors_id);
    ~AgentAccess() noexcept = default;

    uint16_t port() const override;
    ProtocolType protocol() const override;

private:
    uint16_t m_port;
};

extern "C" AgentSensor* create_agent(SensorsId& a_sensors_id) {
    return new AgentAccess(a_sensors_id);
}

}//namespace sb

#endif // AGENT_ACCESS_HPP
