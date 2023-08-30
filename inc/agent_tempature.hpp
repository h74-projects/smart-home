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

    tcp::endpoint endpoint() const override;

private:
    tcp::endpoint m_endpoint;
};

}//namespace sb

#endif // AGENT_TEMPATURE_HPP
