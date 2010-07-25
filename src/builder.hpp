#ifndef _cyanid_builder_hpp
#define _cyanid_builder_hpp

#include "context.hpp"

namespace cyanid {

class builder {
public:
    builder(context* c) : con(c) { };
    virtual ~builder() { };

protected:
    context* get_context() { return con; }

private:
    context* con;
};

}

#endif
