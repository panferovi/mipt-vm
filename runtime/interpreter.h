#ifndef RUNTIME_INTERPRETER_H_
#define RUNTIME_INTERPRETER_H_

#include "common/macros.h"
#include "file/bytecode.h"

namespace mipt_vm {

class Interpreter {
public:
    Interpreter() = default;
    NO_COPY_SEMANTIC(Interpreter);
    NO_MOVE_SEMANTIC(Interpreter);

    void Interpret(Bytecode &bytecode);
};

}  // namespace mipt_vm

#endif  // RUNTIME_INTERPRETER_H_
