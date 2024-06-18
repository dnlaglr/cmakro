#ifndef makro_vm
#define makro_vm

#include "object.h"
#include "value.h"
#include "table.h"

#define FRAME_MAX 64
#define STACK_MAX (FRAME_MAX + UINT8_COUNT)

typedef struct {
  ObjectClosure* closure;
  uint8_t* ip;
  Value* slots;
} CallFrame;

typedef struct {
  CallFrame frames[FRAME_MAX];
  int frameCount;

  Value stack[STACK_MAX];
  Value* stackTop;
  Table globals;
  Table strings;
  ObjectUpvalue* openUpvalues;
  
  size_t bytesAllocated;
  size_t nextGC;
  Object* objects;
  int grayCount;
  int grayCapacity;
  Object** grayStack;
} VM;

typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR
} InterpretResult;

extern VM vm;

void initVM();
void freeVM();

InterpretResult interpret(const char* source);

void push(Value value);
Value pop();

#endif
