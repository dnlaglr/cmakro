#ifndef makro_object
#define makro_object

#include "common.h"
#include "value.h"

#define OBJECT_TYPE(value) (AS_OBJECT(value)->type)

#define IS_STRING(value) isObjectType(value, OBJECT_STRING)

#define AS_STRING(value) ((ObjectString*)AS_OBJECT(value))
#define AS_CSTRING(value) (((ObjectString*)AS_OBJECT(value))->chars)

typedef enum {
  OBJECT_STRING,
} ObjectType;

struct Object {
  ObjectType type;
  struct Object* next;
};

struct ObjectString {
  Object object;
  int length;
  char* chars;
};

ObjectString* takeString(char* chars, int length);
ObjectString* copyString(const char* chars, int length);
void printObject(Value value);

static inline bool isObjectType(Value value, ObjectType type) {
  return IS_OBJECT(value) && AS_OBJECT(value)->type == type;
}

#endif
