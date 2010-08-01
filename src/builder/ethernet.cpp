#include "ethernet.hpp"
#include "../raw_packet.hpp"
#include "../utils/convert.hpp"
#include "../types.hpp"
#include <libnet.h>
#include <string>

namespace cyanid {
namespace builder {

ethernet::ethernet(context* con) : builder(con), data(0)
{
}

ethernet::ethernet(const raw_packet::data* data) : builder(0)
{
    const ethernet_header* header = reinterpret_cast<const ethernet_header*>(data);
    src_mac  = utils::addr_to_mac((basic_mac_addr*) header->source_mac);
    dst_mac  = utils::addr_to_mac((basic_mac_addr*) header->target_mac);
    eth_type = header->ether_type;
    data     = header->data;
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
