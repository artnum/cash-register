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

  ___WidgetMAXStates__
};

typedef struct s_CRWidget CRWidget;
struct s_CRWidget {
  enum CRWidgetTypes type;
  bool rendered;
  float x;
  float y;
  float width;
  float height;
  CRWidget *parent;
  int children_size;
  int children_count;
  CRWidget **children;
  enum CRWidgetStates state;
  void (*mouse_down)(void *, void *);
};

typedef struct s_CRWidgetList CRWidgetList;
struct s_CRWidgetList {
  CRWidget *w;
  CRWidgetList *next;
  CRWidgetList *previous;
};

CRWidget *widget_new(void *_app, CRWidget *parent, enum CRWidgetTypes type);
void widget_render(void *_app, CRWidget *widget, bool parent_rendered);
void widget_trigger(void *_app, int what, float x, float y);
CRWidgetList *widget_get(void *_app, float x, float y);
bool widget_intersect(void *_app, CRWidget *w, float x, float y);
#endif /* WIDGET_H__ */
