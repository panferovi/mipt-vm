#ifndef FILE_BYTECODE_H_
#define FILE_BYTECODE_H_

#include <vector>

#include "file/proto.h"

namespace mipt_vm {

class Instruction {
public:
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

    Type type;
    uint8_t src_1;
    uint8_t src_2;
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
