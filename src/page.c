#include "include/page.h"
#include "include/cr.h"
#include <SDL3/SDL_assert.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>

void page_render(void *_app, void *_w) {
  SDL_assert(_app != NULL);
  SDL_assert(_w != NULL);
  CRApp *app = _app;
  CRPage *page = _w;
  SDL_FRect rect = {app->px * page->w.x, app->px * page->w.y,
                    app->px * page->w.width, app->px * page->w.height};
  const SDL_Color *color = &COLORS[page->background];
  SDL_SetRenderDrawColor(app->renderer, color->r, color->g, color->b, color->a);
  SDL_RenderFillRect(app->renderer, &rect);
}

CRPage *page_new(void *_app, void *_params) {
  SDL_assert(_app != NULL);
  CRApp *app = _app;
  CRPage *p = NULL;

  p = SDL_calloc(1, sizeof(*p));
  if (p) {
    p->w.render = page_render;
    p->w.type = WidgetPage;
  }
  return p;
}
