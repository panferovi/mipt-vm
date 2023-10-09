#ifndef FILE_PROTO_H_
#define FILE_PROTO_H_

#include <cstdint>

namespace mipt_vm {

class Proto {
public:
    enum Type : uint8_t {
        HANDLE_VOID_VOID,
        HANDLE_VOID_I,
        HANDLE_I_VOID,
        HANDLE_I_I,

        HANDLE_COMPLEX
    };

private:
    Type type_;
    uint8_t arg_name_ {0};
    void *handler_ {nullptr};
};

}  // namespace mipt_vm

#endif  // FILE_PROTO_H_
