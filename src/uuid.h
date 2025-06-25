#ifndef UUID_HPP
#define UUID_HPP

#include <random>
#include <sstream>
#include <iomanip>
#include <string>

class UUID {
public:
    static std::string generate() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<uint32_t> dist(0, 0xffffffff);

        uint32_t data[4] = { dist(gen), dist(gen), dist(gen), dist(gen) };

        std::stringstream ss;
        ss << std::hex << std::setfill('0');

        ss << std::setw(8) << (data[0]) << "-";
        ss << std::setw(4) << ((data[1] >> 16) & 0xffff) << "-";
        ss << std::setw(4) << (((data[1] >> 0) & 0x0fff) | 0x4000) << "-";
        ss << std::setw(4) << (((data[2] >> 16) & 0x3fff) | 0x8000) << "-";
        ss << std::setw(4) << ((data[2] >> 0) & 0xffff);
        ss << std::setw(8) << (data[3]);

        return ss.str();
    }
};

#endif // UUID_HPP