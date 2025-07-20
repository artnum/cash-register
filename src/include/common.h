#ifndef COMMON_H__
#define COMMON_H__

#include <stdbool.h>
#include <stdint.h>

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

typedef struct s_CRWidgetList CRWidgetList;
struct s_CRWidgetList {
  CRWidget *w;
  CRWidgetList *next;
  CRWidgetList *previous;
};

#endif /* COMMON_H__ */
