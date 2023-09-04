#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <cstdio> // popen
#include <cstring> // memset
#include <iostream>
#include "client.hpp"
#include "protocol.hpp"

#include "plot.h"

class Pinger : public sf::Drawable
{
public:
    Pinger()
    // : dns_(dns)
    {
        m_plot.setSize(sf::Vector2f(600, 400));
        m_plot.setTitle("Tempature");
        m_plot.setFont("../../assets/font.ttf");
        m_plot.setXLabel("Seconds");
        m_plot.setYLabel("Tempature C");
        m_plot.setBackgroundColor(sf::Color(rand()%255, rand()%255, rand()%255));
        m_plot.setTitleColor(sf::Color::Black);
        // m_plot.setPosition(sf::Vector2f(598*1, 398*1));
        sf::plot::Curve &curve = m_plot.createCurve("Tempature", sf::Color::Red);
        curve.setFill(rand() % 2);
        curve.setThickness(2 + rand() % 10);
        curve.setColor(sf::Color(rand()%255, rand()%255, rand()%255));
        curve.setLimit(10 + rand() % 100);
    }

    void update(std::string a_data)
    {
        sf::plot::Curve &curve = m_plot.getCurve("Tempature");
        // curve.addValue(ping(dns_));
        // int n = 5;
        // std::cin >> n;
        curve.addValue(stoi(a_data));
        m_plot.prepare();
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_plot, states);
    }

    /// launch the ping command and get the ping ms result
    /// not safe !
    /// better in a thread !
    float ping(const std::string& dns)
    {
        std::string cmd = "ping " + dns + " -c 1";
        FILE* file = popen(cmd.c_str(), "r");
        if(!file) return -1.0f;
        char buffer[1024];
        std::memset(buffer, 0, 1024*sizeof(char));
        if(fread(buffer, sizeof(char), 1024, file) == 0)
        {
            pclose(file);
            return -1.0f;
        }
        std::string in(buffer);
        size_t pos = in.find("time=");
        size_t end_pos = in.find(" ms", pos+1);
        if(pos == std::string::npos || end_pos == std::string::npos)
        {
            pclose(file);
            return -1.0f;
        }
        in = in.substr(pos+5, end_pos-(pos+5));
        pclose(file);
        return std::atof(in.c_str());
    }

private:
    sf::plot::Plot m_plot;
    // std::string m_dns;
};


int main(int argc, char* argv[])
{
    // initialize the srand
    // srand (time(NULL));

    sf::RenderWindow window(sf::VideoMode(600, 400), "SFML plot", sf::Style::Default);

    sf::Clock clock;
    Pinger temp_log{};
    try
    {
        if (argc != 2)
        {
        std::cerr << "Usage: <port>\n";
        return 1;
        }

        boost::asio::io_context io_context;
        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve("", argv[1]);
        sb::Client c(io_context, endpoints);

        std::thread t([&io_context](){ io_context.run(); });

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if(event.type == sf::Event::Closed)
                    window.close();
            }

            // Each 200 ms, a new random value is add to the random curve
            if(clock.getElapsedTime().asMilliseconds() > 1000)
            {
                clock.restart();
                temp_log.update(c.data());
            }

            window.clear();

            window.draw(temp_log);

            window.display();
        }

        c.close();
        t.join();

    }catch (std::exception& e){
        std::cerr << "Exception: " << e.what() << "\n";
    }
    

    return 0;
}
