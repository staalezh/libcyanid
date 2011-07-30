#include "packet.hpp"
#include "device.hpp"
#include <libnet.h>

#include <stdexcept>
#include <sstream>

namespace cyanid {

packet::packet(const device& dev) : 
    dev(dev), 
    packet_builder(0),
    con(dev.get_context())
{
}

packet::packet(const std::string& dev_name) :
    dev(dev_name),
    packet_builder(0),
    con(dev.get_context())
{
}

packet::~packet()
{
    delete packet_builder;
}

context* packet::get_context()
{
    return con;
}

size_t packet::dispatch()
{
    int bytes_written = libnet_write(con);

    libnet_clear_packet(con);

    if(bytes_written == -1) {
        std::stringstream error;
        error << "Error while sending packet: " << libnet_geterror(con) 
              << std::endl;
        throw std::runtime_error(error.str());
    }

    return bytes_written;
}

const std::string packet::get_error() const
{
    return libnet_geterror(con);
}

}
