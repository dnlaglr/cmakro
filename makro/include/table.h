#ifndef makro_table
#define makro_table

#include "common.h"
#include "value.h"

typedef struct {
  ObjectString* key;
  Value value;
} Entry;

typedef struct {
  int count;
  int capacity;
  Entry* entries;
} Table;

void initTable(Table* table);
void freeTable(Table* table);
bool tableSet(Table* table, ObjectString* key, Value value);
bool tableGet(Table* table, ObjectString* key, Value* value);
bool tableDelete(Table* table, ObjectString* key);
void tableAddAll(Table* from, Table* to);
ObjectString* tableFindString(Table* table, const char* chars, int length, uint32_t hash);

#endif
