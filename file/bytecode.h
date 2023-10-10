#ifndef FILE_BYTECODE_H_
#define FILE_BYTECODE_H_

#include <vector>

#include "proto.h"

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
    };

    union OperandType {
        uint8_t reg_name;
        Immediate imm;
        Proto *proto {nullptr};
    };

    Type type;
    uint8_t reg_src_1 {0};
    OperandType src_2;
};

class Bytecode {
public:
    using Instructions = std::vector<Instruction>;

    Instructions &GetInstructions()
    {
        return instructions_;
    }

private:
    Instructions instructions_;
};

}  // namespace mipt_vm

#endif  // FILE_BYTECODE_H_
