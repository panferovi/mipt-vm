#include "runtime/interpreter.h"
#include "file/bytecode.h"
#include "common/macros.h"

namespace mipt_vm {

void Interpreter::InterpretEntrypoint(Bytecode &bytecode, std::string_view entrypoint_name)
{
    ASSERT(frames_.empty());
    auto *method = bytecode.GetEntryPoint(entrypoint_name);
    ASSERT(method->GetSignature().GetParamsCnt() == 0);
    FrameEntrypoint(method);
    Interpret(bytecode);
}

void Interpreter::Interpret(Bytecode &bytecode)
{
    ASSERT(frames_.size() == 1);

    static void *dispatch_table[] = {&&lda,    &&ldai,  &&flda,  &&fldai, &&ldastr, &&sta,           &&fsta,
                                     &&staobj, &&add,   &&addi,  &&fadd,  &&faddi,  &&sub,           &&subi,
                                     &&fsub,   &&fsubi, &&mul,   &&muli,  &&fmul,   &&fmuli,         &&div,
                                     &&divi,   &&fdiv,  &&fdivi, &&call,  &&ret,    &&callintrinsic, &&exit};

    uint64_t *pc = nullptr;
    const Instruction *instr = nullptr;
    Frame *frame = GetCurrentFrame();
    frame->SetupContext(&pc, &instr);

    Proto::Type proto_type = Proto::UNDEFINED;
    void *handler = nullptr;
    uint16_t reg = 0;

#define DISPATCH()                               \
    (*pc)++;                                     \
    instr = frame->GetInstruction(*pc);          \
    ASSERT(instr->type != Instruction::INVALID); \
    goto *dispatch_table[instr->type]

    goto *dispatch_table[instr->type];

sta:
    LOG("Im sta");
    frame->GetRegister(instr->reg) = accum_;
    DISPATCH();
fsta:
    LOG("Im fsta");
    frame->GetRegister(instr->reg) = accum_;
    DISPATCH();
lda:
    LOG("Im lda");
    accum_ = frame->GetRegister(instr->reg);
    DISPATCH();
ldai:
    LOG("Im ldai");
    accum_.as_int = instr->imm.as_int;
    DISPATCH();
flda:
    LOG("Im flda");
    accum_ = frame->GetRegister(instr->reg);
    DISPATCH();
fldai:
    LOG("Im fldai");
    accum_.as_double = instr->imm.as_double;
    DISPATCH();
add:
    LOG("Im add");
    accum_.as_int += frame->GetRegister(instr->reg).as_int;
    DISPATCH();
addi:
    LOG("Im addi");
    accum_.as_int += instr->imm.as_int;
    DISPATCH();
fadd:
    LOG("Im fadd");
    accum_.as_double += frame->GetRegister(instr->reg).as_double;
    DISPATCH();
faddi:
    LOG("Im faddi");
    accum_.as_double += instr->imm.as_double;
    DISPATCH();
sub:
    LOG("Im sub");
    accum_.as_int -= frame->GetRegister(instr->reg).as_int;
    DISPATCH();
subi:
    LOG("Im subi");
    accum_.as_int -= instr->imm.as_int;
    DISPATCH();
fsub:
    LOG("Im fsub");
    accum_.as_double -= frame->GetRegister(instr->reg).as_double;
    DISPATCH();
fsubi:
    LOG("Im fsubi");
    accum_.as_double -= instr->imm.as_double;
    DISPATCH();
mul:
    LOG("Im mul");
    accum_.as_int *= frame->GetRegister(instr->reg).as_int;
    DISPATCH();
muli:
    LOG("Im muli");
    accum_.as_int *= instr->imm.as_int;
    DISPATCH();
fmul:
    LOG("Im fmul");
    accum_.as_double *= frame->GetRegister(instr->reg).as_double;
    DISPATCH();
fmuli:
    LOG("Im fmuli");
    accum_.as_double *= instr->imm.as_double;
    DISPATCH();
div:
    accum_.as_int /= frame->GetRegister(instr->reg).as_int;
    LOG("Im div");
    DISPATCH();
divi:
    accum_.as_int /= instr->imm.as_int;
    LOG("Im divi");
    DISPATCH();
fdiv:
    LOG("Im fdiv");
    accum_.as_double /= frame->GetRegister(instr->reg).as_double;
    DISPATCH();
fdivi:
    LOG("Im fdivi");
    accum_.as_double /= instr->imm.as_double;
    DISPATCH();
ldastr:
    LOG("Im ldastr");
    accum_.as_obj = instr->imm.as_obj;
    DISPATCH();
staobj:
    LOG("Im staobj");
    frame->GetRegister(instr->reg) = accum_;
    DISPATCH();
call:
    LOG("Im call");
    FrameEntrypoint(bytecode.GetMethod(instr->imm.as_int));
    (*pc)++;
    frame = GetCurrentFrame();
    frame->SetupContext(&pc, &instr);
    goto *dispatch_table[instr->type];
ret:
    LOG("Im ret");
    FrameEndpoint();
    frame = GetCurrentFrame();
    // return from start entrypoint
    if (UNLIKELY(frame == nullptr)) {
        goto exit;
    }
    frame->SetupContext(&pc, &instr);
    goto *dispatch_table[instr->type];
callintrinsic:
    proto_type = instr->proto->GetType();
    handler = instr->proto->GetHandler();
    reg = instr->proto->GetReg();

    switch (proto_type) {
        case Proto::HANDLE_VOID_F64:
            reinterpret_cast<void (*)(double)>(handler)(frame->GetRegister(reg).as_double);
            break;
        case Proto::HANDLE_VOID_OBJ:
            LOG("Im HANDLE_VOID_OBJ");
            reinterpret_cast<void (*)(uintptr_t)>(handler)(frame->GetRegister(reg).as_obj);
            break;
        case Proto::HANDLE_F64_VOID:
            accum_.as_double = reinterpret_cast<double (*)()>(handler)();
            break;
        case Proto::HANDLE_F64_F64:
            accum_.as_double = reinterpret_cast<double (*)(double)>(handler)(frame->GetRegister(reg).as_double);
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
