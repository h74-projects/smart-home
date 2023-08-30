#ifndef SMART_HOME_HPP
#define SMART_HOME_HPP

#include <string>
#include <unordered_map>

namespace sb {

class SmartBuilding {
public:
    SmartBuilding() = default;
    ~SmartBuilding() = default;

    void run();
    void configure(std::string a_path);
private:
    void load_types(std::string a_path);
private:
    std::unordered_map<std::string, std::string> m_libraries;
};

} //namespace sb

#endif // SMART_HOME_HPP
