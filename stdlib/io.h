#ifndef STDLIB_IO_H_
#define STDLIB_IO_H_

#include <cstdint>

namespace mipt_vm::stdlib {

class IO {
public:
    static void printString(const char *str);

    static void printI64(int64_t val);
};

}  // namespace mipt_vm::stdlib

#endif  // STDLIB_IO_H_
