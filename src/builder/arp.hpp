#ifndef _cyanid_builder_arp_hpp_
#define _cyanid_builder_arp_hpp_

#include "builder.hpp"
#include "../raw_packet.hpp"
#include "../context.hpp"
#include "../utils/convert.hpp"

namespace cyanid {
namespace builder {

class arp : public builder {
public:
    static const int ETHER_TYPE = 0x0806;

    enum type { REQUEST = 1, REPLY = 2 };

    arp(context*);
    arp(const raw_packet::data*, size_t);

    void operator()(type, const std::string&, const std::string&, 
        const std::string&, const std::string&);

    uint16_t htype() const { return hw_type; }
    uint16_t ptype() const { return pr_type; }
    uint8_t hlen() const { return hw_len; }
    uint8_t plen() const { return pr_len; }

    const std::string& sha() const { return source_ha; }
    const std::string& spa() const { return source_pa; }
    const std::string& tha() const { return target_ha; }
    const std::string& tpa() const { return target_pa; }

    type oper() const { return req_type; }

    struct header {
        uint16_t hw_type;
        uint16_t pr_type;
        uint8_t  hw_addr_len;
        uint8_t  pr_addr_len;
        uint16_t opcode;
        uint8_t sha[6];
        uint8_t spa[4];
        uint8_t tha[6];
        uint8_t tpa[4];
    };

    static const size_t header_size = sizeof(header);

private:
    uint16_t hw_type;
    uint16_t pr_type;
    uint8_t  hw_len;
    uint8_t  pr_len;

    type req_type;

    std::string source_ha;
    std::string source_pa;
    std::string target_ha;
    std::string target_pa;

};

} // namespace builder
} // namespace cyanid

#endif
