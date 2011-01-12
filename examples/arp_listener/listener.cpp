#include <iostream>

#include "listener.hpp"
#include <cyanid.hpp>

using namespace std;

Listener::Listener(cyanid::device& device) : listener(device)
{
    apply_filter("arp");
}

void Listener::handle_packet(const cyanid::raw_packet& packet)
{
    size_t packet_size = packet.packet_header()->len;
    cyanid::builder::ethernet eth(packet.payload(), packet_size);

    size_t arp_size = packet_size - cyanid::builder::ethernet::header_size;
    cyanid::builder::arp arp(eth.payload(), arp_size);

    std::string type = arp.oper() == cyanid::builder::arp::REQUEST ? 
        "REQUEST" : "REPLY";

    cout << "Captured ARP packet: " << endl
         << "============================================" << endl
         << "ARP type: " << type << endl
         << "Source hardware address: " << arp.sha() << endl
         << "Target hardware address: " << arp.tha() << endl
         << "Source protocol address: " << arp.spa() << endl
         << "Target protocol address: " << arp.tpa() << endl
         << endl;
}
