#ifndef PAGE_H__
#define PAGE_H__

#include "color.h"
#include "widget.h"

typedef struct {
  char *name;
} CRPageParams;

typedef struct {
  CRWidget w;
  enum Color background;
  void (*render)(void *, void *);
} CRPage;

CRPage *page_new(void *_app, void *_params);
#endif /* PAGE_H__ */
