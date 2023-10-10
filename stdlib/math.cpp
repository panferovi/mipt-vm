#include <cmath>

#include "stdlib/math.h"

namespace mipt_vm::stdlib {

double Math::sqrt(double val)
{
    return std::sqrt(val);
}

double Math::sin(double val)
{
    return std::sin(val);
}

double Math::cos(double val)
{
    return std::cos(val);
}

}  // namespace mipt_vm::stdlib
