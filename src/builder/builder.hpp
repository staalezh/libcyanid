#ifndef _cyanid_builder_hpp
#define _cyanid_builder_hpp

#include "../context.hpp"
#include "../raw_packet.hpp"

namespace cyanid {

namespace builder {

class builder {
public:
    builder(context* c) : con(c) { };
    virtual ~builder() { };

    virtual const raw_packet::data* payload() const = 0;

protected:
    context* get_context() { return con; }

private:
    context* con;
};

} // namespace builder
} // namespace cyanid

#endif
