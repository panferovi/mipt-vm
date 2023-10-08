#ifndef FILE_BYTECODE_H_
#define FILE_BYTECODE_H_

#include <vector>

namespace mipt_vm {

class Instruction {

};

class Bytecode {
public:
    using Instructions = std::vector<Instruction>;

    Instructions &GetInstructions() {
        return instructions_;
    }

private:
    Instructions instructions_;
};

}  // namespace mipt_vm

#endif  // FILE_BYTECODE_H_
