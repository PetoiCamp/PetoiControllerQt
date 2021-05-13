#include "MainWindow.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // create main window
    MainWindow w;
    w.setWindowTitle("OpenCatSerialController v0.2.1a");
    w.show();

    // everything done
    return a.exec();
}
