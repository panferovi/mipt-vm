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
        auto main_body = [](StringTable &table, const BytecodeMeta &) {
            Body::Instructions instrs;

            instrs.emplace_back(Instruction::LDASTR,
                                Instruction::Immediate {.as_obj = table.RegisterString("Input coeffs: a, b, c")});
            instrs.emplace_back(Instruction::STAOBJ, 0);
            instrs.emplace_back(
                Proto::Create(Proto::HANDLE_VOID_OBJ, reinterpret_cast<void *>(stdlib::IO::printlnString), 0));

            instrs.emplace_back(Proto::Create(Proto::HANDLE_F64_VOID, reinterpret_cast<void *>(stdlib::IO::inputF64)));
            instrs.emplace_back(Instruction::FSTA, 0);
            instrs.emplace_back(Proto::Create(Proto::HANDLE_F64_VOID, reinterpret_cast<void *>(stdlib::IO::inputF64)));
            instrs.emplace_back(Instruction::FSTA, 1);
            instrs.emplace_back(Proto::Create(Proto::HANDLE_F64_VOID, reinterpret_cast<void *>(stdlib::IO::inputF64)));
            instrs.emplace_back(Instruction::FSTA, 2);

            instrs.emplace_back(Instruction::FLDA, 0);
            instrs.emplace_back(Instruction::FMUL, 2);
            instrs.emplace_back(Instruction::FMULI, Instruction::Immediate {.as_double = 4});
            instrs.emplace_back(Instruction::FSTA, 3);
            instrs.emplace_back(Instruction::FLDA, 1);
            instrs.emplace_back(Instruction::FMUL, 1);
            instrs.emplace_back(Instruction::FSUB, 3);
            instrs.emplace_back(Instruction::FSTA, 3);
            instrs.emplace_back(Proto::Create(Proto::HANDLE_F64_F64, reinterpret_cast<void *>(stdlib::Math::sqrt), 3));
            instrs.emplace_back(Instruction::FSTA, 3);

            instrs.emplace_back(Instruction::FLDAI, Instruction::Immediate {.as_double = 0});
            instrs.emplace_back(Instruction::FSUB, 1);
            instrs.emplace_back(Instruction::FSTA, 4);

            instrs.emplace_back(Instruction::FLDA, 0);
            instrs.emplace_back(Instruction::FMULI, Instruction::Immediate {.as_double = 2});
            instrs.emplace_back(Instruction::FSTA, 5);

            instrs.emplace_back(Instruction::FLDA, 4);
            instrs.emplace_back(Instruction::FADD, 3);
            instrs.emplace_back(Instruction::FDIV, 5);
            instrs.emplace_back(Instruction::FSTA, 6);

            instrs.emplace_back(Instruction::FLDA, 4);
            instrs.emplace_back(Instruction::FSUB, 3);
            instrs.emplace_back(Instruction::FDIV, 5);
            instrs.emplace_back(Instruction::FSTA, 7);

            instrs.emplace_back(Instruction::LDASTR,
                                Instruction::Immediate {.as_obj = table.RegisterString("Roots of the equation:")});
            instrs.emplace_back(Instruction::STAOBJ, 3);
            instrs.emplace_back(
                Proto::Create(Proto::HANDLE_VOID_OBJ, reinterpret_cast<void *>(stdlib::IO::printlnString), 3));

            instrs.emplace_back(
                Proto::Create(Proto::HANDLE_VOID_F64, reinterpret_cast<void *>(stdlib::IO::printlnF64), 6));
            instrs.emplace_back(
                Proto::Create(Proto::HANDLE_VOID_F64, reinterpret_cast<void *>(stdlib::IO::printlnF64), 7));
            instrs.emplace_back(Instruction::RET, Instruction::Immediate {0});

            return Body(8, std::move(instrs));
        };
        bc.CreateMethod(std::move(main_body), Signature(Signature::INT, {}), "main");
        return bc;
    }
};

int main()
{
    mipt_vm::Runtime::Create();

    auto *runtime = mipt_vm::Runtime::GetInstance();
    auto bytecode = SquareEquation::GenerateBytecode();
    runtime->GetVM()->GetInterpreter().InterpretEntrypoint(bytecode, "main");

    mipt_vm::Runtime::Destroy();

    return 0;
}
