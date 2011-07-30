#include "listener.hpp"
#include "raw_packet.hpp"
#include <sstream>
#include <stdexcept>
#include <functional>

namespace cyanid {

listener::listener(const device& dev) :
    dev(dev),
    handle(0)
{
    char errbuf[PCAP_ERRBUF_SIZE];
    handle = pcap_open_live(dev.get_name().c_str(), BUFSIZ, true, -1, errbuf);

    if(handle == 0) {
        std::stringstream error;
        error << "Unable to open device for sniffing: " << errbuf;
        throw std::runtime_error(error.str());
    }
}

listener::~listener()
{
    pcap_close(handle);
}

void listener::run()
{
    raw_packet::header header;

    while(true) {
        const raw_packet::data* data = pcap_next(handle, &header);
        if(data != 0) {
            handle_packet(raw_packet(&header, data));
        }
    }
}

void listener::apply_filter(const std::string& filter)
{
    char errbuf[PCAP_ERRBUF_SIZE];

    bpf_u_int32 ip;
    bpf_u_int32 mask;

    if(pcap_lookupnet(dev.get_name().c_str(), &ip, &mask, errbuf)) {
        std::stringstream error;
        error << "While getting netmask and ip for device: " << errbuf 
              << std::endl;
        throw std::runtime_error(error.str());
    }

    bpf_program fp;
    if(pcap_compile(handle, &fp, const_cast<char*>(filter.c_str()), 0, mask)) {
        std::stringstream error;
        error << "While parsing filter \"" << filter << "\": " 
              << pcap_geterr(handle);
        throw std::runtime_error(error.str());
    }

    if(pcap_setfilter(handle, &fp)) {
        std::stringstream error;
        error << "While setting filter \"" << filter << "\": " 
              << pcap_geterr(handle);
        throw std::runtime_error(error.str());
    }
}

const device& listener::get_device() const
{
    return dev;
}

} // namespace cyanid
