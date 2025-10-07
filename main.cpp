#include "lab.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Lab window;
    window.show();
    return app.exec();
}
