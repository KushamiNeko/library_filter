#include <gtk-3.0/gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

#include "header/main_window.h"
#include "header/list_item.h"

int main(int argc, char const *argv[]) {
  gtk_init(NULL, NULL);

  struct MainWindow *mainWindow = mainWindowNew(LIBRARY_PATH);

  gtk_main();
  return 0;
}
