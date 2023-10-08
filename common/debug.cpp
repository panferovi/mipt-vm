#include <cerrno>
#include <cstring>
#include <iostream>

#include "common/debug.h"

namespace mipt_vm {

[[noreturn]] void AssertionFail(const char* expr, const char* file, unsigned line, const char* function)
{
    int errnum = errno;
    std::cerr << "ASSERTION FAILED: " << expr << std::endl;
    std::cerr << "IN " << file << ":" << std::dec << line << ": " << function << std::endl;
    if (errnum != 0) {
        std::cerr << "ERRNO: " << errnum << " (" << std::strerror(errnum) << ")" << std::endl;
    }
    std::abort();
}

}  // namespace mipt_vm
