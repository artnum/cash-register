#include "include/widget_list.h"
#include <SDL3/SDL_assert.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_stdinc.h>

static CRWidgetList *free_list = NULL;

static CRWidgetList *_get_new_list_item() {
  CRWidgetList *item = NULL;
  if (free_list) {
    item = free_list;
    free_list = item->next;
    if (free_list) {
      free_list->previous = NULL;
    }

    item->previous = NULL;
    item->next = NULL;
    item->w = NULL;
  } else {
    item = SDL_calloc(1, sizeof(*item));
  }
  return item;
}
void widget_list_free(CRWidgetList *list) {
  if (!list) {
    return;
  }
  if (free_list) {
    for (CRWidgetList *item = list; item;) {
      CRWidgetList *next = item->next;
      item->w = NULL;
      item->previous = NULL;
      item->next = free_list;
      free_list->previous = item;
      free_list = item;
      item = next;
    }
  } else {
    free_list = list;
    for (CRWidgetList *item = list; item; item = item->next) {
      item->w = NULL;
    }
  }
}

bool widget_list_append(CRWidgetList **list, CRWidget *widget) {
  SDL_assert(list != NULL);
  SDL_assert(widget != NULL);

  /* don't happen twice */
  for (CRWidgetList *i = *list; i; i = i->next) {
    if (i->w->id == widget->id) {
      return true;
    }
  }

  CRWidgetList *item = _get_new_list_item();
  if (!item) {
    return false;
  }

  item->w = widget;
  item->previous = NULL;
  item->next = NULL;
  if (*list) {
    item->next = *list;
    (*list)->previous = item;
    *list = item;
  } else {
    *list = item;
  }
  return true;
}
