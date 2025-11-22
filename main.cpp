#include <QtWidgets/QApplication>

#include "ObjectFactory/shapesRegistrator.h"
#include "lab.h"

int main(int argc, char *argv[]) {
  ShapesRegistrator::registerTypes();

  QApplication app(argc, argv);
  Lab window;
  window.show();

  return app.exec();
}
