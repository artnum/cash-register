#ifndef INPUT_H__
#define INPUT_H__
#include "color.h"
#include "cr.h"
#include "widget.h"

typedef struct {
  CRWidget w;
  enum Color color;
  enum Color border_color;
  enum Color text_color;
  char *content;
} CRInput;

CRInput *input_new();
void input_render(void *_app, void *_w);
#endif /* INPUT_H__ */
