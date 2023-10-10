#ifndef STDLIB_MATH_H_
#define STDLIB_MATH_H_

#include <cstdint>

namespace mipt_vm::stdlib {

class Math {
public:
    static double sqrt(double val);

    static double sin(double val);

    static double cos(double val);
};

}  // namespace mipt_vm::stdlib

#endif  // STDLIB_MATH_H_
