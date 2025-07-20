#ifndef WIDGET_H__
#define WIDGET_H__

#include "widget_list.h"
#include <SDL3/SDL_stdinc.h>

enum CRWidgetTypes {
  WidgetRoot = 1,
  WidgetPage,
  WidgetInput,
  WidgetButton,

  ___WidgetMAX__
};

enum CRWidgetStates {
  WidgetNormalState = 0,
  WidgetPressedState,
  WidgetActiveState,
  WidgetFocusSate,

  ___WidgetMAXStates__
};

#define widget_is_visible(w) ((w)->state.active == true)
#define widget_has_changed(w) ((w)->state.raw != (w)->previous_state.raw)
#define widget_can_render(w) (widget_has_changed(w) && (w)->state.active)
#define widget_can_trigger(w) (widget_has_changed(w) && (w)->trigger)
#define widget_trigger(w, app)                                                 \
  do {                                                                         \
    (w)->trigger((app), (w));                                                  \
  } while (0)

union u_CRWidgetState {
  struct {
    bool created : 1;
    bool pressed : 1;
    bool released : 1;
    bool clicked : 1;
    bool focused : 1;
    bool active : 1;
  };
  uint32_t raw;
};

static const union u_CRWidgetState CR_WIDGET_CREATED_STATE = {.active = true,
                                                              .created = true};
static const union u_CRWidgetState CR_WIDGET_DEFAULT_STATE = {.active = true};

#define widget_reset_state(w) ((w)->state.raw &= CR_WIDGET_DEFAULT_STATE.raw)
typedef struct s_CRWidget CRWidget;
struct s_CRWidget {
  enum CRWidgetTypes type;
  int id;
  bool rendered;
  float x;
  float y;
  float width;
  float height;
  CRWidget *parent;
  CRWidget **children;
  int children_size;
  int children_count;

  union u_CRWidgetState state;
  union u_CRWidgetState previous_state;

  void (*trigger)(void *, void *);
  void (*render)(void *, void *);
  void (*pressed)(void *, void *);
  void (*click)(void *, void *);
};

CRWidget *widget_new(void *_app, CRWidget *parent, enum CRWidgetTypes type,
                     void *params);
void widget_render(void *_app, CRWidget *widget, bool parent_rendered);
CRWidgetList *widget_get(void *_app, float x, float y);
bool widget_intersect(void *_app, CRWidget *w, float x, float y);
void widget_free_list(void *_app, CRWidgetList *list);
#endif /* WIDGET_H__ */
