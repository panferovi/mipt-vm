#ifndef COMMON_DEBUG_H_
#define COMMON_DEBUG_H_

namespace mipt_vm {

[[noreturn]] void AssertionFail(const char* expr, const char* file, unsigned line, const char* function);

}  // namespace mipt_vm

#endif  // COMMON_DEBUG_H_
