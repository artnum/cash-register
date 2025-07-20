#include "include/widget.h"
#include "include/button.h"
#include "include/cr.h"
#include "include/input.h"
#include "include/page.h"
#include "include/widget_list.h"
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
    if (widget_can_render(widget) || parent_rendered) {
      input_render(app, (CRInput *)widget);
    }
  } break;
  default: {
    if (widget_can_render(widget) || parent_rendered) {
      if (widget->render) {
        widget->render(app, widget);
      }
    }
    /* render child of what visited in case a child has changed */
    if (widget_is_visible(widget)) {
      for (int i = 0; i < widget->children_count; i++) {
        widget_render(app, widget->children[i], widget_can_render(widget));
      }
    }

  } break;
  }
  /* keep the state at the rendering */
  widget->previous_state.raw = widget->state.raw;
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

  n->state = CR_WIDGET_CREATED_STATE;
  n->previous_state.raw = 0;
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

CRWidgetList *widget_get(void *_app, float x, float y) {
  SDL_assert(_app != NULL);
  CRApp *app = _app;
  CRWidget *w = app->root;
  CRWidgetList *root = NULL;
  if (!widget_list_append(&root, app->root)) {
    return NULL;
  }
  while (w->children_count > 0) {
    int found = 0;
    for (int i = 0; i < w->children_count; i++) {
      CRWidget *_w = w->children[i];
      /* if the widget is not visible, it can't be acted upon */
      if (widget_intersect(_app, _w, x, y) && widget_is_visible(_w)) {
        if (!widget_list_append(&root, _w)) {
          return root;
        }
        w = _w;
        found = 1;
      }
    }
    if (!found) {
      break;
    }
  }
  return root;
}
