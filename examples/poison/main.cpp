#include <cyanid.hpp>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    const std::string iface = "wlan0";

    cyanid::device device(iface);
    cyanid::basic_mac_addr* source_mac = device.get_mac();
    cyanid::ip_addr source_ip = device.get_ip();

    cout << "Using interface: " << iface << endl
         << "MAC addr:        " << cyanid::utils::addr_to_mac(source_mac) << endl
         << "IP addr:         " << cyanid::utils::addr4_to_ip(source_ip) << endl;

    cyanid::packet packet(device);

    packet.build<cyanid::arp>()(
            cyanid::arp::REPLY,
            "aa:bb:cc:dd:ee:ff",
            "192.168.1.4",
            "00:00:00:00:00:00",
            "192.168.1.1");

    packet.build<cyanid::ethernet>()(
            "00:00:00:00:00:00",
            cyanid::arp::ETHER_TYPE);

    size_t bytes_written = packet.dispatch();
    cout << "Wrote " << bytes_written << " bytes to the network" << endl;

    return 0;
}
