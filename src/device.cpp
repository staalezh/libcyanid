#include "device.hpp"
#include <libnet.h>
#include <sstream>
#include <stdexcept>

namespace cyanid {

device::device(const std::string& name) : name(name)
{
    char errbuf[LIBNET_ERRBUF_SIZE];
    con = libnet_init(LIBNET_LINK, const_cast<char*>(name.c_str()), errbuf);

    if(con == 0) {
        std::stringstream error;
        error << "Unable to initialize libnet: " << errbuf << std::endl;
        throw std::runtime_error(error.str());
    }
}

const std::string& device::get_name()
{
    return name;
}

basic_mac_addr* device::get_mac()
{
    return reinterpret_cast<basic_mac_addr*>(libnet_get_hwaddr(con));
}

ip_addr device::get_ip()
{
    return libnet_get_ipaddr4(con);
}

context* device::get_context()
{
    return con;
}


}
