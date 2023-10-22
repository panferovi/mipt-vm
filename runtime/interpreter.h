#ifndef RUNTIME_INTERPRETER_H_
#define RUNTIME_INTERPRETER_H_

#include <stack>

#include "common/macros.h"
#include "runtime/frame.h"

namespace mipt_vm {

class Bytecode;

class Interpreter {
public:
    Interpreter() = default;
    NO_COPY_SEMANTIC(Interpreter);
    NO_MOVE_SEMANTIC(Interpreter);

    void InterpretEntrypoint(Bytecode &bytecode, std::string_view entrypoint_name);

    void FrameEntrypoint(Method *method)
    {
        auto *next_frame = Frame::Create(method);
        auto *frame = GetCurrentFrame();
        if (frame != nullptr) {
            next_frame->PassParams(frame);
        }
        frames_.push(next_frame);
    }

    void FrameEndpoint()
    {
        auto *frame = frames_.top();
        ASSERT(frame != nullptr);
        accum_ = frame->GetReturnValue();
        Frame::Destroy(frame);
        frames_.pop();
    }

    Frame *GetCurrentFrame()
    {
        if (UNLIKELY(frames_.empty())) {
            return nullptr;
        }
        return frames_.top();
    }

private:
    void Interpret(Bytecode &bytecode);

    Register accum_;
    std::stack<Frame *> frames_;
};

}  // namespace mipt_vm

#endif  // RUNTIME_INTERPRETER_H_
