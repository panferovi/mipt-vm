#include "file/instruction.h"

namespace mipt_vm {

Instruction::Instruction(Instruction::Type type) : type(type)
{
    ASSERT((type == Instruction::RET) || (type == Instruction::EXIT));
}

Instruction::Instruction(Instruction::Type type, uint16_t reg_src_2) : type(type)
{
    reg = reg_src_2;
}

Instruction::Instruction(Instruction::Type type, Instruction::Immediate imm) : type(type)
{
    this->imm = imm;
}

Instruction::Instruction(Proto *proto) : type(Instruction::Type::CALLINTRINSIC)
{
    this->proto = proto;
}

Instruction::Instruction(Instruction::Type type, uint16_t src_1, Instruction::Immediate imm)
    : type(type), src_reg_1(src_1)
{
    this->imm = imm;
}

Instruction::Instruction(Instruction::Type type, uint16_t src_1, uint16_t reg_src_2) : type(type), src_reg_1(src_1)
{
    reg = reg_src_2;
}

Instruction::Instruction(Instruction &&inst) : type(inst.type), src_reg_1(inst.src_reg_1), imm(inst.imm)
{
    inst.type = Instruction::INVALID;
}

Instruction &Instruction::operator=(Instruction &&inst)
{
    if (this != &inst) {
        type = inst.type;
        src_reg_1 = inst.src_reg_1;
        imm = inst.imm;
        inst.type = Instruction::INVALID;
    }
    return *this;
}

Instruction::~Instruction()
{
    if (type == Instruction::Type::CALLINTRINSIC) {
        Proto::Destroy(proto);
    }
}

}  // namespace mipt_vm
