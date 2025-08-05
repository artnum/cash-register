#ifndef INPUT_H__
#define INPUT_H__
#include "color.h"
#include "cr.h"
#include "widget.h"
#include <SDL3/SDL_timer.h>

typedef struct {
  CRWidget w;
  enum Color color;
  enum Color border_color;
  enum Color text_color;
  char *content;
  bool cursor_blink_state;
  SDL_TimerID timer;
} CRInput;

CRInput *input_new();
void input_render(void *_app, void *_w);
#endif /* INPUT_H__ */
