#include "../header/list_item.h"

struct ListItem *listItemNew(const gchar *imageFile) {
  struct ListItem *re;
  GdkPixbuf *icon;
  const gchar *iconFile;

  gchar *imageBaseExt;
  gchar *imageBase;

  gchar *label;

  re = defenseMalloc(sizeof(struct ListItem));

  if (fileExist(imageFile)) {
    iconFile = imageFile;
  } else {
    iconFile = FOLDER_ICON;
  }

  icon = gdk_pixbuf_new_from_file_at_scale(iconFile, ICON_SIZE, -1, TRUE, NULL);
  if (icon == NULL) {
    g_print("icon construct failed: %sn", imageFile);
    exit(1);
  }

  imageBaseExt = pathGetBase((gchar *)imageFile);
  imageBase = pathRemoveExt(imageBaseExt);

  free(imageBaseExt);
  re->name = imageBase;

  if (strlen(imageBase) > MAX_LABEL_CHAR) {
    label = (gchar *)defenseMalloc(MAX_LABEL_CHAR + 1 * sizeof(char));
    strncpy(label, imageBase, MAX_LABEL_CHAR - 2);
    label[MAX_LABEL_CHAR - 2] = '.';
    label[MAX_LABEL_CHAR - 1] = '.';
    label[MAX_LABEL_CHAR] = '\0';
  } else {
    label = imageBase;
  }

//#pragma omp parallel
//{
#pragma omp critical
  {
    re->image = gtk_image_new_from_pixbuf(icon);
    re->container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    re->label = gtk_label_new(label);
  }
  //}

  gtk_widget_set_margin_bottom(re->container, WIDGET_MARGIN);
  gtk_widget_set_margin_top(re->container, WIDGET_MARGIN);
  gtk_widget_set_margin_start(re->container, WIDGET_MARGIN);
  gtk_widget_set_margin_end(re->container, WIDGET_MARGIN);

  gtk_widget_set_halign(re->label, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(re->label, GTK_ALIGN_CENTER);
  // gtk_label_set_selectable(GTK_LABEL(re->label), TRUE);

  gtk_widget_set_margin_top(re->label, WIDGET_MARGIN);
  gtk_widget_set_margin_top(re->label, WIDGET_MARGIN);

  gtk_box_pack_start(GTK_BOX(re->container), re->image, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(re->container), re->label, FALSE, TRUE, 0);

  gtk_widget_show_all(re->container);
  return re;
}
