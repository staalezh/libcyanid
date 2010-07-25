#include "convert.hpp"
#include <string>
#include <sstream>
#include <iomanip>

namespace cyanid {
namespace utils {

basic_mac_addr* mac_to_addr(const std::string& addr)
{
    int addr_size;
    basic_mac_addr* ret = libnet_hex_aton(const_cast<char*>(addr.c_str()), &addr_size);
    return ret;
}

ip_addr ip_to_addr4(const std::string& addr, context* con)
{
    static u_int8_t mode = LIBNET_DONT_RESOLVE;
    return libnet_name2addr4(con, const_cast<char*>(addr.c_str()), mode);
}

ip_addr name_to_addr4(const std::string& addr, context* con)
{
    static u_int8_t mode = LIBNET_RESOLVE;
    return libnet_name2addr4(con, const_cast<char*>(addr.c_str()), mode);
}

std::string addr4_to_name(ip_addr addr)
{
    return libnet_addr2name4(addr, LIBNET_RESOLVE);
}

std::string addr4_to_ip(ip_addr addr)
{
    return libnet_addr2name4(addr, LIBNET_DONT_RESOLVE);
}

std::string addr_to_mac(basic_mac_addr* addr)
{
    static const int mac_size = 6;

    std::stringstream result;
    result.fill('0');
    result.width(2);

    for(int i = 0; i < mac_size; ++i) {
        result << std::hex << static_cast<int>(addr[i]);
        if(i != mac_size - 1) {
            result << ":";
        }
    }

    return result.str();
}

} // namespace utils
} // namespace cyanid
