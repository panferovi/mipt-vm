#ifndef FILE_BYTECODE_H_
#define FILE_BYTECODE_H_

#include <vector>

#include "file/proto.h"

namespace mipt_vm {

class Instruction {
public:
    // clang-format off
    enum Type : uint8_t {
        LDA,
        LDA_I,
        LDA_STR,
        STA,
        STA_OBJ,
        ADD,
        SUB,
        MUL,
        MULI,
        DIV,
        CALL,
        RETURN
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
