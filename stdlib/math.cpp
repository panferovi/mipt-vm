#include <cmath>

#include "stdlib/math.h"

namespace mipt_vm::stdlib {

int Math::sqrt(int64_t val)
{
    return std::sqrt(val);
}

int Math::sin(int64_t val)
{
    return std::sin(val);
}

int Math::cos(int64_t val)
{
    return std::cos(val);
}

}  // namespace mipt_vm::stdlib
