#ifndef RUNTIME_VM_H_
#define RUNTIME_VM_H_

#include "runtime/interpreter.h"
#include "common/macros.h"

namespace mipt_vm {

class VM {
public:
    VM() = default;
    NO_COPY_SEMANTIC(VM);
    NO_MOVE_SEMANTIC(VM);

    Interpreter &GetInterpreter();

private:
    Interpreter interpreter_;
};

}  // namespace mipt_vm

#endif  // RUNTIME_VM_H_
