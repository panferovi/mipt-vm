#include "runtime/runtime.h"
#include "runtime/vm.h"
#include "file/bytecode.h"

class SquareEquation {
public:
    static mipt_vm::Bytecode GenerateBytecode()
    {
        using namespace mipt_vm;

        Bytecode bc;
        auto &insts = bc.GetInstructions();
        insts.push_back(Instruction{});

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
