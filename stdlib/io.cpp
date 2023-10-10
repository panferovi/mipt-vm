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
    printString(str);
    std::cout << std::endl;
}

/* static */
void IO::printI64(int64_t val)
{
    std::cout << val;
}

/* static */
void IO::printlnI64(int64_t val)
{
    printI64(val);
    std::cout << std::endl;
}

/* static */
void IO::printF64(double val)
{
    std::cout << val;
}

/* static */
void IO::printlnF64(double val)
{
    printF64(val);
    std::cout << std::endl;
}

/* static */
int64_t IO::inputI64()
{
    int64_t val;
    std::cin >> val;
    return val;
}

/* static */
double IO::inputF64()
{
    double val;
    std::cin >> val;
    return val;
}

}  // namespace mipt_vm::stdlib
