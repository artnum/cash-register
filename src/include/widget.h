#ifndef WIDGET_H__
#define WIDGET_H__

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

  union {
    struct {
      bool created : 1;
      bool pressed : 1;
      bool released : 1;
      bool clicked : 1;
      bool focused : 1;
    };
    uint32_t raw;
  } state;
  uint32_t previous_state;

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

CRWidget *widget_new(void *_app, CRWidget *parent, enum CRWidgetTypes type,
                     void *params);
void widget_render(void *_app, CRWidget *widget, bool parent_rendered);
void widget_trigger(void *_app, int what, float x, float y);
CRWidgetList *widget_get(void *_app, float x, float y);
bool widget_intersect(void *_app, CRWidget *w, float x, float y);
void widget_free_list(void *_app, CRWidgetList *list);
#endif /* WIDGET_H__ */
