#ifndef FILE_STRING_TABLE_H_
#define FILE_STRING_TABLE_H_

#include <vector>
#include <string_view>

#include "common/macros.h"

namespace mipt_vm {

class StringTable {
public:
    using StringId = uintptr_t;

    StringId RegisterString(std::string_view immidiate_string)
    {
        StringId id = reinterpret_cast<StringId>(immidiate_string.data());
        for (size_t i = 0; i < table_.size(); ++i) {
            if (table_[i] == immidiate_string) {
                return id;
            }
        }
        table_.emplace_back(std::move(immidiate_string));
        return id;
    }

private:
    std::vector<std::string_view> table_;
};

}  // namespace mipt_vm

#endif  // FILE_STRING_TABLE_H_
