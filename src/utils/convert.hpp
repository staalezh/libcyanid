#ifndef _cyanid_utils_convert_hpp_
#define _cyanid_utils_convert_hpp_

#include "../packet.hpp"
#include "../types.hpp"
#include <libnet.h>
#include <string>

namespace cyanid {
namespace utils {

basic_mac_addr* mac_to_addr(const std::string& addr);
ip_addr ip_to_addr4(const std::string& addr, context* con);
ip_addr name_to_addr4(const std::string& addr, context* con);

std::string addr4_to_name(ip_addr);
std::string addr4_to_ip(ip_addr);
std::string addr_to_mac(basic_mac_addr*);

}
}

#endif
