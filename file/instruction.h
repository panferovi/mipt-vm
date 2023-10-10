#ifndef FILE_INSTRUCTION_H_
#define FILE_INSTRUCTION_H_

#include <cstdint>
#include <iostream>

#include "file/proto.h"
#include "common/macros.h"

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
        int64_t as_int;
        uint64_t as_uint;
        double as_double;
        void *as_ptr;
    };

    union OperandType {
        uint8_t reg;
        Immediate imm;
        Proto *proto {nullptr};
    };

    Instruction(Type type, uint8_t reg_src_2);
    Instruction(Type type, Immediate imm);
    Instruction(Proto *proto);
    Instruction(Type type, uint8_t src_1, Immediate imm);
    Instruction(Type type, uint8_t src_1, uint8_t reg_src_2);

    NO_COPY_SEMANTIC(Instruction);
    Instruction(Instruction &&inst);
    Instruction &operator=(Instruction &&inst);
    ~Instruction();

    Type type;
    uint8_t src_reg_1 {0};
    OperandType src_2;
};

}  // namespace mipt_vm

#endif  // FILE_INSTRUCTION_H_
