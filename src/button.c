#include "include/button.h"
#include "include/color.h"
#include "include/cr.h"
#include <SDL3/SDL_assert.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdio.h>

void click(void *_app, void *_widget) {
  CRApp *app = _app;

  CRButton *button = _widget;
  CRWidget *mainpage = registry_get(&app->registry, "mainpage");
  CRWidget *secondpage = registry_get(&app->registry, "secondpage");
  SDL_Log("mainpage %p secondpage %p\n", mainpage, secondpage);
  mainpage->state.active = !mainpage->state.active;
  secondpage->state.active = !secondpage->state.active;
  SDL_Log("CLICK p %d, s %d -> %d, %d\n", mainpage->id, secondpage->id,
          mainpage->state.active, secondpage->state.active);
}
void trigger(void *_app, void *_widget) {
  CRApp *app = _app;
  CRButton *button = _widget;
  SDL_assert(app != NULL);
  SDL_assert(button != NULL);
  if (button->w.state.clicked) {
    click(app, button);
  }
}

CRButton *button_new() {
  CRButton *n = SDL_calloc(1, sizeof(*n));
  if (n) {
    n->w.type = WidgetButton;
    n->w.click = click;
    n->w.render = button_render;
    n->w.trigger = trigger;
  }
  return n;
}

void button_render(void *_app, void *_w) {
  CRApp *app = _app;
  CRButton *button = _w;

  enum CRWidgetStates s =
      button->w.state.pressed
          ? WidgetPressedState
          : (button->w.state.focused ? WidgetFocusSate : WidgetNormalState);
  if (button->colors[s].background == COLOR_NONE) {
    s = WidgetNormalState;
  }

  /* outer box, so border */
  {
    SDL_FRect rect = {app->px * button->w.x, app->px * button->w.y,
                      app->px * button->w.width, app->px * button->w.height};

    const SDL_Color *color = &COLORS[button->colors[s].border];
    SDL_SetRenderDrawColor(app->renderer, color->r, color->g, color->b,
                           color->a);
    SDL_RenderFillRect(app->renderer, &rect);
  }

  /* inner box */
  {
    SDL_FRect rect = {(app->px * button->w.x) + app->border,
                      (app->px * button->w.y) + app->border,
                      (app->px * button->w.width) - (app->border * 2),
                      (app->px * button->w.height) - (app->border * 2)};

    const SDL_Color *color = &COLORS[button->colors[s].background];
    SDL_SetRenderDrawColor(app->renderer, color->r, color->g, color->b,
                           color->a);
    SDL_RenderFillRect(app->renderer, &rect);
  }

  /* text */
  {
    const SDL_Color *color = &COLORS[button->colors[s].text];
    const SDL_Color *bg_color = &COLORS[button->colors[s].background];

    SDL_Surface *text =
        TTF_RenderText_Shaded_Wrapped(app->main_font, button->text, 0, *color,
                                      *bg_color, button->w.width * app->px);
    SDL_Texture *ttext = SDL_CreateTextureFromSurface(app->renderer, text);
    float w, h;
    SDL_GetTextureSize(ttext, &w, &h);
    SDL_FRect src = {0, 0, w, h};
    SDL_FRect dest = {
        (app->px * button->w.x) + (app->px * button->w.width / 2) - (w / 2),
        (app->px * button->w.y) + (button->w.height * app->px / 2) - (h / 2), w,
        h};
    SDL_RenderTexture(app->renderer, ttext, NULL, &dest);
    SDL_DestroyTexture(ttext);
    SDL_DestroySurface(text);
  }
}
