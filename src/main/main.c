#include <gtk-3.0/gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

// static void print_hello(GtkWidget *widget, gpointer data) {
//   g_print("Hello World\n");
// }
//
// static void activate(GtkApplication *app, gpointer user_data) {
//   GtkWidget *window;
//   GtkWidget *button;
//   GtkWidget *button_box;
//
//   window = gtk_application_window_new(app);
//   gtk_window_set_title(GTK_WINDOW(window), "Window");
//   gtk_window_set_default_size(GTK_WINDOW(window), 200, 100);
//
//   button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
//   gtk_container_add(GTK_CONTAINER(window), button_box);
//
//   button = gtk_button_new_with_label("Hello World");
//   g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);
//   // g_signal_connect_swapped(button, "clicked",
//   G_CALLBACK(gtk_widget_destroy),
//   //                          window);
//   gtk_container_add(GTK_CONTAINER(button_box), button);
//
//   gtk_widget_show_all(window);
// }
#define UIFILE "src/ui/mainUI.glade"

typedef struct { GtkWidget *container, *image, *label; } flowBoxItem;

flowBoxItem *newFlowBoxItem(const char *file) {
  flowBoxItem *item = (flowBoxItem *)calloc(sizeof(flowBoxItem), 1);
  item->container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_show(item->container);

  gtk_widget_set_halign(item->container, GTK_ALIGN_START);
  gtk_widget_set_valign(item->container, GTK_ALIGN_START);

  gtk_widget_set_hexpand(item->container, FALSE);
  gtk_widget_set_vexpand(item->container, FALSE);

  gtk_widget_set_margin_bottom(item->container, 7);
  gtk_widget_set_margin_top(item->container, 7);
  gtk_widget_set_margin_start(item->container, 7);
  gtk_widget_set_margin_end(item->container, 7);

  // gtk_widget_set_size_request(item->container, 135, 100);

  GdkPixbuf *icon =
      gdk_pixbuf_new_from_file_at_scale(file, 150, -1, TRUE, NULL);
  item->image = gtk_image_new_from_pixbuf(icon);
  gtk_widget_show(item->image);

  item->label = gtk_label_new(file);
  gtk_widget_show(item->label);
  gtk_widget_set_halign(item->label, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(item->label, GTK_ALIGN_CENTER);

  gtk_widget_set_margin_top(item->label, 3);
  gtk_widget_set_margin_top(item->label, 3);
  // gtk_widget_set_size_request(item->label, 50, 10);

  gtk_box_pack_start(GTK_BOX(item->container), item->image, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(item->container), item->label, FALSE, TRUE, 0);
  // gtk_container_add((GtkContainer *)item->container, item->label);

  return item;
}

int main(int argc, char const *argv[]) {
  printf("%s\n", "Hello GTK");

  GtkBuilder *builder;
  GObject *window;
  // GObject *mainView;
  GObject *mainScroll;

  GtkWidget *flowBox;

  // GObject *status;
  // GtkWidget *button;

  gtk_init(NULL, NULL);
  builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, UIFILE, NULL);

  window = gtk_builder_get_object(builder, "window1");
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  // button = gtk_button_new_with_label("test");
  mainScroll = gtk_builder_get_object(builder, "scrolledwindow1");
  // mainView = gtk_builder_get_object(builder, "viewport1");

  // gtk_widget_set_vexpand(GTK_WIDGET(mainScroll), TRUE);
  // gtk_widget_set_hexpand(GTK_WIDGET(mainScroll), TRUE);
  // gtk_widget_set_valign(GTK_WIDGET(mainScroll), GTK_ALIGN_CENTER);
  // gtk_widget_set_halign(GTK_WIDGET(mainScroll), GTK_ALIGN_CENTER);

  GtkAdjustment *hadjus =
      gtk_scrolled_window_get_hadjustment(GTK_SCROLLED_WINDOW(mainScroll));
  GtkAdjustment *vadjus =
      gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(mainScroll));

  flowBox = gtk_flow_box_new();
  gtk_widget_show(flowBox);
  gtk_container_add(GTK_CONTAINER(mainScroll), flowBox);

  gtk_flow_box_set_homogeneous(GTK_FLOW_BOX(flowBox), TRUE);
  gtk_flow_box_set_min_children_per_line(GTK_FLOW_BOX(flowBox), 3);

  // gtk_flow_box_set_row_spacing(GTK_FLOW_BOX(flowBox), 7);
  // gtk_flow_box_set_row_spacing(GTK_FLOW_BOX(flowBox), 7);

  gtk_flow_box_set_hadjustment(GTK_FLOW_BOX(flowBox), hadjus);
  gtk_flow_box_set_vadjustment(GTK_FLOW_BOX(flowBox), vadjus);

  gtk_widget_set_halign(flowBox, GTK_ALIGN_START);
  gtk_widget_set_valign(flowBox, GTK_ALIGN_START);

  // gtk_widget_set_margin_end(flowBox, 7);
  // gtk_widget_set_margin_start(flowBox, 7);
  // gtk_widget_set_margin_top(flowBox, 7);
  // gtk_widget_set_margin_bottom(flowBox, 7);

  flowBoxItem *item = newFlowBoxItem("icon.jpg");
  flowBoxItem *item02 = newFlowBoxItem("icon.jpg");
  // gtk_widget_set_halign(item->container, GTK_ALIGN_START);
  // gtk_widget_set_valign(item->container, GTK_ALIGN_START);
  // gtk_widget_set_halign(item02->container, GTK_ALIGN_START);
  // gtk_widget_set_valign(item02->container, GTK_ALIGN_START);

  gtk_container_add(GTK_CONTAINER(flowBox), item->container);
  // gtk_container_child_set((GtkContainer *)flowBox, item->container, "halign",
  // "start");
  gtk_container_add(GTK_CONTAINER(flowBox), item02->container);

  // gtk_container_add(mainView, flowBox);
  // gtk_container_add(flowBox, button);
  //

  // gtk_widget_show(button);

  // gtk_widget_show_all(window);
  gtk_main();

  return 0;
}
