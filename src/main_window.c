#include "main_window.h"

static void constructListItem(struct MainWindow *window,
                              const gchar *libraryPath) {
  tinydir_dir dir;
  tinydir_open(&dir, libraryPath);

#pragma omp parallel firstprivate(libraryPath) shared(window)
  {
#pragma omp master
    {
      while (dir.has_next) {
        tinydir_file file;
        tinydir_readfile(&dir, &file);

        if (file.is_dir) {
          tinydir_next(&dir);
          continue;
        }

#pragma omp task firstprivate(file)
        {
          char *imageFile = pathJoin(libraryPath, file.name);
          struct ListItem *item = listItemNew(imageFile);
#pragma omp critical
          {
            gtk_container_add(GTK_CONTAINER(window->flowBox), item->container);
            generalListAddItemStack(&(window->filterStay), (void *)item);

            free(imageFile);
          }
        }

#pragma omp master
        { tinydir_next(&dir); }
      }
    }
  }

  tinydir_close(&dir);
}

static void entryBufferInserted(GtkEntryBuffer *buffer, guint position,
                                gchar *chars, guint n_chars, void *userData) {}

static void entryBufferDeleted(GtkEntryBuffer *buffer, guint position,

                               guint n_chars, void *userData) {}

struct MainWindow *mainWindowNew(const gchar *libraryPath) {
  GtkAdjustment *h;
  GtkAdjustment *v;

  struct MainWindow *re;

  re = (struct MainWindow *)defenseMalloc(sizeof(struct MainWindow));

  re->filterStay = generalListNew(NULL);
  re->filterOut = generalListNew(NULL);

  //  re->stay = NULL;
  //  re->end = NULL;

  re->mainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(re->mainWindow), "GTK Library Filter");
  gtk_window_set_position(GTK_WINDOW(re->mainWindow), GTK_WIN_POS_CENTER);

  re->mainContainer = gtk_box_new(GTK_ORIENTATION_VERTICAL, WIDGET_MARGIN);
  gtk_widget_set_margin_bottom(re->mainContainer, WIDGET_MARGIN);
  gtk_widget_set_margin_top(re->mainContainer, WIDGET_MARGIN);
  gtk_widget_set_margin_start(re->mainContainer, WIDGET_MARGIN);
  gtk_widget_set_margin_end(re->mainContainer, WIDGET_MARGIN);

  gtk_widget_set_size_request(re->mainContainer, BOX_WIDTH, BOX_HEIGHT);

  gtk_container_add(GTK_CONTAINER(re->mainWindow), re->mainContainer);

  re->entryBuffer = gtk_entry_buffer_new(NULL, -1);
  re->entry = gtk_entry_new_with_buffer(GTK_ENTRY_BUFFER(re->entryBuffer));

  gtk_container_add(GTK_CONTAINER(re->mainContainer), re->entry);

  re->scrollWindow = gtk_scrolled_window_new(NULL, NULL);
  h = gtk_scrolled_window_get_hadjustment(
      GTK_SCROLLED_WINDOW(re->scrollWindow));
  v = gtk_scrolled_window_get_vadjustment(
      GTK_SCROLLED_WINDOW(re->scrollWindow));

  gtk_widget_set_margin_bottom(re->scrollWindow, WIDGET_MARGIN);
  gtk_widget_set_margin_top(re->scrollWindow, WIDGET_MARGIN);
  gtk_widget_set_margin_start(re->scrollWindow, WIDGET_MARGIN);
  gtk_widget_set_margin_end(re->scrollWindow, WIDGET_MARGIN);

  gtk_widget_set_hexpand(re->scrollWindow, TRUE);
  gtk_widget_set_vexpand(re->scrollWindow, TRUE);

  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(re->scrollWindow),
                                 GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

  gtk_container_add(GTK_CONTAINER(re->mainContainer), re->scrollWindow);

  re->flowBox = gtk_flow_box_new();
  gtk_flow_box_set_homogeneous(GTK_FLOW_BOX(re->flowBox), TRUE);
  gtk_flow_box_set_min_children_per_line(GTK_FLOW_BOX(re->flowBox), MIN_ITEM);

  // gtk_flow_box_set_row_spacing(GTK_FLOW_BOX(re->flowBox),
  // FLOW_BOX_SPACE);

  gtk_flow_box_set_hadjustment(GTK_FLOW_BOX(re->flowBox), h);
  gtk_flow_box_set_vadjustment(GTK_FLOW_BOX(re->flowBox), v);

  gtk_widget_set_halign(re->flowBox, GTK_ALIGN_START);
  gtk_widget_set_valign(re->flowBox, GTK_ALIGN_START);

  gtk_widget_set_margin_bottom(re->flowBox, WIDGET_MARGIN);
  gtk_widget_set_margin_top(re->flowBox, WIDGET_MARGIN);
  gtk_widget_set_margin_start(re->flowBox, WIDGET_MARGIN);
  gtk_widget_set_margin_end(re->flowBox, WIDGET_MARGIN);

  gtk_container_add(GTK_CONTAINER(re->scrollWindow), re->flowBox);

  gtk_widget_show_all(re->mainWindow);

  g_signal_connect(re->mainWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  constructListItem(re, libraryPath);

  return re;
}
