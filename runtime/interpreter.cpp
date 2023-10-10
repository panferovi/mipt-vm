#include "interpreter.h"
#include "../file/bytecode.h"

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

#define DISPATCH() \
    pc++;          \
    goto *dispatch_table[insns[pc].type];

    goto *dispatch_table[insns[pc].type];

sta:
    printf("Im sta\n");
    registers[insns[pc].src_2.reg_name] = ac;
    DISPATCH()
fsta:
    printf("Im fsta\n");
    registers[insns[pc].src_2.reg_name] = ac;
    DISPATCH()
lda:
    printf("Im lda\n");
    ac = registers[insns[pc].src_2.reg_name];
    DISPATCH()
ldai:
    printf("Im ldai\n");
    ac.value.as_int = insns[pc].src_2.imm.as_int;
    DISPATCH()
flda:
    printf("Im flda\n");
    ac = registers[insns[pc].src_2.reg_name];
    DISPATCH()
fldai:
    printf("Im fldai\n");
    ac.value.as_double = insns[pc].src_2.imm.as_double;
    DISPATCH()
add:
    printf("Im add\n");
    ac.value.as_int += registers[insns[pc].src_2.reg_name].value.as_int;
    DISPATCH()
addi:
    printf("Im addi\n");
    ac.value.as_int += insns[pc].src_2.imm.as_int;
    DISPATCH()
fadd:
    printf("Im fadd\n");
    ac.value.as_double += registers[insns[pc].src_2.reg_name].value.as_double;
    DISPATCH()
faddi:
    printf("Im faddi\n");
    ac.value.as_double += insns[pc].src_2.imm.as_double;
    DISPATCH()
sub:
    printf("Im sub\n");
    ac.value.as_int -= registers[insns[pc].src_2.reg_name].value.as_int;
    DISPATCH()
subi:
    printf("Im subi\n");
    ac.value.as_int -= insns[pc].src_2.imm.as_int;
    DISPATCH()
fsub:
    printf("Im fsub\n");
    ac.value.as_double -= registers[insns[pc].src_2.reg_name].value.as_double;
    DISPATCH()
fsubi:
    printf("Im fsubi\n");
    ac.value.as_double -= insns[pc].src_2.imm.as_double;
    DISPATCH()
mul:
    printf("Im mul\n");
    ac.value.as_int *= registers[insns[pc].src_2.reg_name].value.as_int;
    DISPATCH()
muli:
    printf("Im muli\n");
    ac.value.as_int *= insns[pc].src_2.imm.as_int;
    DISPATCH()
fmul:
    printf("Im fmul\n");
    ac.value.as_double *= registers[insns[pc].src_2.reg_name].value.as_double;
    DISPATCH()
fmuli:
    printf("Im fmuli\n");
    ac.value.as_double *= insns[pc].src_2.imm.as_double;
    DISPATCH()
div:
    ac.value.as_int /= registers[insns[pc].src_2.reg_name].value.as_int;
    printf("Im div\n");
    DISPATCH()
divi:
    ac.value.as_int /= insns[pc].src_2.imm.as_int;
    printf("Im divi\n");
    DISPATCH()
fdiv:
    printf("Im fdiv\n");
    ac.value.as_double /= registers[insns[pc].src_2.reg_name].value.as_double;
    DISPATCH()
fdivi:
    printf("Im fdivi\n");
    ac.value.as_double /= insns[pc].src_2.imm.as_double;
    DISPATCH()
ldastr:
    printf("Im ldai\n");
    ac.value.as_uint = insns[pc].src_2.imm.as_uint;
    DISPATCH()
staobj:
    registers[insns[pc].src_2.reg_name] = ac;
    DISPATCH();
exit:
    // printf("Res %ld\n", ac.value.as_int);
    return;
call:
    auto proto_type = insns[pc].src_2.proto->GetType();
    auto handler = insns[pc].src_2.proto->GetHandler();
    auto arg = insns[pc].src_2.proto->GetArg();

    switch (proto_type) {
        case Proto::Type::HANDLE_VOID_F64:
            reinterpret_cast<void (*)(double)>(handler)(registers[arg].value.as_double);
            break;
        case Proto::Type::HANDLE_VOID_OBJ:
            reinterpret_cast<void (*)(uint64_t)>(handler)(registers[arg].value.as_uint);
            break;
        case Proto::Type::HANDLE_F64_VOID:
            ac.value.as_double = reinterpret_cast<double (*)()>(handler)();
            break;
        case Proto::Type::HANDLE_F64_F64:
            ac.value.as_double = reinterpret_cast<double (*)(double)>(handler)(registers[arg].value.as_double);
            break;
        default:
            UNREACHABLE();
            break;
    }
}

}  // namespace mipt_vm
