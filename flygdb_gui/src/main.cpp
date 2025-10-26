#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include "flygdb/flygdb.hpp"

int main(int, char**) {
  Fl_Window win(460, 160, "FlyGdbGui");
  auto info = flygdb::hello();

  Fl_Box box(20, 40, 420, 80, info.c_str());
  box.labelsize(12);
  win.end();
  win.show();
  return Fl::run();
}
