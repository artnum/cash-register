#include "include/registry.h"
#include "include/widget.h"
#include <SDL3/SDL_assert.h>
#include <SDL3/SDL_stdinc.h>
#include <xxhash.h>

#define XXH_SEED 0
void registry_init(CRRegistry *r) {}

void registry_destroy(CRRegistry *r) {
  for (int i = 0; i < CR_REGISTRY_TABLE_SIZE; i++) {
    CRRegistryCell *current = r->table[i], *next = NULL;
    while (current) {
      next = current->next;
      SDL_free(current->name);
      SDL_free(current);
      current = next;
    }
    r->table[i] = NULL;
  }
}

int registry_register(CRRegistry *r, const char *name, CRWidget *widget) {
  SDL_assert(r != NULL);
  SDL_assert(name != NULL);
  SDL_assert(widget != NULL);

  Uint32 idx = XXH32(name, SDL_strlen(name), XXH_SEED);
  Uint32 place = idx % CR_REGISTRY_TABLE_SIZE;
  CRRegistryCell *cell = SDL_calloc(1, sizeof(*cell));

  cell->name = SDL_strdup(name);
  cell->idx = idx;
  cell->widget = widget;

  if (!r->table[place]) {
    r->table[place] = cell;
  } else {
    CRRegistryCell *root = r->table[place];
    while (root->next) {
      root = root->next;
    }
    root->next = cell;
  }
  return 0;
}

CRWidget *registry_get(CRRegistry *r, const char *name) {
  SDL_assert(r != NULL);
  SDL_assert(name != NULL);
  Uint32 idx = XXH32(name, SDL_strlen(name), XXH_SEED);
  Uint32 place = idx % CR_REGISTRY_TABLE_SIZE;

  CRWidget *w = NULL;
  if (r->table[place]) {
    CRRegistryCell *root;
    while (root && SDL_strcmp(root->name, name) != 0) {
      root = root->next;
    }
    if (root) {
      w = root->widget;
    }
  }
  return w;
}

CRWidget *registry_remove(CRRegistry *r, const char *name) {
  SDL_assert(r != NULL);
  SDL_assert(name != NULL);

  Uint32 idx = XXH32(name, SDL_strlen(name), XXH_SEED);
  Uint32 place = idx % CR_REGISTRY_TABLE_SIZE;

  CRWidget *w = NULL;
  if (r->table[place]) {
    CRRegistryCell *current = r->table[place], *previous = NULL;
    while (current && SDL_strcmp(current->name, name) != 0) {
      previous = current;
      current = current->next;
    }
    if (current) {
      w = current->widget;
      SDL_free(current->name);
      if (previous == NULL) {
        r->table[place] = current->next;
      } else {
        previous->next = current->next;
      }
      SDL_free(current);
    }
  }

  return w;
}
