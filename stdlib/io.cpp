#include <iostream>

#include "stdlib/io.h"

namespace mipt_vm::stdlib {

/* static */
void IO::printString(const char *str)
{
    std::cout << str;
}

/* static */
void IO::printI64(int64_t val)
{
    std::cout << val;
}

}  // namespace mipt_vm::stdlib
