#include "include/input.h"
#include "include/widget.h"
#include <SDL3/SDL_stdinc.h>

CRInput *input_new() {
  CRInput *input;
  input = SDL_calloc(1, sizeof(*input));
  if (input) {
    input->w.type = WidgetButton;
  }
  return input;
}

void input_render(CRApp *app, CRInput *input) {
  /* outer box, so border */
  {
    SDL_FRect rect = {app->px * input->x, app->px * input->y,
                      app->px * input->width, app->px * input->height};

    const SDL_Color *color = &COLORS[input->border_color];
    SDL_SetRenderDrawColor(app->renderer, color->r, color->g, color->b,
                           color->a);
    SDL_RenderFillRect(app->renderer, &rect);
  }

  /* inner box */
  {
    SDL_FRect rect = {(app->px * input->x) + app->border,
                      (app->px * input->y) + app->border,
                      (app->px * input->width) - (app->border * 2),
                      (app->px * input->height) - (app->border * 2)};
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
        input->width * app->px);
    SDL_Texture *ttext = SDL_CreateTextureFromSurface(app->renderer, text);
    float w, h;
    SDL_GetTextureSize(ttext, &w, &h);
    SDL_FRect src = {0, 0, w, h};
    SDL_FRect dest = {
        (app->px * input->x) + (app->px * input->width) - (app->border + w),
        (app->px * input->y) + (input->height * app->px / 2) - (h / 2), w, h};
    SDL_RenderTexture(app->renderer, ttext, NULL, &dest);
    SDL_DestroyTexture(ttext);
    SDL_DestroySurface(text);
  }
}
