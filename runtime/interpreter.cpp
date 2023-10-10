#include "runtime/interpreter.h"
#include "file/bytecode.h"
#include "common/macros.h"

namespace mipt_vm {

void Interpreter::Interpret([[maybe_unused]] Bytecode &bytecode)
{
    static void *dispatch_table[] = {
        &&lda,  &&ldai, &&flda,  &&fldai, &&ldastr, &&sta,  &&fsta,  &&staobj, &&add,  &&addi, &&fadd,  &&faddi, &&sub,
        &&subi, &&fsub, &&fsubi, &&mul,   &&muli,   &&fmul, &&fmuli, &&div,    &&divi, &&fdiv, &&fdivi, &&call,  &&exit,
    };

    std::vector<Instruction> &insns = bytecode.GetInstructions();
    auto &pc = reg_manager_.GetPc();
    auto &ac = reg_manager_.GetAccumulator();
    auto &registers = reg_manager_.GetRegisters();

    Proto::Type proto_type = Proto::Type::UNDEFINED;
    void *handler = nullptr;
    uint8_t reg = 0;

#define DISPATCH() \
    pc++;          \
    goto *dispatch_table[insns[pc].type]

    goto *dispatch_table[insns[pc].type];

sta:
    LOG("Im sta");
    registers[insns[pc].src_2.reg] = ac;
    DISPATCH();
fsta:
    LOG("Im fsta");
    registers[insns[pc].src_2.reg] = ac;
    DISPATCH();
lda:
    LOG("Im lda");
    ac = registers[insns[pc].src_2.reg];
    DISPATCH();
ldai:
    LOG("Im ldai");
    ac.value.as_int = insns[pc].src_2.imm.as_int;
    DISPATCH();
flda:
    LOG("Im flda");
    ac = registers[insns[pc].src_2.reg];
    DISPATCH();
fldai:
    LOG("Im fldai");
    ac.value.as_double = insns[pc].src_2.imm.as_double;
    DISPATCH();
add:
    LOG("Im add");
    ac.value.as_int += registers[insns[pc].src_2.reg].value.as_int;
    DISPATCH();
addi:
    LOG("Im addi");
    ac.value.as_int += insns[pc].src_2.imm.as_int;
    DISPATCH();
fadd:
    LOG("Im fadd");
    ac.value.as_double += registers[insns[pc].src_2.reg].value.as_double;
    DISPATCH();
faddi:
    LOG("Im faddi");
    ac.value.as_double += insns[pc].src_2.imm.as_double;
    DISPATCH();
sub:
    LOG("Im sub");
    ac.value.as_int -= registers[insns[pc].src_2.reg].value.as_int;
    DISPATCH();
subi:
    LOG("Im subi");
    ac.value.as_int -= insns[pc].src_2.imm.as_int;
    DISPATCH();
fsub:
    LOG("Im fsub");
    ac.value.as_double -= registers[insns[pc].src_2.reg].value.as_double;
    DISPATCH();
fsubi:
    LOG("Im fsubi");
    ac.value.as_double -= insns[pc].src_2.imm.as_double;
    DISPATCH();
mul:
    LOG("Im mul");
    ac.value.as_int *= registers[insns[pc].src_2.reg].value.as_int;
    DISPATCH();
muli:
    LOG("Im muli");
    ac.value.as_int *= insns[pc].src_2.imm.as_int;
    DISPATCH();
fmul:
    LOG("Im fmul");
    ac.value.as_double *= registers[insns[pc].src_2.reg].value.as_double;
    DISPATCH();
fmuli:
    LOG("Im fmuli");
    ac.value.as_double *= insns[pc].src_2.imm.as_double;
    DISPATCH();
div:
    ac.value.as_int /= registers[insns[pc].src_2.reg].value.as_int;
    LOG("Im div");
    DISPATCH();
divi:
    ac.value.as_int /= insns[pc].src_2.imm.as_int;
    LOG("Im divi");
    DISPATCH();
fdiv:
    LOG("Im fdiv");
    ac.value.as_double /= registers[insns[pc].src_2.reg].value.as_double;
    DISPATCH();
fdivi:
    LOG("Im fdivi");
    ac.value.as_double /= insns[pc].src_2.imm.as_double;
    DISPATCH();
ldastr:
    LOG("Im ldastr");
    ac.value.as_uint = insns[pc].src_2.imm.as_uint;
    DISPATCH();
staobj:
    LOG("Im staobj");
    registers[insns[pc].src_2.reg] = ac;
    DISPATCH();
call:
    proto_type = insns[pc].src_2.proto->GetType();
    handler = insns[pc].src_2.proto->GetHandler();
    reg = insns[pc].src_2.proto->GetReg();

    switch (proto_type) {
        case Proto::Type::HANDLE_VOID_F64:
            reinterpret_cast<void (*)(double)>(handler)(registers[reg].value.as_double);
            break;
        case Proto::Type::HANDLE_VOID_OBJ:
            LOG("Im HANDLE_VOID_OBJ");
            reinterpret_cast<void (*)(uint64_t)>(handler)(registers[reg].value.as_uint);
            break;
        case Proto::Type::HANDLE_F64_VOID:
            ac.value.as_double = reinterpret_cast<double (*)()>(handler)();
            break;
        case Proto::Type::HANDLE_F64_F64:
            ac.value.as_double = reinterpret_cast<double (*)(double)>(handler)(registers[reg].value.as_double);
            break;
        default:
            UNREACHABLE();
            break;
    }
    DISPATCH();
exit:
    return;
}

}  // namespace mipt_vm
