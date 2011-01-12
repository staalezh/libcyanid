#include "listener.hpp"

#include <cyanid.hpp>

#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Usage: arp_listener [IFACE]" << endl;
        return 1;
    }

    const std::string iface = argv[1];

    cyanid::device device(iface);
    Listener listener(device);
    listener.run();

    return 0;
}
