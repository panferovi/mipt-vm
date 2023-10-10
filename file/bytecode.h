#ifndef FILE_BYTECODE_H_
#define FILE_BYTECODE_H_

#include <vector>

#include "file/instruction.h"

namespace mipt_vm {

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
