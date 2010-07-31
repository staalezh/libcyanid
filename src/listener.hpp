#ifndef _cyanid_listener_hpp_
#define _cyanid_listener_hpp_

#include "device.hpp"
#include "raw_packet.hpp"
#include <list>

namespace cyanid {

class listener {
public:
    listener(device&);
    ~listener();
    void run();
    void apply_filter(const std::string&);
    virtual void handle_packet(const raw_packet&) = 0;

private:
    static void on_packet(raw_packet::data*, 
            const raw_packet::header*,
            const raw_packet::data*);

    device& dev;
    pcap_t* handle;
};

}

#endif
