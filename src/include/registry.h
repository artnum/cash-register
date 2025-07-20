#ifndef REGISTRY_H__
#define REGISTRY_H__

#include "widget.h"
#include <SDL3/SDL_stdinc.h>
#define CR_REGISTRY_TABLE_SIZE 97
typedef struct s_CRRegistryCell CRRegistryCell;

struct s_CRRegistryCell {
  CRWidget *widget;
  Uint32 idx;
  char *name;
  CRRegistryCell *next;
};

typedef struct {
  CRRegistryCell *table[CR_REGISTRY_TABLE_SIZE];
} CRRegistry;

void registry_init(CRRegistry *r);
void registry_destroy(CRRegistry *r);
int registry_register(CRRegistry *r, const char *name, CRWidget *widget);
CRWidget *registry_get(CRRegistry *r, const char *name);
CRWidget *registry_remove(CRRegistry *r, const char *name);
#endif /* REGISTRY_H__ */
