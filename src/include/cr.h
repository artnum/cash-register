#ifndef CR_H__
#define CR_H__
#include "widget.h"
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdio.h>

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
  CRWidgetList *current;
} CRApp;

#endif /* CR_H__ */
