#ifndef FILE_METHOD_H_
#define FILE_METHOD_H_

#include <string_view>
#include <vector>
#include <array>
#include <initializer_list>

#include "file/instruction.h"

namespace mipt_vm {

class Body {
public:
    using Instructions = std::vector<Instruction>;

    Body(uint16_t reg_cnt, Instructions instructions) : reg_cnt_(reg_cnt), instructions_(std::move(instructions)) {}

    uint16_t GetRegCnt() const
    {
        return reg_cnt_;
    }

    inline const Instruction *GetInstruction(uint64_t pc) const
    {
        ASSERT(pc < instructions_.size());
        return &instructions_[pc];
    }

private:
    uint16_t reg_cnt_ = 0;
    Instructions instructions_;
};

class Signature {
public:
    enum Type : uint8_t { VOID, INT, DOUBLE, STR, OBJ };

    static constexpr uint8_t MAX_PARAMS_CNT = 4;
    using Params = std::array<Type, MAX_PARAMS_CNT>;

    Signature(Type ret, std::initializer_list<Type> params) : ret_(ret), param_cnt_(params.size())
    {
        ASSERT(param_cnt_ < MAX_PARAMS_CNT);
        auto param_iter = params.begin();
        for (size_t i = 0; i < param_cnt_; ++i, ++param_iter) {
            params_[i] = *param_iter;
        }
    }

    uint8_t GetParamsCnt() const
    {
        return param_cnt_;
    }

    Type GetReturnType() const
    {
        return ret_;
    }

    const Params &GetParams() const
    {
        return params_;
    }

private:
    Type ret_;
    Params params_;
    uint8_t param_cnt_ = 0;
};

class Method {
public:
    Method(Body body, Signature signature, std::string_view entrypoint_name)
        : body_(std::move(body)), signature_(std::move(signature)), entrypoint_name_(std::move(entrypoint_name))
    {
    }

    static Method *Create(Body body, Signature signature, std::string_view entrypoint_name)
    {
        return new Method(std::move(body), std::move(signature), std::move(entrypoint_name));
    }

    static void Destroy(Method *method)
    {
        delete method;
    }

    const Body &GetBody() const
    {
        return body_;
    }

    const Signature &GetSignature() const
    {
        return signature_;
    }

private:
    Body body_;
    Signature signature_;
    std::string_view entrypoint_name_;
};

}  // namespace mipt_vm

#endif  // FILE_METHOD_H_
