#ifndef WIDGET_LIST_H__
#define WIDGET_LIST_H__

#include <stdbool.h>

struct s_CRWidget;
typedef struct s_CRWidget CRWidget;

typedef struct s_CRWidgetList CRWidgetList;
struct s_CRWidgetList {
  CRWidget *w;
  CRWidgetList *next;
  CRWidgetList *previous;
};

#define widget_list_foreach(list, action, ...)                                 \
  {                                                                            \
    for (CRWidgetList *item = list; item; item = item->next) {                 \
      action(item->w, ##__VA_ARGS__);                                          \
    }                                                                          \
  }

bool widget_list_append(CRWidgetList **list, CRWidget *widget);
void widget_list_free(CRWidgetList *list);

#endif /* WIDGET_LIST_H__ */
