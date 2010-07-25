#ifndef _cyanid_listener_hpp_
#define _cyanid_listener_hpp_

#include "device.hpp"
#include "raw_packet.hpp"

namespace cyanid {

class listener {
public:
    listener(device&);
    void run();

protected:
    virtual void handle_packet(const raw_packet&) = 0;

private:
    device& dev;
    pcap_t* handle;
};

}

#endif
