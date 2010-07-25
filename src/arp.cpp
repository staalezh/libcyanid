#include "arp.hpp"
#include "builder.hpp"
#include "context.hpp"
#include "utils/convert.hpp"
#include "utils/smart_ptr.hpp"

#include <memory>

namespace cyanid {

const int arp::ETHER_TYPE;

arp::arp(context* con) 
    : builder(con)
{
}

void arp::operator()(type t, const std::string& sha, const std::string& spa, 
        const std::string& tha, const std::string& tpa)
{
    ip_addr source_ip = utils::ip_to_addr4(spa, get_context());
    ip_addr target_ip = utils::ip_to_addr4(tpa, get_context());

    mac_addr source_mac = utils::mac_to_addr(sha);
    mac_addr target_mac = utils::mac_to_addr(tha);

    arp_header = libnet_autobuild_arp(
            t,
            source_mac,
            reinterpret_cast<u_int8_t*>(&source_ip),
            target_mac,
            reinterpret_cast<u_int8_t*>(&target_ip),
            get_context());
}

}
