#ifndef STDLIB_IO_H_
#define STDLIB_IO_H_

#include <cstdint>

namespace mipt_vm::stdlib {

class IO {
public:
    static void printString(const char *str);

    static void printlnString(const char *str);

    static void printI64(int64_t val);

    static void printlnI64(int64_t val);

    static void printF64(double val);

    static void printlnF64(double val);

    static int64_t inputI64();

    static double inputF64();
};

}  // namespace mipt_vm::stdlib

#endif  // STDLIB_IO_H_
