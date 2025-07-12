#include <SDL3/SDL_error.h>
#include <stdio.h>
#define SDL_MAIN_USE_CALLBACKS

#include <SDL3/SDL_main.h>

#include "include/button.h"
#include "include/color.h"
#include "include/cr.h"
#include "include/widget.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3_ttf/SDL_ttf.h>

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
  CRApp *app = SDL_calloc(1, sizeof(*app));
  if (!app) {
    return SDL_APP_FAILURE;
  }
  *appstate = app;

  app->border = 0.8;
  app->px = 25.0;
  app->font = 18.0;

  SDL_SetAppMetadata("CR", "0.0.0", "ch.artnum.cr");
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer("CR", 750, 500, 0, &app->window, &app->renderer);
  SDL_SetRenderTarget(app->renderer, NULL);
  SDL_RenderClear(app->renderer);

  TTF_Init();
  app->main_font = TTF_OpenFont("fonts/NotoSans-SemiBold.ttf", app->font);
  app->input_font = TTF_OpenFont("fonts/RobotoMono-SemiBold.ttf", app->font);
  TTF_SetFontHinting(app->main_font, TTF_HINTING_LIGHT_SUBPIXEL);

  widget_new(app, NULL, WidgetRoot);
  app->root->x = 0;
  app->root->y = 0;
  app->root->width = 750 / app->px;
  app->root->height = 500 / app->px;
  CRWidget *n = widget_new(app, app->root, WidgetButton);
  n->x = 0;
  n->y = 0;
  n->height = 1;
  n->width = 10;
  ((CRButton *)n)->text = "Bouton";
  ((CRButton *)n)->colors[WidgetNormalState].background = COLOR_LINEN;
  ((CRButton *)n)->colors[WidgetNormalState].text = COLOR_BLACK;
  ((CRButton *)n)->colors[WidgetNormalState].border = COLOR_GOLDENROD;
  ((CRButton *)n)->colors[WidgetPressedState].background = COLOR_CORAL;
  ((CRButton *)n)->colors[WidgetPressedState].text = COLOR_BLACK;
  ((CRButton *)n)->colors[WidgetPressedState].border = COLOR_GOLDENROD;

  return SDL_APP_CONTINUE;
}

char *input_content = "";
SDL_AppResult SDL_AppIterate(void *appstate) {
  CRApp *app = (CRApp *)appstate;

  const int target_fps = 30;
  const Uint32 frame_time_ms = 1000 / target_fps;
  Uint32 frame_start = SDL_GetTicks();

  widget_render(app, NULL, false);

  SDL_RenderPresent(app->renderer);

  Uint32 frame_duration = SDL_GetTicks() - frame_start;
  if (frame_duration < frame_time_ms) {
    SDL_Delay(frame_time_ms - frame_duration);
  }

  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {}
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  CRApp *app = (CRApp *)appstate;

  app->mouse_x = 0;
  app->mouse_y = 0;
  switch (event->type) {
  case SDL_EVENT_MOUSE_BUTTON_DOWN: {
    CRWidgetList *list = widget_get(app, event->motion.x, event->motion.y);
    for (CRWidgetList *item = list->next; item; item = item->next) {
      item->w->state = WidgetPressedState;
      item->w->rendered = false;
    }
    app->current = list;
    break;
  }
  case SDL_EVENT_MOUSE_BUTTON_UP: {
    if (app->current) {
      for (CRWidgetList *item = app->current->next; item;) {
        CRWidgetList *next = item->next;
        item->w->state = WidgetNormalState;
        item->w->rendered = false;
        SDL_free(item);
        item = next;
      }
      SDL_free(app->current);
      app->current = NULL;
    }
    break;
  }
  case SDL_EVENT_MOUSE_MOTION: {
    if (app->current) {
      CRWidgetList *rm = NULL;
      for (CRWidgetList *item = app->current->next; item;) {
        CRWidgetList *next = item->next;
        if (!widget_intersect(app, item->w, event->motion.x, event->motion.y)) {
          item->previous->next = NULL;
          item->previous = NULL;
          rm = item;
          break;
        }
        item = next;
      }
      for (CRWidgetList *item = rm; item;) {
        CRWidgetList *next = item->next;
        item->w->state = WidgetNormalState;
        item->w->rendered = false;
        SDL_free(item);
        item = next;
      }
      if (!app->current->next) {
        SDL_free(app->current);
        app->current = NULL;
      }
    }
    break;
  }
  }
  return SDL_APP_CONTINUE;
}
