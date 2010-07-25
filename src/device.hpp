#ifndef _cyanid_device_hpp_
#define _cyanid_device_hpp_

#include "types.hpp"
#include "context.hpp"
#include <string>

namespace cyanid {

class device {
public:
    device(const std::string&);

    const std::string& get_name();
    basic_mac_addr* get_mac();
    ip_addr get_ip();
    context* get_context();

private:
    context* con;
    std::string name;
};

}

#endif
