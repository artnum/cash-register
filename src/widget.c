#include "include/widget.h"
#include "include/button.h"
#include "include/cr.h"
#include "include/input.h"
#include "include/page.h"
#include <SDL3/SDL_assert.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_stdinc.h>

#define WIDGET_CHILDREN_CHUNK 50
void widget_render(void *_app, CRWidget *widget, bool parent_rendered) {
  SDL_assert(_app != NULL);
  CRApp *app = _app;
  if (widget == NULL) {
    widget = app->root;
  }
  switch (widget->type) {
  case WidgetRoot:
    for (int i = 0; i < widget->children_count; i++) {
      widget_render(app, widget->children[i], false);
    }
    break;
  case WidgetInput: {
    if (widget->state.raw != widget->previous_state || parent_rendered) {
      input_render(app, (CRInput *)widget);
    }
  } break;
  default: {
    if (widget->state.raw != widget->previous_state || parent_rendered) {
      if (widget->render) {
        widget->render(app, widget);
      }
    }
    for (int i = 0; i < widget->children_count; i++) {
      widget_render(app, widget->children[i],
                    widget->state.raw == widget->previous_state);
    }
  } break;
  }
  /* keep the state at the rendering */
  widget->previous_state = widget->state.raw;
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

CRWidget *widget_new(void *_app, CRWidget *parent, enum CRWidgetTypes type,
                     void *params) {
  SDL_assert(_app != NULL);
  CRApp *app = _app;
  CRWidget *n = NULL;
  switch (type) {
  case WidgetRoot: {
    n = _widget_new_generic(type);
    app->root = n;
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
    break;
  }
  case WidgetPage: {
    n = (CRWidget *)page_new(app, params);
    n->x = parent->x;
    n->y = parent->y;
    n->width = parent->width;
    n->height = parent->height;
    n->rendered = false;
    widget_insert_child(parent, n);
    break;
  }
  default:
    break;
  }
  n->state.raw = false;
  n->previous_state = false;
  n->state.created = true;
  n->type = type;
  n->id = ++app->widgets_id;
  return n;
}

bool widget_intersect(void *_app, CRWidget *w, float x, float y) {
  SDL_assert(_app != NULL);
  CRApp *app = _app;
  return ((app->px * w->x) <= x) && (((w->x + w->width) * app->px) >= x) &&
         ((app->px * w->y) <= y) && (((w->y + w->height) * app->px) >= y);
}

void widget_free_list(void *_app, CRWidgetList *list) {
  SDL_assert(_app != NULL);
  SDL_assert(list != NULL);
  CRApp *app = _app;

  if (app->current[CR_FREE_QUEUE]) {
    for (CRWidgetList *item = list; item;) {
      CRWidgetList *next = item->next;
      item->w = NULL;
      item->previous = NULL;
      item->next = app->current[CR_FREE_QUEUE];
      app->current[CR_FREE_QUEUE]->previous = item;
      app->current[CR_FREE_QUEUE] = item;
      item = next;
    }
  } else {
    app->current[CR_FREE_QUEUE] = list;
    for (CRWidgetList *item = list; item; item = item->next) {
      item->w = NULL;
    }
  }
}

static CRWidgetList *_get_new_list_item(CRApp *app) {
  CRWidgetList *item = NULL;
  if (app->current[CR_FREE_QUEUE]) {
    SDL_Log("new item from free list\n");
    item = app->current[CR_FREE_QUEUE];
    app->current[CR_FREE_QUEUE] = item->next;
    if (app->current[CR_FREE_QUEUE]) {
      app->current[CR_FREE_QUEUE]->previous = NULL;
    }

    item->previous = NULL;
    item->next = NULL;
    item->w = NULL;
  } else {
    SDL_Log("new item allocated\n");
    item = SDL_calloc(1, sizeof(*item));
  }

  return item;
}

CRWidgetList *widget_get(void *_app, float x, float y) {
  SDL_assert(_app != NULL);
  CRApp *app = _app;
  CRWidget *w = app->root;
  CRWidgetList *root = _get_new_list_item(app);
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
        item->next = _get_new_list_item(app);
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
