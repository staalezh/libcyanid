#include "ethernet.hpp"
#include "utils/convert.hpp"
#include <libnet.h>
#include <string>

namespace cyanid {

ethernet::ethernet(context* con) 
    : builder(con)
{
}

void ethernet::operator()(const std::string& tha, int type)
{
    mac_addr target = utils::mac_to_addr(tha);

    eth_header = libnet_autobuild_ethernet(
            target,
            type,
            get_context());
}

}
