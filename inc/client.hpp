#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "protocol.hpp"
#include "event.hpp"

#include <boost/asio.hpp>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <thread>
#include <string>

using boost::asio::ip::tcp;

namespace sb {

typedef std::deque<Protocol> Events;

class Client {
public:
  Client(boost::asio::io_context& io_context, const tcp::resolver::results_type& endpoints);

  void write(const Protocol& msg);
  void close();
  void do_read_header();
  std::string data();
  
private:
  void do_connect(const tcp::resolver::results_type& endpoints);
  void do_read_body();
  void do_write();
  
private:
  boost::asio::io_context& m_io_context;
  tcp::socket m_socket;
  Protocol m_read_event;
  Events m_events;
  std::string m_data;

};

} // namespcae sb

#endif // CLIENT_HPP