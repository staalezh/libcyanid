#ifndef _cyanid_packet_hpp_
#define _cyanid_packet_hpp_

#include "device.hpp"
#include "context.hpp"
#include "builder/builder.hpp"
#include "device.hpp"
#include <libnet.h>
#include <string>

namespace cyanid {

class packet {
public:
    typedef libnet_ptag_t header;

    packet(const device&);
    packet(const std::string&);
    ~packet();

    template<class Builder>
    Builder& build()
    {
        delete packet_builder;
        packet_builder = new Builder(con);
        return *dynamic_cast<Builder*>(packet_builder);
    }

    size_t dispatch();

protected:
    context* get_context();
    const std::string get_error() const;

private:
    const device& dev;
    builder::builder* packet_builder;
    context* con;
};

}

#endif
