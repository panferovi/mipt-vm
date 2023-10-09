#include <iostream>

#include "stdlib/io.h"

namespace mipt_vm::stdlib {

/* static */
void IO::printString(const char *str)
{
    std::cout << str;
}

/* static */
void IO::printlnString(const char *str)
{
    std::cout << str;
    std::cout << std::endl;
}

/* static */
void IO::printI64(int64_t val)
{
    std::cout << val;
}

/* static */
void IO::printI64(int64_t val)
{
    std::cout << val;
    std::cout << std::endl;
}
}  // namespace mipt_vm::stdlib
