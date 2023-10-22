#ifndef RUNTIME_FRAME_H_
#define RUNTIME_FRAME_H_

#include "file/method.h"
#include "runtime/register_manager.h"

namespace mipt_vm {

class Frame {
public:
    Frame(Method *method) : method_(method), reg_manager_(method->GetBody().GetRegCnt()) {}

    static Frame *Create(Method *method)
    {
        // TODO(egorov): allocate Frame via internal_allocator
        return new Frame(method);
    }

    static void Destroy(Frame *frame)
    {
        delete frame;
    }

    void PassParams(Frame *prev_frame)
    {
        ASSERT(prev_frame != nullptr);
        [[maybe_unused]] const auto *instr = prev_frame->method_->GetBody().GetInstruction(frame_pc_);
        ASSERT(instr->type == Instruction::CALL);
        auto params_cnt = method_->GetSignature().GetParamsCnt();
        [[maybe_unused]] auto &params = method_->GetSignature().GetParams();
        for (size_t i = 0; i < params_cnt; ++i) {
            UNREACHABLE();
            // Register reg;
            // switch (params[i]) {
            //     case Signature::OBJ:
            //         reg = prev_frame->reg_manager_.GetRegister(instr->params[i]);
            //         break;
            //     case Signature::INT:
            //         // TODO(panferovi): implement instruction hierarchy
            //         UNREACHABLE();
            //         break;
            //     case Signature::DOUBLE:
            //         UNREACHABLE();
            //         break;
            //     case Signature::STR:
            //         UNREACHABLE();
            //         break;
            //     default:
            //         UNREACHABLE();
            // }
            // reg_manager_.AllocateRegister(reg);
        }
    }

    Register GetReturnValue()
    {
        const auto *instr = method_->GetBody().GetInstruction(frame_pc_);
        ASSERT(instr->type == Instruction::RET);
        switch (method_->GetSignature().GetReturnType()) {
            case Signature::VOID:
                return Register {};
            case Signature::INT:
                return Register {.as_int = instr->imm.as_int};
            case Signature::DOUBLE:
                return Register {.as_double = instr->imm.as_double};
            case Signature::STR:
                return Register {.as_obj = instr->imm.as_obj};
            case Signature::OBJ:
                return reg_manager_.GetRegister(instr->reg);
            default:
                UNREACHABLE();
        }
    }

    void SetupContext(uint64_t **pc, const Instruction **instr)
    {
        *pc = &frame_pc_;
        *instr = method_->GetBody().GetInstruction(frame_pc_);
    }

    inline const Instruction *GetInstruction(uint64_t pc)
    {
        return method_->GetBody().GetInstruction(pc);
    }

    inline Register &GetRegister(RegisterManager::RegisterIdx idx)
    {
        return reg_manager_.GetRegister(idx);
    }

private:
    uint64_t frame_pc_ {0};
    Method *method_;
    RegisterManager reg_manager_;
};

}  // namespace mipt_vm

#endif  // RUNTIME_FRAME_H_
