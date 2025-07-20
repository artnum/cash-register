#ifndef CR_H__
#define CR_H__
#include "registry.h"
#include "widget.h"
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdio.h>

enum CRStateQueue {
  CR_MOUSE_PRESS_QUEUE,
  CR_FOCUS_QUEUE,
  CR_MOUSE_CLICK_QUEUE,
  CR_FREE_QUEUE,
  CR_QUEUE__MAX__
};

typedef struct {
  SDL_Window *window;
  SDL_Texture *target;
  SDL_Renderer *renderer;
  float px;     /* pixel size */
  float border; /* border size in px */
  float font;   /* font size */
  TTF_Font *main_font;
  TTF_Font *input_font;

  float mouse_x;
  float mouse_y;
  CRWidget *root;
  CRWidgetList *current[CR_QUEUE__MAX__];
  CRRegistry registry;
  int widgets_id;
} CRApp;

#endif /* CR_H__ */
