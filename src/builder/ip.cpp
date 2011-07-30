#include "ip.hpp"

#include <sstream>
#include <stdexcept>

namespace cyanid {
namespace builder {

ip::ip(context* con) : builder(con), data(0)
{
}

ip::ip(const raw_packet::data* packet, size_t data_size) : builder(0)
{
    if (data_size < header_size) {
        std::stringstream error;
        error << "Unable to create IP header: Data size too small";
        throw std::runtime_error(error.str());
    }

    const header* ip_hdr = reinterpret_cast<const header*>(packet);
    hdr = *ip_hdr;
}

} // namespace builder
} // namespace cyanid
