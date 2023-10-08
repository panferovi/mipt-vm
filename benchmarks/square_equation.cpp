#include "runtime/runtime.h"

class SquareEquation {
public:
    static mipt_vm::Bytecode GenerateBytecode()
    {
        mipt_vm::Bytecode bc;
        return bc;
    }
};

int main()
{
    mipt_vm::Runtime::Create();

    auto *runtime = mipt_vm::Runtime::GetInstance();
    auto bytecode = SquareEquation::GenerateBytecode();
    runtime->GetVM()->GetInterpreter().Interpret(bytecode);

    mipt_vm::Runtime::Destroy();

    return 0;
}
