#include "listener.hpp"
#include "raw_packet.hpp"
#include <sstream>
#include <stdexcept>
#include <functional>

namespace cyanid {

listener::listener(device& dev) :
    dev(dev),
    handle(0)
{
    char errbuf[PCAP_ERRBUF_SIZE];
    handle = pcap_open_live(dev.get_name().c_str(), 1, true, -1, errbuf);

    if(handle == 0) {
        std::stringstream error;
        error << "Unable to open device for sniffing: " << errbuf;
        throw std::runtime_error(error.str());
    }
}

void listener::run()
{
    while(true) {
        raw_packet::header header;
        const raw_packet::data* data = pcap_next(handle, &header);
        handle_packet(raw_packet(&header, data));
    }
}

} // namespace cyanid
