#include "udp.hpp"

namespace sb {

Udp::Udp(boost::asio::io_context& a_io_context)
: m_io_context(a_io_context)
, m_socket(m_io_context, udp::endpoint(udp::v4(), 0))
{
    do_read_header();
}

void Udp::write(const Protocol& msg, udp::resolver::results_type& a_endpoints)
{
    boost::asio::post(m_io_context, [this, msg, &a_endpoints](){ bool write_in_progress = !m_events.empty();
    m_events.push_back(msg);
    if (!write_in_progress){
        do_write(a_endpoints);
    }});
}

void Udp::close()
{
    boost::asio::post(m_io_context, [this]() { m_socket.close(); });
}

// void Udp::do_connect(const udp::resolver::results_type& endpoints)
// {
//     boost::asio::async_connect(m_socket, endpoints, [this](boost::system::error_code ec, udp::endpoint){
//         if (!ec){
//             do_read_header();
//         }
//     });
// }

        
void Udp::do_read_header()
{
    m_socket.async_receive(boost::asio::buffer(m_read_event.data(), sb::header_length),
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
    m_socket.async_receive(
         boost::asio::buffer(m_read_event.body(), m_read_event.body_length()),
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

void Udp::do_write(udp::resolver::results_type& a_endpoints)
{
    m_socket.async_send_to(
        boost::asio::buffer(m_events.front().data(), m_events.front().length()), *a_endpoints.begin(),
        [this, &a_endpoints](boost::system::error_code ec, std::size_t /*length*/){
        if (!ec){
            m_events.pop_front();
            if (!m_events.empty())
            {
                do_write(a_endpoints);
            }
        }else{
            m_socket.close();
        }
    });
}

} // namespace sb