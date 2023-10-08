#ifndef RUNTIME_RUNTIME_H_
#define RUNTIME_RUNTIME_H_

#include "common/macros.h"
#include "runtime/vm.h"

namespace mipt_vm {

class Runtime {
public:
    static void Create();

    static void Destroy();

    static Runtime *GetInstance();

    VM *GetVM();

private:
    Runtime();
    ~Runtime();
    NO_COPY_SEMANTIC(Runtime);
    NO_MOVE_SEMANTIC(Runtime);

    VM *vm_ = nullptr;
    static Runtime *instance_;
};

}  // namespace mipt_vm

#endif  // RUNTIME_RUNTIME_H_
