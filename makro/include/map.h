#ifndef makro_map
#define makro_map

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
} Map;

void initMap(Map* map);
void freeMap(Map* map);
bool mapSet(Map* map, ObjectString* key, Value value);
bool mapGet(Map* map, ObjectString* key, Value* value);
bool mapDelete(Map* map, ObjectString* key);
void mapAddAll(Map* from, Map* to);
ObjectString* mapFindString(Map* map, const char* chars, int length, uint32_t hash);

#endif