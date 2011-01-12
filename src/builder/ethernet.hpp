#ifndef _cyanid_builder_ethernet_hpp_
#define _cyanid_builder_ethernet_hpp_

#include "builder.hpp"
#include "../packet.hpp"
#include "../raw_packet.hpp"
#include <libnet.h>
#include <string>

namespace cyanid {
namespace builder {

class ethernet : public builder {
public:
    ethernet(context*);
    ethernet(const raw_packet::data*, size_t);

    void operator()(const std::string&, int);

    const std::string& source_mac() const;
    const std::string& target_mac() const;
    uint16_t ether_type() const;
    const raw_packet::data* payload() const;

    struct header {
        unsigned char target_mac[6];
        unsigned char source_mac[6];
        uint16_t ether_type;
    };

    static const size_t header_size = sizeof(header);

private:
    std::string src_mac;
    std::string dst_mac;
    uint16_t eth_type;
    const raw_packet::data* data;
};

} // namespace builder
} // namespace cyanid

#endif
