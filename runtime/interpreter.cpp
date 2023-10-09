#include "runtime/interpreter.h"
#include "file/bytecode.h"

namespace mipt_vm {

void Interpreter::Interpret([[maybe_unused]] Bytecode &bytecode)
{
  static void *dispatch_table[] = {
    &&lda,      //1
    &&ldai,     //2
    &&ldastr,
    &&sta,
    &&staobj,
    &&add,      //3
    &&addi,     //4
    &&sub,      //5
    &&subi,     //6
    &&mul,      //7
    &&muli,     //8
    &&div,      //9
    &&divi,     //10
    &&IOprint,  //11
    &&IOprinti, //12
    &&IOprintString, //13
    &&IOscan,   //14
    &&exit,     //15
  }; 

  std::vector<Instruction> insns = bytecode.GetInstructions();
  RegisterManager &reg_manager = GetRegManager();
  uint64_t &pc = reg_manager.GetPc();
  uint64_t &ac = reg_manager.GetAccumulator();
  std::array<Register, RegisterCount> = ...

  #define NEXT()                     \
    pc++;                            \
    goto *dispatch_table[insns[pc].opcode];

  goto *dispatch_table[insns[pc].opcode];

sta:
  printf("Im sta\n");
  registers[insns[pc].op1] = ac;
  NEXT()
lda:
  printf("Im lda\n");
  ac = registers[insns[pc].op1];
  NEXT()
ldai:
  printf("Im ldai\n");
  ac = insns[pc].op1;
  NEXT()
add:
  printf("Im add\n");
  ac += registers[insns[pc].op1];
  NEXT()
addi:
  printf("Im addi\n");
  ac += insns[pc].op1;
  NEXT()
sub:
  printf("Im sub\n");
  ac -= registers[insns[pc].op1];
  NEXT()
subi:
  printf("Im subi\n");
  ac -= insns[pc].op1;
  NEXT()
mul:
  printf("Im mul\n");
  ac *= registers[insns[pc].op1];
  NEXT()
muli:
  printf("Im muli\n");
  ac *= insns[pc].op1;
  NEXT()
div:
  ac /= registers[insns[pc].op1];
  printf("Im div\n");
  NEXT()
divi:
  ac /= insns[pc].op1;
  printf("Im divi\n");
  NEXT()
IOprint:
  printf("%ld\n", registers[insns[pc].op1]);
  NEXT()
IOprinti:
  printf("%ld\n", insns[pc].op1);
  NEXT()
IOprintString:
  printf("%s\n", (reinterpret_cast<char *> (registers[insns[pc].op1])));
  NEXT()
IOscan:
  scanf("%ld\n", &registers[insns[pc].op1]);
  NEXT()
exit:
  //printf("Res %ld\n", registers[0]);
  return;
ldastr:
  ac = insns[pc].op1;
  NEXT();
staobj:
  registers[insns[pc].op1] = ac;
  NEXT();
}

}  // namespace mipt_vm
