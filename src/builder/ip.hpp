#ifndef _cyanid_builder_ip_hpp_
#define _cyanid_builder_ip_hpp_

#include "builder.hpp"
#include "../packet.hpp"
#include "../raw_packet.hpp"
#include <libnet.h>
#include <string>

namespace cyanid {
namespace builder {

class ip : public builder {
public:
    ip(context*);
    ip(const raw_packet::data*, size_t);

    struct header {
        uint8_t version : 4;
        uint8_t ihl : 4;
        uint8_t tos;
        uint16_t len;
        uint16_t id;
        uint16_t flags : 3;
        uint16_t offset : 13;
        uint8_t ttl;
        uint8_t proto;
        uint16_t checksum;
        uint32_t src_ip;
        uint32_t dst_ip;
        // TODO: options and shit
    };

    int version()  const { return hdr.version;  }
    int ihl()      const { return hdr.ihl;      }
    int tos()      const { return hdr.tos;      }
    int len()      const { return hdr.len;      }
    int id()       const { return hdr.id;       }
    int flags()    const { return hdr.flags;    }
    int offset()   const { return hdr.offset;   }
    int ttl()      const { return hdr.ttl;      }
    int proto()    const { return hdr.proto;    }
    int checksum() const { return hdr.checksum; }

    ip_addr src_ip() const { return hdr.src_ip; }
    ip_addr dst_ip() const { return hdr.dst_ip; }

    static const size_t header_size = sizeof(header);

private:
    header hdr;
    const raw_packet::data* data;
};

} // namespace builder
} // namespace cyanid

#endif // _cyanid_builder_ip_hpp_
