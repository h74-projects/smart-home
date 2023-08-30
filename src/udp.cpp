#include "udp.hpp"

namespace sb {

Udp::Udp(boost::asio::io_context& io_context, const udp::resolver::results_type& endpoints)
: m_io_context(io_context)
, m_socket(io_context)
{
    do_connect(endpoints);
}

void Udp::write(const Protocol& msg)
{
    boost::asio::post(m_io_context, [this, msg](){ bool write_in_progress = !m_events.empty();
    m_events.push_back(msg);
    if (!write_in_progress){
        do_write();
    }});
}

void Udp::close()
{
    boost::asio::post(m_io_context, [this]() { m_socket.close(); });
}

void Udp::do_connect(const udp::resolver::results_type& endpoints)
{
    boost::asio::async_connect(m_socket, endpoints, [this](boost::system::error_code ec, udp::endpoint){
        if (!ec){
            do_read_header();
        }
    });
}

        
void Udp::do_read_header()
{
    m_socket.async_receive_from(
         boost::asio::buffer(m_read_event.data(), sb::header_length), sender_temp,
        [this](boost::system::error_code ec, std::size_t /*length*/){
        if (!ec && m_read_event.check_packet_length()){
            do_read_body();
        }else{
            m_socket.close();
        }
    });
}


void Udp::do_read_body()
{
    m_socket.async_receive_from(
         boost::asio::buffer(m_read_event.body(), m_read_event.body_length()), sender_temp,
        [this](boost::system::error_code ec, std::size_t /*length*/){
        if (!ec){
            std::cout.write(m_read_event.body(), m_read_event.body_length());
            std::cout << "\n";
            do_read_header();
        }else{
            m_socket.close();
        }
    });
}

void Udp::do_write()
{
    m_socket.async_send_to(
        boost::asio::buffer(m_events.front().data(), m_events.front().length()), sender_temp,
        [this](boost::system::error_code ec, std::size_t /*length*/){
        if (!ec){
            m_events.pop_front();
            if (!m_events.empty())
            {
                do_write();
            }
        }else{
            m_socket.close();
        }
    });
}

} // namespace sb