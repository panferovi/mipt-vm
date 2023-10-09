#ifndef RUNTIME_INTERPRETER_H_
#define RUNTIME_INTERPRETER_H_

#include "common/macros.h"
#include "runtime/register_manager.h"

namespace mipt_vm {

class Bytecode;

class Interpreter {
public:
    Interpreter() = default;
    NO_COPY_SEMANTIC(Interpreter);
    NO_MOVE_SEMANTIC(Interpreter);

    void Interpret(Bytecode &bytecode);

private:
    RegisterManager reg_manager_;
};

}  // namespace mipt_vm

#endif  // RUNTIME_INTERPRETER_H_
