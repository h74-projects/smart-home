#include "session.hpp"


namespace sb {

Session::Session(tcp::socket a_socket, SubscribeManager& a_subscribtion, bool a_type)
: m_socket(std::move(a_socket))
, m_subscribtion(a_subscribtion)
, m_type{a_type}
{
}

void Session::start()
{
    if(m_type){//sensor socket state
        do_read_header(); //need this reader?
    }else {//controler socket state
        m_subscribtion.join(shared_from_this());
    }
}

void Session::deliver(Protocol const& a_msg)
{
    bool write_in_progress = !m_write_msgs.empty();
    m_write_msgs.push_back(a_msg);
    if (!write_in_progress)
    {
        do_write();
    }
}

void Session::do_read_header()
{
    auto self(shared_from_this());
    boost::asio::async_read(m_socket, boost::asio::buffer(m_read_msg.data(), sb::header_length), 
        [this, self](boost::system::error_code ec, std::size_t /*length*/){ //length comment
            if (!ec && m_read_msg.check_packet_length()){
                do_read_body();
            }else {
                m_subscribtion.leave(shared_from_this());
            }
        });
}

void Session::do_read_body()
{
    auto self(shared_from_this());
    boost::asio::async_read(m_socket, boost::asio::buffer(m_read_msg.body(), m_read_msg.body_length()),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (!ec){
                m_subscribtion.deliver(m_read_msg);
                do_read_header();
            }else {
                m_subscribtion.leave(shared_from_this());
            }
        });
}

void Session::do_write()
{
    auto self(shared_from_this());
    boost::asio::async_write(m_socket, boost::asio::buffer(m_write_msgs.front().data(), m_write_msgs.front().length()),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (!ec) {
                m_write_msgs.pop_front();
            if (!m_write_msgs.empty()) { // change this if to elseif?
                do_write();
            }
            } else {
                m_subscribtion.leave(shared_from_this());
            }
        });
}

}// namespace sb