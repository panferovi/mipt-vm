#ifndef FILE_BYTECODE_H_
#define FILE_BYTECODE_H_

#include <vector>
#include <functional>

#include "file/meta.h"
#include "file/method.h"
#include "file/string_table.h"

namespace mipt_vm {

class Bytecode {
public:
    Bytecode() = default;
    NO_COPY_SEMANTIC(Bytecode);
    DEFAULT_MOVE_SEMANTIC(Bytecode);

    ~Bytecode()
    {
        for (auto *method : methods_) {
            Method::Destroy(method);
        }
    }

    using MethodBody = std::function<Body(StringTable &, const BytecodeMeta &)>;

    void CreateMethod(const MethodBody &body, Signature signature, std::string_view method_name)
    {
        auto id = methods_.size();
        auto *method = Method::Create(body(string_table_, meta_info_), std::move(signature), method_name);
        methods_.emplace_back(method);
        meta_info_.RegisterMethod(method_name, id);
    }

    Method *GetMethod(BytecodeMeta::MethodId id)
    {
        ASSERT(id < methods_.size());
        return methods_[id];
    }

    Method *GetEntryPoint(std::string_view method_name)
    {
        auto id = meta_info_.GetMethodId(method_name);
        return methods_[id];
    }

private:
    using Methods = std::vector<Method *>;

    Methods methods_;
    BytecodeMeta meta_info_;
    StringTable string_table_;
};

}  // namespace mipt_vm

#endif  // FILE_BYTECODE_H_
