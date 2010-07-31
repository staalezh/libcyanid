#ifndef _cyanid_builder_ethernet_hpp_
#define _cyanid_builder_ethernet_hpp_

#include "builder.hpp"
#include "../packet.hpp"
#include <libnet.h>
#include <string>

namespace cyanid {
namespace builder {

class ethernet : public builder {
public:
    ethernet(context*);
    void operator()(const std::string&, int);

private:
    packet::header eth_header;
};

} // namespace builder
} // namespace cyanid

#endif
