#ifndef FILE_INSTRUCTION_H_
#define FILE_INSTRUCTION_H_

#include <cstdint>
#include <iostream>

#include "file/proto.h"

namespace mipt_vm {

class Instruction {
public:
    // clang-format off
    enum Type : uint8_t {
        LDA,
        LDAI,
        FLDA,
        FLDAI,
        LDASTR,
        STA,
        FSTA,
        STAOBJ,
        ADD,
        ADDI,
        FADD,
        FADDI,
        SUB,
        SUBI,
        FSUB,
        FSUBI,
        MUL,
        MULI,
        FMUL,
        FMULI,
        DIV,
        DIVI,
        FDIV,
        FDIVI,
        CALL,
        EXIT
    };
    // clang-format on

    union Immediate {
        uint64_t as_uint;
        int64_t as_int;
        double as_double;
    };

    union OperandType {
        uint8_t reg;
        Immediate imm;
        Proto *proto {nullptr};
    };

    Instruction(Type type, uint8_t reg_src_2) : type(type)
    {
        src_2.reg = reg_src_2;
    }

    Instruction(Type type, Immediate imm) : type(type)
    {
        src_2.imm = imm;
    }

    Instruction(Proto *proto) : type(Type::CALL)
    {
        src_2.proto = proto;
    }

    Instruction(Type type, uint8_t src_1, Immediate imm) : type(type), src_reg_1(src_1)
    {
        src_2.imm = imm;
    }

    Instruction(Type type, uint8_t src_1, uint8_t reg_src_2) : type(type), src_reg_1(src_1)
    {
        src_2.reg = reg_src_2;
    }

    Instruction(Instruction &&inst)
        : type(inst.type), src_reg_1(inst.src_reg_1), src_2(inst.src_2)
    {
        if (type == Type::CALL) {
            src_2.proto = nullptr;
        }
    }
    Instruction &operator=(Instruction &&inst) {
        if (this != &inst) {
            type = inst.type;
            src_reg_1 = inst.src_reg_1;
            src_2 = inst.src_2;
            if (inst.type == Type::CALL) {
                inst.src_2.proto = nullptr;
            }
        }
        return *this;
    }

    NO_COPY_SEMANTIC(Instruction);

    ~Instruction() {
        if (type == Type::CALL) {
            Proto::Destroy(src_2.proto);
        }
    }

    Type type;
    uint8_t src_reg_1 {0};
    OperandType src_2;
};

}  // mipt_vm

#endif  // FILE_INSTRUCTION_H_
