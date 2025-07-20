#ifndef WIDGET_LIST_H__
#define WIDGET_LIST_H__

#include "common.h"
#include <stdbool.h>

#define widget_list_foreach(list, action, ...)                                 \
  {                                                                            \
    for (CRWidgetList *item = list; item; item = item->next) {                 \
      action(item->w, ##__VA_ARGS__);                                          \
    }                                                                          \
  }

bool widget_list_append(CRWidgetList **list, CRWidget *widget);
void widget_list_free(CRWidgetList *list);

#endif /* WIDGET_LIST_H__ */
