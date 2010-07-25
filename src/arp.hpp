#ifndef _cyanid_arp_hpp_
#define _cyanid_arp_hpp_

#include "context.hpp"
#include "builder.hpp"
#include "utils/convert.hpp"

namespace cyanid {

class arp : public builder {
public:
    static const int ETHER_TYPE = 0x0806;

    enum type { REQUEST = 1, REPLY = 2 };

    arp(context*);

    void operator()(type, const std::string&, const std::string&, 
        const std::string&, const std::string&);

private:
    packet::header arp_header;
    context* con;
};

}

#endif
