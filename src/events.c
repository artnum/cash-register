#include "include/events.h"
#include "include/cr.h"
#include "include/widget.h"
#include "include/widget_list.h"
#include <SDL3/SDL_log.h>

void events_mouse_down(CRApp *app, float x, float y) {
  SDL_Log("MOUSE DOWN STARTED\n");
  CRWidgetList *list = widget_get(app, x, y);
  for (CRWidgetList *item = list; item; item = item->next) {
    item->w->state.pressed = true;
    SDL_Log("[MOUSE_DOWN] %d : prev %u, now %u\n", item->w->id,
            item->w->previous_state.raw, item->w->state.raw);
    if (widget_can_trigger(item->w)) {
      widget_trigger(item->w, app);
    }
  }
  if (app->current[CR_MOUSE_PRESS_QUEUE]) {
    widget_list_free(app->current[CR_MOUSE_PRESS_QUEUE]);
  }
  app->current[CR_MOUSE_PRESS_QUEUE] = list;
}

void events_mouse_up(CRApp *app, float x, float y) {
  SDL_Log("MOUSE UP STARTED\n");
  CRWidgetList *to_trigger = NULL;
  if (app->current[CR_MOUSE_CLICK_QUEUE]) {
    for (CRWidgetList *item = app->current[CR_MOUSE_CLICK_QUEUE]->next; item;
         item = item->next) {
      item->w->state.pressed = false;
      item->w->state.clicked = false;
    }
    widget_list_free(app->current[CR_MOUSE_CLICK_QUEUE]);
    app->current[CR_MOUSE_CLICK_QUEUE] = NULL;
  }

  CRWidgetList *list = widget_get(app, x, y);
  if (list) {
    for (CRWidgetList *item = list; item; item = item->next) {
      if (item->w->state.pressed) {
        item->w->state.clicked = true;
        item->w->state.pressed = false;
      }
      item->w->state.released = true;

      SDL_Log("[MOUSE_UP] %d : prev %u, now %u\n", item->w->id,
              item->w->previous_state.raw, item->w->state.raw);
      /* trigger a state change */
      if (widget_can_trigger(item->w)) {
        widget_list_append(&to_trigger, item->w);
      }
    }
    app->current[CR_MOUSE_CLICK_QUEUE] = list;
  }

  if (app->current[CR_MOUSE_PRESS_QUEUE]) {
    CRWidgetList *previous = app->current[CR_MOUSE_PRESS_QUEUE];
    for (CRWidgetList *item = app->current[CR_MOUSE_PRESS_QUEUE]->next; item;
         item = item->next) {
      item->w->state.pressed = false;

      SDL_Log("%d : prev %u, now %u\n", item->w->id,
              item->w->previous_state.raw, item->w->state.raw);
      /* trigger a state change */
      if (widget_can_trigger(item->w)) {
        widget_list_append(&to_trigger, item->w);
      }
    }
    widget_list_free(app->current[CR_MOUSE_PRESS_QUEUE]);
  }
  widget_list_foreach(to_trigger, widget_trigger, app);
  widget_list_free(to_trigger);
  app->current[CR_MOUSE_PRESS_QUEUE] = NULL;
}

void event_focuse(CRApp *app, float x, float y) {
  CRWidgetList *list = widget_get(app, x, y);
}
