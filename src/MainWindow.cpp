#include "MainWindow.h"
#include "ui_mainwindow.h"

#include "Config/SerialConnectionPreference.h"

#include <QDebug>


UiSerialHandler     MainWindow::uiSerialHandler;    // handler for serial connection and message send/recv
UiCalibrationCheck  MainWindow::uiCalibration;      // calibration
UiMotionControl     MainWindow::uiMotionControl;    // default actions

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // new instances
    ui->setupUi(this);

    // bind all widgets signals/slots
    bindQtSlots();

    // setup ui
    setupWidgets();
}


MainWindow::~MainWindow() {

    // unbind all widgets signals/slots
    unbindQtSlots();

    // delete ui
    delete ui;
}


void MainWindow::setupWidgets() {
    // setup serial selections
    uiSerialHandler.setupSerialParametersSelections(
                ui->boxPortNumber,
                ui->boxBaudRate,
                ui->boxParity,
                ui->boxDataBits,
                ui->boxStopBits);

    // change to those selections to default
    SerialConnectionPreference::getPreferences(
                ui->boxPortNumber,
                ui->boxBaudRate,
                ui->boxParity,
                ui->boxDataBits,
                ui->boxStopBits);

    // setup servos selection
    uiCalibration.setupServosSelections(
                ui->boxSteering);

    // setup illustration
    uiCalibration.setupIllustration(
                ui->viewBittleIllustration);
}


void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (ui->tabWidget->currentIndex() == 0) return; // 1st tab skipped

    switch (event->key())
    {
    case Qt::Key_R:
        qDebug() << "Self-right...";
        uiSerialHandler.sendCmdViaSerialPort("krc");
        break;

    case Qt::Key_G:
        qDebug() << "Gryo switch...";
        uiSerialHandler.sendCmdViaSerialPort("g");
        break;

    case Qt::Key_H:
        qDebug() << "Servos switch...";
        uiSerialHandler.sendCmdViaSerialPort("d");
        break;

    case Qt::Key_Backspace:
        qDebug() << "keep balance...";
        uiSerialHandler.sendCmdViaSerialPort("kbalance");
        break;

    case Qt::Key_W:  // forward
    case Qt::Key_S:  // backward
    case Qt::Key_A:  // left
    case Qt::Key_D:  // right
    case Qt::Key_1:  // normal
    case Qt::Key_2:  // run
    case Qt::Key_3:  // crawl

        if (!uiMotionControl.isKeyListeningOn()) {
            uiMotionControl.startKeyListen();
        }

        uiMotionControl.procQtKeyPressedEvent(event);
        break;
    }
}


void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if (ui->tabWidget->currentIndex() == 0) return; // 1st tab skipped

    uiMotionControl.procQtKeyReleasedEvent(event);
}
