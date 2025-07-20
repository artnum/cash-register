#ifndef WIDGET_H__
#define WIDGET_H__

#include "common.h"
#include "widget_list.h"
#include <SDL3/SDL_stdinc.h>

#define widget_is_visible(w) ((w)->state.active == true)
#define widget_has_changed(w) ((w)->state.raw != (w)->previous_state.raw)
#define widget_can_render(w) (widget_has_changed(w) && (w)->state.active)
#define widget_can_trigger(w) (widget_has_changed(w) && (w)->trigger)
#define widget_trigger(w, app)                                                 \
  do {                                                                         \
    if ((w)->trigger)                                                          \
      (w)->trigger((app), (w));                                                \
  } while (0)

#define widget_set_focus(w) ((w)->state.focused = true)
#define widget_unset_focus(w) ((w)->state.focused = false)

CRWidget *widget_new(void *_app, CRWidget *parent, enum CRWidgetTypes type,
                     void *params);
void widget_render(void *_app, CRWidget *widget, bool parent_rendered);
CRWidgetList *widget_get(void *_app, float x, float y);
bool widget_intersect(void *_app, CRWidget *w, float x, float y);
void widget_free_list(void *_app, CRWidgetList *list);
#endif /* WIDGET_H__ */
