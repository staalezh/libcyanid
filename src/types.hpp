#ifndef _cyanid_types_hpp_
#define _cyanid_types_hpp_

#include <libnet.h>

#include "utils/smart_ptr.hpp"

namespace cyanid {

typedef u_int8_t basic_mac_addr;
typedef utils::smart_ptr<basic_mac_addr> mac_addr;
typedef u_int32_t ip_addr;

}

#endif
