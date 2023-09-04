#include "client.hpp"

namespace sb {

Client::Client(boost::asio::io_context& io_context, const tcp::resolver::results_type& endpoints)
: m_io_context(io_context)
, m_socket(io_context)
, m_data{}
{
    do_connect(endpoints);
}

void Client::write(const Protocol& msg)
{
    boost::asio::post(m_io_context, [this, msg](){ bool write_in_progress = !m_events.empty();
    m_events.push_back(msg);
    if (!write_in_progress){
        do_write();
    }});
}

void Client::close()
{
    boost::asio::post(m_io_context, [this]() { m_socket.close(); });
}

void Client::do_connect(const tcp::resolver::results_type& endpoints)
{
    boost::asio::async_connect(m_socket, endpoints, [this](boost::system::error_code ec, tcp::endpoint){
        if (!ec){
            do_read_header();
        }
    });
}

void Client::do_read_header()
{
    boost::asio::async_read(m_socket,
    boost::asio::buffer(m_read_event.data(), sb::header_length), [this](boost::system::error_code ec, std::size_t /*length*/){
        if (!ec && m_read_event.check_packet_length()){
            do_read_body();
        }else{
            m_socket.close();
        }
    });
}

void Client::do_read_body()
{
    boost::asio::async_read(m_socket, boost::asio::buffer(m_read_event.body(), m_read_event.body_length()),
    [this](boost::system::error_code ec, std::size_t /*length*/){
        if (!ec){
            std::cout.write(m_read_event.body(), m_read_event.body_length());
            std::cout << "\n";
            m_data = m_read_event.body();
            do_read_header();
        }else{
            m_socket.close();
        }
    });
}

void Client::do_write()
{
    boost::asio::async_write(m_socket, boost::asio::buffer(m_events.front().data(), m_events.front().length()),
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

std::string Client::data() 
{
    return m_data;
}

} // namespace sb
