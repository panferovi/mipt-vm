#ifndef STDLIB_MATH_H_
#define STDLIB_MATH_H_

#include <cstdint>

namespace mipt_vm::stdlib {

class Math {
public:
    static int sqrt(int64_t val);

    static int sin(int64_t val);

    static int cos(int64_t val);
};

}  // namespace mipt_vm::stdlib

#endif  // STDLIB_MATH_H_
