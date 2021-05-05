#include "ui/mainwindow.h"
#include "ui/logger.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // initialize logger
    logger::Logger::init();

    // create main window
    MainWindow w;
    w.setWindowTitle("OpenCatSerialController v0.1a");
    w.show();

    // everything done
    return a.exec();
}
