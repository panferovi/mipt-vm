#ifndef FILE_PROTO_H_
#define FILE_PROTO_H_

#include <cstdint>

namespace mipt_vm {

class Proto {
public:
    enum Type : uint8_t {
        UNDEFINED,
        HANDLE_VOID_VOID,
        HANDLE_VOID_I64,
        HANDLE_VOID_F64,
        HANDLE_VOID_OBJ,
        HANDLE_I64_VOID,
        HANDLE_F64_VOID,
        HANDLE_OBJ_VOID,
        HANDLE_F64_F64,

        HANDLE_COMPLEX
    };

    static Proto *Create(Type type, void *handler, uint8_t reg)
    {
        return new Proto {type, handler, reg};
    }

    static Proto *Create(Type type, void *handler)
    {
        return new Proto {type, handler};
    }

    static void Destroy(Proto *proto)
    {
        delete proto;
    }

    Proto(Type type, void *handler, uint16_t reg) : type_(type), handler_(handler), reg_(reg) {}

    Proto(Type type, void *handler) : type_(type), handler_(handler) {}

    void *GetHandler()
    {
        return handler_;
    }

    uint16_t GetReg()
    {
        return reg_;
    }

    Type GetType()
    {
        return type_;
    }

private:
    const Type type_;
    void *handler_ {nullptr};
    uint16_t reg_ {0};
};

}  // namespace mipt_vm

#endif  // FILE_PROTO_H_
