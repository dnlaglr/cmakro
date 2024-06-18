#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../include/memory.h"
#include "../include/object.h"
#include "../include/value.h"
#include "../include/table.h"
#include "../include/vm.h"

#define ALLOCATE_OBJECT(type, objectType) (type*)allocateObject(sizeof(type), objectType)

static Object* allocateObject(size_t size, ObjectType type) {
  Object* object = (Object*)reallocate(NULL, 0, size);
  object->type = type;
  object->isMarked = false;

  object->next = vm.objects;
  vm.objects = object;

  #ifdef DEBUG_LOG_GARBAGE_COLLECT
      printf("%p allocate %zu for %d\n", (void*)object, size, type);
  #endif

  return object;
}

ObjectClosure* newClosure(ObjectFunction* function) {
  ObjectUpvalue** upvalues = ALLOCATE(ObjectUpvalue*, function->upvalueCount);

  for (int i = 0; i < function->upvalueCount; i++) {
    upvalues[i] = NULL;
  }

  ObjectClosure* closure = ALLOCATE_OBJECT(ObjectClosure, OBJECT_CLOSURE);
  closure->function = function;
  closure->upvalues = upvalues;
  closure->upvalueCount = function->upvalueCount;
  return closure;
}

ObjectFunction* newFunction() {
  ObjectFunction* function = ALLOCATE_OBJECT(ObjectFunction, OBJECT_FUNCTION);
  function->arity = 0;
  function->upvalueCount = 0;
  function->name = NULL;
  initChunk(&function->chunk);
  return function;
}

ObjectNative* newNative(NativeFn function) {
  ObjectNative* native = ALLOCATE_OBJECT(ObjectNative, OBJECT_NATIVE);
  native->function = function;
  return native;
}

static ObjectString* allocateString(char* chars, int length, uint32_t hash) {
  ObjectString* string = ALLOCATE_OBJECT(ObjectString, OBJECT_STRING);
  string->length = length;
  string->chars = chars;
  string->hash = hash;

  push(OBJECT_VAL(string));
  tableSet(&vm.strings, string, NULL_VAL);
  pop();

  return string;
}

static uint32_t hashString(const char* key, int length) {
  uint32_t hash = 2166136261u;
  for (int i = 0; i < length; i++) {
    hash ^= (uint32_t)key[i];
    hash *= 16777619;
  }

  return hash;
}

ObjectString* takeString(char* chars, int length) {
  uint32_t hash = hashString(chars, length);
  ObjectString* interned = tableFindString(&vm.strings, chars, length, hash);
  if (interned != NULL) {
    FREE_ARRAY(char, chars, length + 1);
    return interned;
  }

  return allocateString(chars, length, hash);
}

ObjectString* copyString(const char* chars, int length) {
  uint32_t hash = hashString(chars, length);
  ObjectString* interned = tableFindString(&vm.strings, chars, length, hash);
  if (interned != NULL) return interned;

  char* heapChars = ALLOCATE(char, length + 1);
  memcpy(heapChars, chars, length);
  heapChars[length] = '\0';

  return allocateString(heapChars, length, hash);
}

ObjectUpvalue* newUpvalue(Value* slot) {
  ObjectUpvalue* upvalue = ALLOCATE_OBJECT(ObjectUpvalue, OBJECT_UPVALUE);
  upvalue->closed = NULL_VAL;
  upvalue->location = slot;
  upvalue->next = NULL;
  return upvalue;
}

static void printFunction(ObjectFunction* function) {
  if (function->name == NULL) {
    printf("<script>");
    return;
  }

  printf("<fn %s>", function->name->chars);
}

void printObject(Value value) {
  switch (OBJECT_TYPE(value)) {
    case OBJECT_CLOSURE:
      printFunction(AS_CLOSURE(value)->function);
      break;
    case OBJECT_FUNCTION:
      printFunction(AS_FUNCTION(value));
      break;
    case OBJECT_NATIVE:
      printf("<native fn>");
      break;
    case OBJECT_STRING:
      printf("%s", AS_CSTRING(value));
      break;
    case OBJECT_UPVALUE:
      printf("upvalue");
      break;
  }
}
