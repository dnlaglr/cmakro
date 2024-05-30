#ifndef makro_compiler
#define makro_compiler

#include "object.h"
#include "vm.h"

bool compile(const char* source, Chunk* chunk);

#endif
