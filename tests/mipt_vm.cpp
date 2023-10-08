#include <gtest/gtest.h>

#include "runtime/runtime.h"

TEST(MIPT_VM, ExecutionFlowTest)
{
    ASSERT_EQ(mipt_vm::Runtime::GetInstance(), nullptr);
    mipt_vm::Runtime::Create();

    auto *runtime = mipt_vm::Runtime::GetInstance();
    ASSERT_NE(runtime, nullptr);
    ASSERT_NE(runtime->GetVM(), nullptr);

    mipt_vm::Bytecode bc;
    runtime->GetVM()->GetInterpreter().Interpret(bc);

    mipt_vm::Runtime::Destroy();
    ASSERT_EQ(mipt_vm::Runtime::GetInstance(), nullptr);
}
