#include "ethernet.hpp"
#include "../raw_packet.hpp"
#include "../utils/convert.hpp"
#include "../types.hpp"

#include <libnet.h>

#include <arpa/inet.h>

#include <string>
#include <sstream>
#include <stdexcept>

namespace cyanid {
namespace builder {

ethernet::ethernet(context* con) : builder(con), data(0)
{
}

ethernet::ethernet(const raw_packet::data* packet, size_t data_size) : 
    builder(0)
{
    if(data_size < header_size) {
        std::stringstream error;
        error << "Unable to create ethernet header: Data size too small";
        throw std::runtime_error(error.str());
    }

    const header* eth_header = reinterpret_cast<const header*>(packet);
    src_mac  = utils::mac_to_str((basic_mac_addr*) eth_header->source_mac);
    dst_mac  = utils::mac_to_str((basic_mac_addr*) eth_header->target_mac);
    eth_type = ntohs(eth_header->ether_type);
    data     = packet + header_size;
}

void ethernet::operator()(const std::string& tha, int type)
{
    src_mac  = "<source-mac>";
    dst_mac  = tha;
    eth_type = type;

    mac_addr target = utils::mac_to_addr(tha);

    libnet_autobuild_ethernet(
            target,
            type,
            get_context());
}

const std::string& ethernet::source_mac() const
{
    return src_mac;
}

const std::string& ethernet::target_mac() const
{
    return dst_mac;
}

uint16_t ethernet::ether_type() const
{
    return eth_type;
}

const raw_packet::data* ethernet::payload() const
{
    return data;
}

} // namespace builder
} // namespace cyanid
