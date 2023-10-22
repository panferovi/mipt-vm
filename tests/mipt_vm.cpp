#include <gtest/gtest.h>

#include "runtime/runtime.h"
#include "runtime/vm.h"
#include "file/bytecode.h"
#include "stdlib/io.h"

namespace mipt_vm::testing {

TEST(MIPT_VM, ExecutionFlowTest)
{
    ASSERT_EQ(mipt_vm::Runtime::GetInstance(), nullptr);
    mipt_vm::Runtime::Create();

    auto *runtime = mipt_vm::Runtime::GetInstance();
    ASSERT_NE(runtime, nullptr);
    ASSERT_NE(runtime->GetVM(), nullptr);

    mipt_vm::Bytecode bc;
    auto main_body = [](StringTable &, const BytecodeMeta &) {
        Body::Instructions instrs;
        instrs.emplace_back(Instruction::Type::RET, Instruction::Immediate {0});
        return Body(0, std::move(instrs));
    };
    bc.CreateMethod(std::move(main_body), Signature(Signature::INT, {}), "main");
    runtime->GetVM()->GetInterpreter().InterpretEntrypoint(bc, "main");

    mipt_vm::Runtime::Destroy();
    ASSERT_EQ(mipt_vm::Runtime::GetInstance(), nullptr);
}

TEST(MIPT_VM, CallTest)
{
    using namespace mipt_vm;
    Bytecode bc;

    // foo frame
    auto foo_body = [](StringTable &table, const BytecodeMeta &) {
        Body::Instructions instrs;
        auto id = table.RegisterString("Inside foo");
        instrs.emplace_back(Instruction::Type::LDASTR, Instruction::Immediate {.as_obj = id});
        instrs.emplace_back(Instruction::Type::STAOBJ, 0);
        instrs.emplace_back(
            Proto::Create(Proto::Type::HANDLE_VOID_OBJ, reinterpret_cast<void *>(stdlib::IO::printlnString), 0));
        instrs.emplace_back(Instruction::Type::RET);
        return Body(1, std::move(instrs));
    };
    bc.CreateMethod(std::move(foo_body), Signature(Signature::VOID, {}), "foo");

    // main frame
    auto main_body = [](StringTable &, const BytecodeMeta &meta) {
        Body::Instructions instrs;
        instrs.emplace_back(Instruction::Type::CALL, Instruction::Immediate {meta.GetMethodId("foo")});
        instrs.emplace_back(Instruction::Type::RET, Instruction::Immediate {0});
        return Body(0, std::move(instrs));
    };
    bc.CreateMethod(std::move(main_body), Signature(Signature::INT, {}), "main");

    mipt_vm::Runtime::Create();
    auto *runtime = mipt_vm::Runtime::GetInstance();
    runtime->GetVM()->GetInterpreter().InterpretEntrypoint(bc, "main");
    mipt_vm::Runtime::Destroy();
}

}  // namespace mipt_vm::testing
