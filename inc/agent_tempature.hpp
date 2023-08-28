#ifndef AGENT_TEMPATURE_HPP
#define AGENT_TEMPATURE_HPP

#include "protocol.hpp"
#include "agent.hpp"

#include <unordered_map>
#include <string>

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace sb {

class AgentTempature : public Agent{
public: 
    AgentTempature(std::string const& a_file_name);

    ~AgentTempature() noexcept = default;
    AgentTempature(AgentTempature const& a_other) = default;
    AgentTempature(AgentTempature&& a_other) = default;
    AgentTempature& operator=(AgentTempature const& a_other) = default;
    AgentTempature& operator=(AgentTempature&& a_other) = default;

    // void wraper(Protocol& a_data, Protocol& a_event);
    tcp::endpoint endpoint() const override;

private:
    tcp::endpoint m_endpoint;
};

}//namespace sb

#endif // AGENT_TEMPATURE_HPP
