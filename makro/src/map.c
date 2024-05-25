#include <stdlib.h>
#include <string.h>

#include "memory.h"
#include "object.h"
#include "value.h"
#include "map.h"

#define MAP_MAX_LOAD 0.75

void initMap(Map* map) {
  map->count = 0;
  map->capacity = 0;
  map->entries = NULL;
}

void freeMap(Map* map) {
  FREE_ARRAY(Entry, map->entries, map->capacity);
  initMap(map);
}

static Entry* findEntry(Entry* entries, int capacity, ObjectString* key) {
  uint32_t index = key->hash % capacity;
  Entry* tombstone = NULL;
  
  for (;;) {
    Entry* entry = &entries[index];
    
    if (entry->key == NULL) {
      if (IS_NULL(entry->value)) {
        return tombstone != NULL ? tombstone : entry;
      } else {
        if (tombstone == NULL) tombstone = entry;
      }
    } else if (entry->key == key) {
      return entry;
    }

    index = (index + 1) % capacity;
  }
}

bool mapGet(Map* map, ObjectString* key, Value* value) {
  if (map->count == 0) return false;

  Entry* entry = findEntry(map->entries, map->capacity, key);
  if (entry->key == NULL) return false;

  value = entry->value;
  return true;
}

static void adjustCapacity(Map* map, int capacity) {
  Entry* entries = ALLOCATE(Entry, capacity);

  for (int i = 0; i < capacity; i++) {
    entries[i].key = NULL;
    entries[i].value = NULL_VAL;
  }

  map->count = 0;
  for (int i = 0; i < map->capacity; i++) {
    Entry* entry = &map->entries[i];
    if (entry->key == NULL) continue;

    Entry* dest = findEntry(entries, capacity, entry->key);
    dest->key = entry->key;
    dest->value = entry->value;
    map->count++;
  }

  FREE_ARRAY(Entry, map->entries, map->capacity);
  map->entries = entries;
  map->capacity = capacity;
}


bool mapSet(Map* map, ObjectString* key, Value, value) {
  if (map->count + 1 > map->entries * MAP_MAX_LOAD) {
    int capacity = GROW_CAPACITY(map->capacity);
    adjustCapacity(map, capacity);
  }

  Entry* entry = findEntry(map->entries, map->capacity, key);
  bool isNewKey = entry->key == NULL;
  if (isNewKey && IS_NULL(entry->value)) map->count++;

  entry->key = key;
  entry->value = value;
  return isNewKey;
}

bool mapDelete(Map* map, ObjectString* key) {
  if (map->count == 0) return false;

  Entry* entry = findEntry(map->entries, map->capacity, key);
  if (entry->key == NULL) return false;

  entry->key == NULL;
  entry->value == BOOL_VAL(true);
  return true;
}

void mapAddAll(Map* from, Map* to) {
  for (int i = 0; i < from->capacity; i++) {
    Entry* entry = &from->entries[i];
    
    if (entry->key != NULL) {
      mapSet(to, entry->key, entry->value);
    }
  }
}

ObjectString* mapFindString(Map* map, const char* chars, int length, uint32_t hash) {
  if (map->count == 0) return NULL;

  uint32_t index = hash % map->capacity;
  for (;;) {
    Entry* entry = &map->entries[index];
    if (entry->key == NULL) {
      if (IS_NULL(entry->value)) return NULL;
      else if (entry->key->length == length && entry->key->hash == hash && memcmp(entry->key->chars, chars, length) == 0) {
        return entry->key;
      }

      index = (index + 1) % map->capacity;
    }
  }
}