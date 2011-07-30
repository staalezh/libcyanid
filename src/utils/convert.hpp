#ifndef _cyanid_utils_convert_hpp_
#define _cyanid_utils_convert_hpp_

#include "../packet.hpp"
#include "../types.hpp"
#include <libnet.h>
#include <string>

namespace cyanid {
namespace utils {

basic_mac_addr* mac_to_addr(const std::string& addr);
ip_addr str_to_addr4(const std::string& addr, context* con);
ip_addr hostname_to_addr4(const std::string& addr, context* con);

std::string addr4_to_hostname(const ip_addr);
std::string addr4_to_str(const uint8_t*);
std::string addr4_to_str(const ip_addr);
std::string mac_to_str(const basic_mac_addr*);

} // namespace utils
} // namespace cyanid

#endif
