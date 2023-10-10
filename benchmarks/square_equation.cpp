#include "runtime/runtime.h"
#include "runtime/vm.h"
#include "file/bytecode.h"
#include "stdlib/math.h"
#include "stdlib/io.h"

class SquareEquation {
public:
    static mipt_vm::Bytecode GenerateBytecode()
    {
        using namespace mipt_vm;

        Bytecode bc;
        auto &insts = bc.GetInstructions();
        static constexpr size_t insts_cnt = 34;
        insts.reserve(insts_cnt);
        {
            const char *input_coeffs = "Input coeffs: a, b, c";
            insts.emplace_back(Instruction::Type::LDASTR,
                               Instruction::Immediate {reinterpret_cast<uint64_t>(input_coeffs)});
            insts.emplace_back(Instruction::Type::STAOBJ, 0);
            insts.emplace_back(
                Proto::Create(Proto::Type::HANDLE_VOID_OBJ, reinterpret_cast<void *>(stdlib::IO::printlnString), 0));
        }
        {
            insts.emplace_back(
                Proto::Create(Proto::Type::HANDLE_F64_VOID, reinterpret_cast<void *>(stdlib::IO::inputF64)));
            insts.emplace_back(Instruction::Type::FSTA, 0);
            insts.emplace_back(
                Proto::Create(Proto::Type::HANDLE_F64_VOID, reinterpret_cast<void *>(stdlib::IO::inputF64)));
            insts.emplace_back(Instruction::Type::FSTA, 1);
            insts.emplace_back(
                Proto::Create(Proto::Type::HANDLE_F64_VOID, reinterpret_cast<void *>(stdlib::IO::inputF64)));
            insts.emplace_back(Instruction::Type::FSTA, 2);
        }
        {
            insts.emplace_back(Instruction::Type::FLDA, 0);
            insts.emplace_back(Instruction::Type::FMUL, 2);
            insts.emplace_back(Instruction::Type::FMULI, Instruction::Immediate {.as_double = 4});
            insts.emplace_back(Instruction::Type::FSTA, 3);
            insts.emplace_back(
                Proto::Create(Proto::Type::HANDLE_F64_F64, reinterpret_cast<void *>(stdlib::Math::sqrt)));
            insts.emplace_back(Instruction::Type::FSTA, 3);
        }
        {
            insts.emplace_back(Instruction::Type::FLDAI, Instruction::Immediate {.as_double = 0});
            insts.emplace_back(Instruction::Type::FSUB, 1);
            insts.emplace_back(Instruction::Type::FSTA, 4);
        }
        {
            insts.emplace_back(Instruction::Type::FLDA, 0);
            insts.emplace_back(Instruction::Type::FMULI, Instruction::Immediate {.as_double = 2});
            insts.emplace_back(Instruction::Type::FSTA, 5);
        }
        {
            insts.emplace_back(Instruction::Type::FLDA, 4);
            insts.emplace_back(Instruction::Type::FADD, 3);
            insts.emplace_back(Instruction::Type::FDIV, 5);
            insts.emplace_back(Instruction::Type::FSTA, 6);
        }
        {
            insts.emplace_back(Instruction::Type::FLDA, 4);
            insts.emplace_back(Instruction::Type::FSUB, 3);
            insts.emplace_back(Instruction::Type::FDIV, 5);
            insts.emplace_back(Instruction::Type::FSTA, 7);
        }
        {
            const char *equation_roots = "Roots of the equation:";
            insts.emplace_back(Instruction::Type::LDASTR,
                               Instruction::Immediate {reinterpret_cast<uint64_t>(equation_roots)});
            insts.emplace_back(Instruction::Type::STAOBJ, 3);
            insts.emplace_back(
                Proto::Create(Proto::Type::HANDLE_VOID_OBJ, reinterpret_cast<void *>(stdlib::IO::printlnString), 3));
        }
        {
            insts.emplace_back(
                Proto::Create(Proto::Type::HANDLE_VOID_F64, reinterpret_cast<void *>(stdlib::IO::printlnF64), 6));
            insts.emplace_back(
                Proto::Create(Proto::Type::HANDLE_VOID_F64, reinterpret_cast<void *>(stdlib::IO::printlnF64), 7));
        }
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
