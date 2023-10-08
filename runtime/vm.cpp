#include "runtime/vm.h"

namespace mipt_vm {

Interpreter &VM::GetInterpreter()
{
    return interpreter_;
}

}  // namespace mipt_vm
