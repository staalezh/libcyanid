#include "arp.hpp"
#include "builder.hpp"
#include "../context.hpp"
#include "../utils/convert.hpp"
#include "../utils/smart_ptr.hpp"

#include <arpa/inet.h>

#include <memory>
#include <sstream>
#include <stdexcept>

namespace cyanid {
namespace builder {

arp::arp(context* con) : builder(con)
{
}

arp::arp(const raw_packet::data* data, size_t data_size) : builder(0)
{
    if(data_size < header_size) {
        std::stringstream error;
        error << "Unable to create arp header: "
              << "Data size too small" << std::endl;

        throw std::runtime_error(error.str());
    }

    const header* arp_hdr = reinterpret_cast<const header*>(data);

    hw_type = htons(arp_hdr->hw_type);
    pr_type = htons(arp_hdr->pr_type);
    hw_len  = arp_hdr->hw_addr_len;
    pr_len  = arp_hdr->pr_addr_len;

    req_type = static_cast<type>(ntohs(arp_hdr->opcode));

    source_ha = utils::mac_to_str(arp_hdr->sha);
    source_pa = utils::addr4_to_str(arp_hdr->spa);
    target_ha = utils::mac_to_str(arp_hdr->tha);
    target_pa = utils::addr4_to_str(arp_hdr->tpa);
}

void arp::operator()(type t, const std::string& sha, const std::string& spa, 
        const std::string& tha, const std::string& tpa)
{
    source_ha = sha;
    source_pa = spa;
    target_ha = tha;
    target_pa = tpa;
    req_type  = t;

    ip_addr source_ip = utils::str_to_addr4(spa, get_context());
    ip_addr target_ip = utils::str_to_addr4(tpa, get_context());

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

} // namespace builder
} // namespace cyanid
