#ifndef RUNTIME_REGISTER_MANAGER_H_
#define RUNTIME_REGISTER_MANAGER_H_

#include <cstdint>
#include <cstddef>
#include <array>

namespace mipt_vm {

class Register {
public:
    union {
        int64_t as_int;
        double as_double;
        uintptr_t as_obj;
    };
};

class RegisterManager {
public:
    RegisterManager(uint16_t register_cnt)
    {
        registers_.resize(register_cnt);
    }

    NO_COPY_SEMANTIC(RegisterManager);
    NO_MOVE_SEMANTIC(RegisterManager);

    using RegisterIdx = uint16_t;
    static constexpr uint16_t MAX_REGISTER_CNT = UINT16_MAX;

    inline Register &GetRegister(RegisterIdx idx)
    {
        ASSERT(idx < registers_.size());
        return registers_[idx];
    }

    const Register &GetDummy() const
    {
        return dummy_register_;
    }

    void AllocateRegister(Register reg = dummy_register_)
    {
        registers_.push_back(reg);
    }

private:
    using Registers = std::vector<Register>;

    static Register dummy_register_;
    Registers registers_;
};

}  // namespace mipt_vm

#endif  // RUNTIME_REGISTER_MANAGER_H_
