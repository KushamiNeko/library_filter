#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <gtk-3.0/gtk/gtk.h>
#include "../../third_party/tinydir/tinydir.h"
#include "../../general/src/general_helper.h"
#include "../../general/src/general_list.h"
#include <omp.h>

#include "constant.h"
#include "list_item.h"

struct MainWindow {
  GtkWidget *mainWindow;
  GtkWidget *mainContainer;
  GtkWidget *entry;
  GtkEntryBuffer *entryBuffer;

  GtkWidget *scrollWindow;
  GtkWidget *viewport;
  GtkWidget *flowBox;

  struct GeneralList *filterStay;
  struct GeneralList *filterOut;
};

struct MainWindow *mainWindowNew(const gchar *libraryPath);

#endif
