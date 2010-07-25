#ifndef _cyanid_utils_smart_ptr_hpp_
#define _cyanid_utils_smart_ptr_hpp_

namespace cyanid {
namespace utils {

template<class T>
class smart_ptr {
public:
    smart_ptr(T* ptr) : ptr(ptr) { }
    ~smart_ptr() { free(ptr); }

    operator T*() { return ptr; }
    T& operator->() { return *ptr; }

private:
    T* ptr;
};

} // namespace utils
} // namespace cyanid

#endif
