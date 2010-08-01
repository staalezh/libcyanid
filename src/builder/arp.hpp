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
    arp(const raw_packet::data*);

    void operator()(type, const std::string&, const std::string&, 
        const std::string&, const std::string&);

    const std::string& sha() const;
    const std::string& spa() const;
    const std::string& tha() const;
    const std::string& tpa() const;

    const raw_packet::data* payload() const;

private:
    struct arp_header {
        uint16_t hw_type;
        uint16_t pr_type;
        uint8_t  hw_addr_len;
        uint8_t  pr_addr_len;
        uint16_t opcode;
        unsigned char sha[6];
        uint32_t spa;
        unsigned char tha[6];
        uint32_t tpa;
    };

    std::string source_ha;
    std::string source_pa;
    std::string target_ha;
    std::string target_pa;
    type req_type;
};

} // namespace builder
} // namespace cyanid

#endif
