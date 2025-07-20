#include "include/input.h"
#include "include/cr.h"
#include "include/widget.h"
#include <SDL3/SDL_stdinc.h>

CRInput *input_new() {
  CRInput *input;
  input = SDL_calloc(1, sizeof(*input));
  if (input) {
    input->w.type = WidgetButton;
    input->w.render = input_render;
  }
  return input;
}

void input_render(void *_app, void *_w) {
  CRApp *app = _app;
  CRInput *input = _w;
  /* outer box, so border */
  {
    SDL_FRect rect = {app->px * input->w.x, app->px * input->w.y,
                      app->px * input->w.width, app->px * input->w.height};

    const SDL_Color *color = &COLORS[input->border_color];
    SDL_SetRenderDrawColor(app->renderer, color->r, color->g, color->b,
                           color->a);
    SDL_RenderFillRect(app->renderer, &rect);
  }

  /* inner box */
  {
    SDL_FRect rect = {(app->px * input->w.x) + app->border,
                      (app->px * input->w.y) + app->border,
                      (app->px * input->w.width) - (app->border * 2),
                      (app->px * input->w.height) - (app->border * 2)};
    const SDL_Color *color = &COLORS[input->color];
    SDL_SetRenderDrawColor(app->renderer, color->r, color->g, color->b,
                           color->a);
    SDL_RenderFillRect(app->renderer, &rect);
  }

  /* text */
  if (input->content != NULL || input->content[0] != '\0') {
    const SDL_Color *color = &COLORS[input->text_color];
    const SDL_Color *bg_color = &COLORS[input->color];

    SDL_Surface *text = TTF_RenderText_Shaded_Wrapped(
        app->input_font, input->content, 0, *color, *bg_color,
        input->w.width * app->px);
    SDL_Texture *ttext = SDL_CreateTextureFromSurface(app->renderer, text);
    float w, h;
    SDL_GetTextureSize(ttext, &w, &h);
    SDL_FRect src = {0, 0, w, h};
    SDL_FRect dest = {
        (app->px * input->w.x) + (app->px * input->w.width) - (app->border + w),
        (app->px * input->w.y) + (input->w.height * app->px / 2) - (h / 2), w,
        h};
    SDL_RenderTexture(app->renderer, ttext, NULL, &dest);
    SDL_DestroyTexture(ttext);
    SDL_DestroySurface(text);
  }
}
