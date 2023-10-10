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

    Proto::Type proto_type = Proto::Type::HANDLE_F64_F64;
    void *handler = nullptr;
    uint8_t reg = 0;

#define DISPATCH() \
    pc++;          \
    goto *dispatch_table[insns[pc].type]

    goto *dispatch_table[insns[pc].type];

sta:
    printf("Im sta\n");
    registers[insns[pc].src_2.reg] = ac;
    DISPATCH();
fsta:
    printf("Im fsta\n");
    registers[insns[pc].src_2.reg] = ac;
    DISPATCH();
lda:
    printf("Im lda\n");
    ac = registers[insns[pc].src_2.reg];
    DISPATCH();
ldai:
    printf("Im ldai\n");
    ac.value.as_int = insns[pc].src_2.imm.as_int;
    DISPATCH();
flda:
    printf("Im flda\n");
    ac = registers[insns[pc].src_2.reg];
    DISPATCH();
fldai:
    printf("Im fldai\n");
    ac.value.as_double = insns[pc].src_2.imm.as_double;
    DISPATCH();
add:
    printf("Im add\n");
    ac.value.as_int += registers[insns[pc].src_2.reg].value.as_int;
    DISPATCH();
addi:
    printf("Im addi\n");
    ac.value.as_int += insns[pc].src_2.imm.as_int;
    DISPATCH();
fadd:
    printf("Im fadd\n");
    ac.value.as_double += registers[insns[pc].src_2.reg].value.as_double;
    DISPATCH();
faddi:
    printf("Im faddi\n");
    ac.value.as_double += insns[pc].src_2.imm.as_double;
    DISPATCH();
sub:
    printf("Im sub\n");
    ac.value.as_int -= registers[insns[pc].src_2.reg].value.as_int;
    DISPATCH();
subi:
    printf("Im subi\n");
    ac.value.as_int -= insns[pc].src_2.imm.as_int;
    DISPATCH();
fsub:
    printf("Im fsub\n");
    ac.value.as_double -= registers[insns[pc].src_2.reg].value.as_double;
    DISPATCH();
fsubi:
    printf("Im fsubi\n");
    ac.value.as_double -= insns[pc].src_2.imm.as_double;
    DISPATCH();
mul:
    printf("Im mul\n");
    ac.value.as_int *= registers[insns[pc].src_2.reg].value.as_int;
    DISPATCH();
muli:
    printf("Im muli\n");
    ac.value.as_int *= insns[pc].src_2.imm.as_int;
    DISPATCH();
fmul:
    printf("Im fmul\n");
    ac.value.as_double *= registers[insns[pc].src_2.reg].value.as_double;
    DISPATCH();
fmuli:
    printf("Im fmuli\n");
    ac.value.as_double *= insns[pc].src_2.imm.as_double;
    DISPATCH();
div:
    ac.value.as_int /= registers[insns[pc].src_2.reg].value.as_int;
    printf("Im div\n");
    DISPATCH();
divi:
    ac.value.as_int /= insns[pc].src_2.imm.as_int;
    printf("Im divi\n");
    DISPATCH();
fdiv:
    printf("Im fdiv\n");
    ac.value.as_double /= registers[insns[pc].src_2.reg].value.as_double;
    DISPATCH();
fdivi:
    printf("Im fdivi\n");
    ac.value.as_double /= insns[pc].src_2.imm.as_double;
    DISPATCH();
ldastr:
    printf("Im ldastr\n");
    ac.value.as_uint = insns[pc].src_2.imm.as_uint;
    DISPATCH();
staobj:
    printf("Im staobj\n");
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
            printf("Im HANDLE_VOID_OBJ\n");
            reinterpret_cast<void (*)(uint64_t)>(handler)(registers[reg].value.as_uint);
            break;
        case Proto::Type::HANDLE_F64_VOID:
            ac.value.as_double = reinterpret_cast<double (*)()>(handler)();
            printf("Im HANDLE_F64_VOID %lg\n", ac.value.as_double);
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
    // printf("Res %ld\n", ac.value.as_int);
    return;
}

}  // namespace mipt_vm
