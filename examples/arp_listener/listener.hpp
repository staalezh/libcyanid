#ifndef _listener_hpp_
#define _listener_hpp_

#include <cyanid.hpp>

class Listener : public cyanid::listener {
public:
    Listener(cyanid::device&);
    void handle_packet(const cyanid::raw_packet&);
};

#endif
