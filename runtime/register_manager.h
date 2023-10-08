#ifndef RUNTIME_REGISTER_MANAGER_H_
#define RUNTIME_REGISTER_MANAGER_H_

#include <cstdint>
#include <cstddef>
#include <array>

namespace mipt_vm {

class Register {
public:
    using ValueType = int64_t;
    ValueType value;
};

class RegisterManager {
public:
    RegisterManager() = default;
    NO_COPY_SEMANTIC(RegisterManager);
    NO_MOVE_SEMANTIC(RegisterManager);

    static constexpr uint16_t RegisterCount = UINT16_MAX;

private:
    uint64_t pc_ = 0;
    uint64_t accumulator_ = 0;
    std::array<Register, RegisterCount> registers_;
};

}  // namespace mipt_vm

#endif  // RUNTIME_REGISTER_MANAGER_H_
