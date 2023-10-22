#ifndef FILE_META_H_
#define FILE_META_H_

#include <unordered_map>
#include <string_view>

#include "file/method.h"

namespace mipt_vm {

class BytecodeMeta {
public:
    using MethodId = uint32_t;
    static constexpr uint32_t INVALID_METHOD_ID = UINT32_MAX;

    void RegisterMethod(std::string_view method_name, MethodId id)
    {
        [[maybe_unused]] auto [_, is_inserted] = methods_.insert({method_name, id});
        ASSERT(is_inserted);
    }

    MethodId GetMethodId(std::string_view method_name) const
    {
        auto method_iter = methods_.find(method_name);
        if (method_iter == methods_.cend()) {
            return INVALID_METHOD_ID;
        }
        return method_iter->second;
    }

private:
    std::unordered_map<std::string_view, MethodId> methods_;
};

}  // namespace mipt_vm

#endif  // FILE_META_H_
