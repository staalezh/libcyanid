#include "arp.hpp"
#include "builder.hpp"
#include "../context.hpp"
#include "../utils/convert.hpp"
#include "../utils/smart_ptr.hpp"

#include <memory>

namespace cyanid {
namespace builder {

const int arp::ETHER_TYPE;

arp::arp(context* con) : builder(con)
{
}

arp::arp(const raw_packet::data* data) : builder(0)
{
    const arp_header* header = reinterpret_cast<const arp_header*>(data);

    source_ha = utils::addr_to_mac(header->sha);
    source_pa = utils::addr4_to_ip(header->spa);
    target_ha = utils::addr_to_mac(header->tha);
    target_pa = utils::addr4_to_ip(header->tpa);
    req_type  = static_cast<type>(header->opcode);
}

void arp::operator()(type t, const std::string& sha, const std::string& spa, 
        const std::string& tha, const std::string& tpa)
{
    source_ha = sha;
    source_pa = spa;
    target_ha = tha;
    target_pa = tpa;
    req_type  = t;

    ip_addr source_ip = utils::ip_to_addr4(spa, get_context());
    ip_addr target_ip = utils::ip_to_addr4(tpa, get_context());

    mac_addr source_mac = utils::mac_to_addr(sha);
    mac_addr target_mac = utils::mac_to_addr(tha);

    libnet_autobuild_arp(
            t,
            source_mac,
            reinterpret_cast<u_int8_t*>(&source_ip),
            target_mac,
            reinterpret_cast<u_int8_t*>(&target_ip),
            get_context());
}

const std::string& arp::sha() const
{
    return source_ha;
}

const std::string& arp::spa() const
{
    return source_pa;
}

const std::string& arp::tha() const
{
    return target_ha;
}

const std::string& arp::tpa() const
{
    return target_pa;
}

const raw_packet::data* arp::payload() const
{
    return 0;
}

}
}
