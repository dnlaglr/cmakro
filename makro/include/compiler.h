#ifndef makro_compiler
#define makro_compiler

#include "object.h"
#include "vm.h"

ObjectFunction* compile(const char* source);
void markCompilerRoots();

#endif
