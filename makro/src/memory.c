#include <stdlib.h>

#include "memory.h"
#include "vm.h"

void* reallocate(void* pointer, size_t oldSize, size_t newSize) {
  if (newSize == 0) {
    free(pointer);
    return NULL;
  }

  void* result = realloc(pointer, newSize);
  if (result == NULL) exit(1);
  return result;
}

static void freeObject(Object* object) {
  switch (object->type) {
  case OBJECT_STRING: {
    ObjectString* string = (ObjectString*)object;
    FREE_ARRAY(char, string->chars, string->length + 1);
    FREE(ObjectString, object);
    break;
  }
  }
}

void freeObjects() {
  Object* object = vm.objects;
  while (object != NULL) {
    Object* next = object->next;
    freeObject(object);
    object = next;
  }
}