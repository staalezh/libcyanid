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
    handle = pcap_open_live(dev.get_name().c_str(), 1, false, -1, errbuf);

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
    if(pcap_loop(handle, -1, &listener::on_packet,
                reinterpret_cast<raw_packet::data*>(this)) == -1) {
        std::stringstream error;
        error << "Unable to read packets: " << pcap_geterr(handle) << std::endl;
        throw std::runtime_error(error.str());
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

void listener::on_packet(raw_packet::data* l, 
        const raw_packet::header* header, 
        const raw_packet::data* packet)
{
    listener* handler  = reinterpret_cast<listener*>(l);
    handler->handle_packet(raw_packet(header, packet));
}


} // namespace cyanid
