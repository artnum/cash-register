#ifndef BUTTON_H__
#define BUTTON_H__
#include "color.h"
#include "cr.h"
#include "widget.h"

typedef struct {
  CRWidget w;
  float x;
  float y;
  float width;
  float height;
  struct {
    enum Color background;
    enum Color border;
    enum Color text;
  } colors[___WidgetMAXStates__];
  char *text;
} CRButton;

CRButton *button_new();
void button_render(void *_app, void *_w);
#endif /* BUTTON_H__ */
