#ifndef UDP_HPP
#define UDP_HPP

#include "protocol.hpp"
#include "event.hpp"

#include <boost/asio.hpp>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <thread>

using boost::asio::ip::udp;

namespace sb {

typedef std::deque<Protocol> Events;

class Udp {
public:
  explicit Udp(boost::asio::io_context& io_context);

  void write(const Protocol& msg, udp::resolver::results_type& a_endpoints);
  void close();
  void do_read_header();
  
private:
  void do_connect(const udp::resolver::results_type& endpoints);
  void do_read_body();
  void do_write(udp::resolver::results_type& a_endpoints);
  
private:
  boost::asio::io_context& m_io_context;
  udp::socket m_socket;
  Protocol m_read_event;
  Events m_events;
  udp::endpoint sender_temp;
  
};

} // namespcae sb

#endif // UDP_HPP