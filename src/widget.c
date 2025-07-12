#include "include/widget.h"
#include "include/button.h"
#include "include/cr.h"
#include "include/input.h"
#include <SDL3/SDL_assert.h>
#include <SDL3/SDL_stdinc.h>

#define WIDGET_CHILDREN_CHUNK 50
void widget_render(void *_app, CRWidget *widget, bool parent_rendered) {
  SDL_assert(_app != NULL);
  CRApp *app = _app;
  if (widget == NULL) {
    widget = app->root;
  }
  switch (widget->type) {
  case WidgetPage:
  case WidgetRoot:
    for (int i = 0; i < widget->children_count; i++) {
      widget_render(app, widget->children[i], false);
    }
    break;
  case WidgetInput:
    if (!widget->rendered || parent_rendered) {
      input_render(app, (CRInput *)widget);
      widget->rendered = true;
    }
  case WidgetButton:
    if (!widget->rendered || parent_rendered) {
      button_render(app, (CRButton *)widget);
      widget->rendered = true;
    }
    break;
  default:
    break;
  }
}

void _widget_grow_children(CRWidget *w) {
  SDL_assert(w != NULL);
  CRWidget *tmp =
      SDL_realloc(w->children, (w->children_size + WIDGET_CHILDREN_CHUNK) *
                                   sizeof(*w->children));
  if (!tmp) {
    return;
  }
  //  memset(tmp + w->children_size, 0, sizeof(*tmp) * WIDGET_CHILDREN_CHUNK);
  w->children_size += WIDGET_CHILDREN_CHUNK;
  w->children = (CRWidget **)tmp;
}

CRWidget *_widget_new_generic(enum CRWidgetTypes type) {
  SDL_assert(type < ___WidgetMAX__);
  CRWidget *n = SDL_calloc(1, sizeof(*n));
  if (n) {
    n->type = type;
  }
  return n;
}

void widget_insert_child(CRWidget *parent, CRWidget *child) {
  if (parent->children_count + 1 >= parent->children_size) {
    _widget_grow_children(parent);
  }
  parent->children[parent->children_count] = child;
  parent->children_count++;
  child->parent = parent;
}

CRWidget *widget_new(void *_app, CRWidget *parent, enum CRWidgetTypes type) {
  SDL_assert(_app != NULL);
  CRApp *app = _app;
  CRWidget *n = NULL;
  switch (type) {
  case WidgetRoot: {
    n = _widget_new_generic(type);
    app->root = n;
    n->rendered = false;
    break;
  }
  case WidgetInput: {
    n = (CRWidget *)input_new();
    widget_insert_child(parent, n);
    n->rendered = false;
    break;
  }
  case WidgetButton: {
    n = (CRWidget *)button_new();
    widget_insert_child(parent, n);
    n->rendered = false;
    break;
  }

  default:
    break;
  }
  n->state = WidgetNormalState;
  n->type = type;
  return n;
}

bool widget_intersect(void *_app, CRWidget *w, float x, float y) {
  SDL_assert(_app != NULL);
  CRApp *app = _app;
  return ((app->px * w->x) <= x) && (((w->x + w->width) * app->px) >= x) &&
         ((app->px * w->y) <= y) && (((w->y + w->height) * app->px) >= y);
}

CRWidgetList *widget_get(void *_app, float x, float y) {
  SDL_assert(_app != NULL);
  CRApp *app = _app;
  CRWidget *w = app->root;
  CRWidgetList *root = SDL_calloc(1, sizeof(*root));
  if (!root) {
    return NULL;
  }
  root->w = w;
  CRWidgetList *item = root;
  while (w->children_count > 0) {
    int found = 0;
    for (int i = 0; i < w->children_count; i++) {
      CRWidget *_w = w->children[i];
      if (widget_intersect(_app, _w, x, y)) {
        item->next = SDL_calloc(1, sizeof(*item));
        if (!item->next) {
          return root;
        }
        item->next->w = _w;
        item->next->previous = item;
        item = item->next;
      }
      w = _w;
      found = 1;
    }
    if (!found) {
      break;
    }
  }
  return root;
}
