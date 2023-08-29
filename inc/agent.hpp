#ifndef AGENT_HPP
#define AGENT_HPP

#include "protocol.hpp"

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace sb {

class Agent {
public:
    virtual ~Agent() = default;
    
    virtual tcp::endpoint endpoint() const = 0;
    virtual bool check_event(Protocol const& a_event, Protocol& a_command) = 0;

    Agent(std::string const& a_file_name);

    void wraper(Protocol& a_data, Protocol& a_event);
    void set_sensors_id();

    virtual int event_type() const = 0;

protected:
    Agent(Agent const& a_other) = default;
    Agent& operator=(Agent const& a_other) = default;

private:
    std::string const& m_file_name;
    std::unordered_map<std::string, std::vector<std::string>> m_sensors_id;

};

}//namespace sb

#endif // AGENT_HPP
