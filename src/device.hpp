#ifndef _cyanid_device_hpp_
#define _cyanid_device_hpp_

#include "types.hpp"
#include "context.hpp"

#include <string>

namespace cyanid {

class raw_packet;

class device {
public:
    device(const std::string&);
    ~device();

    const std::string& get_name() const;
    const basic_mac_addr* get_mac() const;
    ip_addr get_ip() const;
    context* get_context() const;

    size_t dispatch_raw(const raw_packet&) const;

private:
    device(const device&);

    context* con;
    std::string name;
};

} // namespace cyanid

#endif
