#ifndef RUNTIME_REGISTER_MANAGER_H_
#define RUNTIME_REGISTER_MANAGER_H_

#include <cstdint>
#include <cstddef>
#include <array>

namespace mipt_vm {

class Register {
public:
    union ValueType {
        int64_t as_int {0};
        uint64_t as_uint;
        double as_double;
    };

    ValueType value;
};

class RegisterManager {
public:
    RegisterManager() = default;
    NO_COPY_SEMANTIC(RegisterManager);
    NO_MOVE_SEMANTIC(RegisterManager);

    static constexpr uint16_t RegisterCount = UINT16_MAX;

    uint64_t &GetPc()
    {
        return pc_;
    }

    Register &GetAccumulator()
    {
        return accumulator_;
    }

    std::array<Register, RegisterCount> &GetRegisters()
    {
        return registers_;
    }

private:
    uint64_t pc_ {0};
    Register accumulator_;
    std::array<Register, RegisterCount> registers_;
};

}  // namespace mipt_vm

#endif  // RUNTIME_REGISTER_MANAGER_H_
