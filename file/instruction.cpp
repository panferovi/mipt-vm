#include "file/instruction.h"

namespace mipt_vm {

Instruction::Instruction(Instruction::Type type, uint8_t reg_src_2) : type(type)
{
    src_2.reg = reg_src_2;
}

Instruction::Instruction(Instruction::Type type, Instruction::Immediate imm) : type(type)
{
    src_2.imm = imm;
}

Instruction::Instruction(Proto *proto) : type(Instruction::Type::CALL)
{
    src_2.proto = proto;
}

Instruction::Instruction(Instruction::Type type, uint8_t src_1, Instruction::Immediate imm)
    : type(type), src_reg_1(src_1)
{
    src_2.imm = imm;
}

Instruction::Instruction(Instruction::Type type, uint8_t src_1, uint8_t reg_src_2) : type(type), src_reg_1(src_1)
{
    src_2.reg = reg_src_2;
}

Instruction::Instruction(Instruction &&inst) : type(inst.type), src_reg_1(inst.src_reg_1), src_2(inst.src_2)
{
    if (type == Instruction::Type::CALL) {
        src_2.proto = nullptr;
    }
}

Instruction &Instruction::operator=(Instruction &&inst)
{
    if (this != &inst) {
        type = inst.type;
        src_reg_1 = inst.src_reg_1;
        src_2 = inst.src_2;
        if (inst.type == Instruction::Type::CALL) {
            inst.src_2.proto = nullptr;
        }
    }
    return *this;
}

Instruction::~Instruction()
{
    if (type == Instruction::Type::CALL) {
        Proto::Destroy(src_2.proto);
    }
}

}  // namespace mipt_vm
