#include "include/events.h"
#include "include/common.h"
#include "include/cr.h"
#include "include/widget.h"
#include "include/widget_list.h"
#include <SDL3/SDL_log.h>

void events_mouse_down(CRApp *app, float x, float y) {
  CRWidgetList *list = widget_get(app, x, y);
  for (CRWidgetList *item = list; item; item = item->next) {
    item->w->state.pressed = true;
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
    for (CRWidgetList *item = app->current[CR_MOUSE_CLICK_QUEUE]; item;
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

      /* trigger a state change */
      if (widget_can_trigger(item->w)) {
        widget_list_append(&to_trigger, item->w);
      }
    }
    app->current[CR_MOUSE_CLICK_QUEUE] = list;
  }

  if (app->current[CR_MOUSE_PRESS_QUEUE]) {
    CRWidgetList *previous = app->current[CR_MOUSE_PRESS_QUEUE];
    for (CRWidgetList *item = app->current[CR_MOUSE_PRESS_QUEUE]; item;
         item = item->next) {
      item->w->state.pressed = false;

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

void event_focus(CRApp *app, float x, float y) {
  CRWidgetList *to_trigger = NULL;

  if (app->current[CR_FOCUS_QUEUE]) {
    for (CRWidgetList *item = app->current[CR_FOCUS_QUEUE]; item;
         item = item->next) {
      if (item->w->state.focused) {
        if (item->w->blur) {
          item->w->blur(app, item);
        }
        item->w->state.focused = false;
        widget_list_append(&to_trigger, item->w);
      }
    }
    widget_list_free(app->current[CR_FOCUS_QUEUE]);
    app->current[CR_FOCUS_QUEUE] = NULL;
  }

  CRWidgetList *list = widget_get(app, x, y);
  for (CRWidgetList *item = list; item; item = item->next) {
    if (!item->w->state.focused) {
      if (item->w->focus) {
        item->w->focus(app, item);
      }
      item->w->state.focused = true;
      widget_list_append(&to_trigger, item->w);
    }
  }
  app->current[CR_FOCUS_QUEUE] = list;

  widget_list_foreach(to_trigger, widget_trigger, app);
  widget_list_free(to_trigger);
}
