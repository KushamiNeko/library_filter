#ifndef LIST_ITEM_HPP
#define LIST_ITEM_HPP

#include <gtk-3.0/gtk/gtk.h>
#include <stdlib.h>
#include <omp.h>
// #include <sys/types.h>
// #include <sys/stat.h>
#include "../../../general/src/header/general_helper.h"
#include "constant.h"

struct ListItem {
  GtkWidget *container;
  GtkWidget *image;
  GtkWidget *label;

  gchar *name;
  gchar **tags;
};

struct ListItem *listItemNew(const gchar *imageFile);

#endif
