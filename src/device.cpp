#include "device.hpp"
#include "raw_packet.hpp"

#include <libnet.h>

#include <sstream>
#include <stdexcept>

namespace cyanid {

device::device(const std::string& name) : name(name)
{
    char errbuf[LIBNET_ERRBUF_SIZE];

    con = libnet_init(
            LIBNET_LINK_ADV,
            const_cast<char*>(name.c_str()),
            errbuf);

    if(con == 0) {
        std::stringstream error;
        error << "Unable to initialize libnet: " << errbuf << std::endl;
        throw std::runtime_error(error.str());
    }
}

device::~device()
{
    libnet_destroy(con);
}

const std::string& device::get_name() const
{
    return name;
}

const basic_mac_addr* device::get_mac() const
{
    const basic_mac_addr* res =
        reinterpret_cast<const basic_mac_addr*>(libnet_get_hwaddr(con));

    if (res == 0) {
        std::stringstream error;
        error << "While getting hardware address: "
            << libnet_geterror(con) << std::endl;
        throw std::runtime_error(error.str());
    }

    return res;
}

ip_addr device::get_ip() const
{
    return libnet_get_ipaddr4(con);
}

context* device::get_context() const
{
    return con;
}

size_t device::dispatch_raw(const raw_packet& packet) const
{
    size_t pkt_size = packet.packet_header()->len;

    u_int8_t data[pkt_size];
    memcpy(data, packet.payload(), pkt_size);
    size_t ret = libnet_adv_write_link(con, data, pkt_size);

    libnet_clear_packet(con);

    return ret;
}

} // namespace cyanid
