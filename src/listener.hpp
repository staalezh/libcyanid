#ifndef _cyanid_listener_hpp_
#define _cyanid_listener_hpp_

#include "device.hpp"
#include "raw_packet.hpp"
#include <list>

namespace cyanid {

class listener {
public:
    listener(const device&);
    ~listener();

    void run();
    void apply_filter(const std::string&);

protected:
    virtual void handle_packet(const raw_packet&) = 0;
    const device& get_device() const;

private:
    const device& dev;
    pcap_t* handle;
};

}

#endif
