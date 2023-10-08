#include "runtime/runtime.h"

namespace mipt_vm {

Runtime *Runtime::instance_ = nullptr;

/* static */
void Runtime::Create()
{
    ASSERT(instance_ == nullptr);
    instance_ = new Runtime();
}

/* static */
void Runtime::Destroy()
{
    ASSERT(instance_ != nullptr);
    delete instance_;
    instance_ = nullptr;
}

/* static */
Runtime *Runtime::GetInstance()
{
    return instance_;
}

VM *Runtime::GetVM()
{
    return vm_;
}

Runtime::Runtime()
{
    vm_ = new VM();
}

Runtime::~Runtime()
{
    delete vm_;
}

}  // namespace mipt_vm
