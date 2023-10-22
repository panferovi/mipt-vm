#ifndef FILE_INSTRUCTION_H_
#define FILE_INSTRUCTION_H_

#include <cstdint>
#include <iostream>

#include "file/proto.h"
#include "common/macros.h"

namespace mipt_vm {

class Instruction {
public:
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
        RET,
        CALLINTRINSIC,
        EXIT,

        INVALID
    };

    union Immediate {
        int64_t as_int;
        double as_double;
        uintptr_t as_obj;
    };

    Instruction(Type type);
    Instruction(Type type, uint16_t reg_src_2);
    Instruction(Type type, Immediate imm);
    Instruction(Proto *proto);
    Instruction(Type type, uint16_t src_1, Immediate imm);
    Instruction(Type type, uint16_t src_1, uint16_t reg_src_2);

    NO_COPY_SEMANTIC(Instruction);
    Instruction(Instruction &&inst);
    Instruction &operator=(Instruction &&inst);
    ~Instruction();

    Type type;
    uint16_t src_reg_1 {0};
    union {
        uint16_t reg;
        Immediate imm;
        Proto *proto {nullptr};
    };
};

}  // namespace mipt_vm

#endif  // FILE_INSTRUCTION_H_
