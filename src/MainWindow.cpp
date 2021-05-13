#include "MainWindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include "Config/SerialConnectionPreference.h"


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


void MainWindow::bindQtSlots() {
    /// serial connection ///
    connect(ui->buttonConnect, SIGNAL(clicked(bool)), this, SLOT(onSerialConnection()));
    connect(ui->buttonRefresh, SIGNAL(clicked(bool)), this, SLOT(onSerialRefresh()));

    /// calibration ///
    connect(ui->buttonCalibration, SIGNAL(clicked(bool)), this, SLOT(onCalibStart()));
    connect(ui->buttonIncreaseAngle, SIGNAL(clicked(bool)), this, SLOT(onIncreaseCalib()));
    connect(ui->buttonDecreaseAngle, SIGNAL(clicked(bool)), this, SLOT(onDecreaseCalib()));
    connect(ui->buttonSaveCalibration, SIGNAL(clicked(bool)), this, SLOT(onSaveCalib()));
    connect(ui->buttonCleanCalibration, SIGNAL(clicked(bool)), this, SLOT(onClearCalib()));

    /// terminal ///
    connect(ui->buttonSendCmd, SIGNAL(clicked(bool)), this, SLOT(onTerminalCmd()));

    /// panel ///
    connect(ui->buttonCtrlBalance, SIGNAL(clicked(bool)), this, SLOT(onPanelBalance()));
    connect(ui->buttonCtrlServos, SIGNAL(clicked(bool)), this, SLOT(onPanelServos()));
    connect(ui->buttonCtrlGyro, SIGNAL(clicked(bool)), this, SLOT(onPanelGyro()));
    connect(ui->buttonCtrlRestPos, SIGNAL(clicked(bool)), this, SLOT(onPanelRecovery()));

    /// motions and postures ///
    connect(ui->buttonPosBackFlip, SIGNAL(clicked(bool)), this, SLOT(onPosBackFlip()));
    connect(ui->buttonPosBunnyJump, SIGNAL(clicked(bool)), this, SLOT(onPosBunnyJump()));
    connect(ui->buttonPosButtomUp, SIGNAL(clicked(bool)), this, SLOT(onPosButtomUp()));
    connect(ui->buttonPosCheckRd, SIGNAL(clicked(bool)), this, SLOT(onPosCheckAround()));
    connect(ui->buttonPosHi, SIGNAL(clicked(bool)), this, SLOT(onPosGreeting()));
    connect(ui->buttonPosPee, SIGNAL(clicked(bool)), this, SLOT(onPosPee()));
    connect(ui->buttonPosPushUp, SIGNAL(clicked(bool)), this, SLOT(onPosPushup()));
    connect(ui->buttonPosRest, SIGNAL(clicked(bool)), this, SLOT(onPosRest()));
    connect(ui->buttonPosSit, SIGNAL(clicked(bool)), this, SLOT(onPosSitdown()));
    connect(ui->buttonPosSleep, SIGNAL(clicked(bool)), this, SLOT(onPosSleep()));
    connect(ui->buttonPosStepping, SIGNAL(clicked(bool)), this, SLOT(onPosStepping()));
    connect(ui->buttonPosStretch, SIGNAL(clicked(bool)), this, SLOT(onPosStretch()));
}


void MainWindow::unbindQtSlots() {
    /// serial connection ///
    disconnect(ui->buttonConnect, SIGNAL(clicked(bool)), this, SLOT(onSerialConnection()));
    disconnect(ui->buttonRefresh, SIGNAL(clicked(bool)), this, SLOT(onSerialRefresh()));

    /// calibration ///
    disconnect(ui->buttonCalibration, SIGNAL(clicked(bool)), this, SLOT(onCalibStart()));
    disconnect(ui->buttonIncreaseAngle, SIGNAL(clicked(bool)), this, SLOT(onIncreaseCalib()));
    disconnect(ui->buttonDecreaseAngle, SIGNAL(clicked(bool)), this, SLOT(onDecreaseCalib()));
    disconnect(ui->buttonSaveCalibration, SIGNAL(clicked(bool)), this, SLOT(onSaveCalib()));
    disconnect(ui->buttonCleanCalibration, SIGNAL(clicked(bool)), this, SLOT(onClearCalib()));

    /// terminal ///
    disconnect(ui->buttonSendCmd, SIGNAL(clicked(bool)), this, SLOT(onTerminalCmd()));

    /// panel ///
    disconnect(ui->buttonCtrlBalance, SIGNAL(clicked(bool)), this, SLOT(onPanelBalance()));
    disconnect(ui->buttonCtrlServos, SIGNAL(clicked(bool)), this, SLOT(onPanelServos()));
    disconnect(ui->buttonCtrlGyro, SIGNAL(clicked(bool)), this, SLOT(onPanelGyro()));
    disconnect(ui->buttonCtrlRestPos, SIGNAL(clicked(bool)), this, SLOT(onPanelRecovery()));

    /// motions and postures ///
    disconnect(ui->buttonPosBackFlip, SIGNAL(clicked(bool)), this, SLOT(onPosBackFlip()));
    disconnect(ui->buttonPosBunnyJump, SIGNAL(clicked(bool)), this, SLOT(onPosBunnyJump()));
    disconnect(ui->buttonPosButtomUp, SIGNAL(clicked(bool)), this, SLOT(onPosButtomUp()));
    disconnect(ui->buttonPosCheckRd, SIGNAL(clicked(bool)), this, SLOT(onPosCheckAround()));
    disconnect(ui->buttonPosHi, SIGNAL(clicked(bool)), this, SLOT(onPosGreeting()));
    disconnect(ui->buttonPosPee, SIGNAL(clicked(bool)), this, SLOT(onPosPee()));
    disconnect(ui->buttonPosPushUp, SIGNAL(clicked(bool)), this, SLOT(onPosPushup()));
    disconnect(ui->buttonPosRest, SIGNAL(clicked(bool)), this, SLOT(onPosRest()));
    disconnect(ui->buttonPosSit, SIGNAL(clicked(bool)), this, SLOT(onPosSitdown()));
    disconnect(ui->buttonPosSleep, SIGNAL(clicked(bool)), this, SLOT(onPosSleep()));
    disconnect(ui->buttonPosStepping, SIGNAL(clicked(bool)), this, SLOT(onPosStepping()));
    disconnect(ui->buttonPosStretch, SIGNAL(clicked(bool)), this, SLOT(onPosStretch()));
}


void MainWindow::onSerialRefresh() {

    // clear
    uiSerialHandler.clearSerialParametersSelections(
                ui->boxPortNumber,
                ui->boxBaudRate,
                ui->boxParity,
                ui->boxDataBits,
                ui->boxStopBits);

    // update selections
    uiSerialHandler.setupSerialParametersSelections(
                ui->boxPortNumber,
                ui->boxBaudRate,
                ui->boxParity,
                ui->boxDataBits,
                ui->boxStopBits);

    // set selections to default
    SerialConnectionPreference::getPreferences(
                ui->boxPortNumber,
                ui->boxBaudRate,
                ui->boxParity,
                ui->boxDataBits,
                ui->boxStopBits);
}


void MainWindow::onSerialConnection() {
    if (ui->buttonConnect->text() == tr("Connect")) {

        // save selections
        SerialConnectionPreference::setPreferences(
                    ui->boxPortNumber,
                    ui->boxBaudRate,
                    ui->boxParity,
                    ui->boxDataBits,
                    ui->boxStopBits);

        // update UI widgets
        ui->buttonConnect->setText(tr("Disconnect"));

        // connect to the serial port
        uiSerialHandler.connectSerial(
                    ui->boxPortNumber->currentText(),
                    ui->boxBaudRate->currentIndex(),
                    ui->boxDataBits->currentIndex(),
                    ui->boxStopBits->currentIndex(),
                    ui->boxParity->currentIndex());

        // bind textbrowser
        uiSerialHandler.bindFeedbackTextview(ui->textTerminalOutput);
    }

    else if (ui->buttonConnect->text() == tr("Disconnect")) {

        // update UI widgets
        ui->buttonConnect->setText(tr("Connect"));

        // disconnect from the serial port
        uiSerialHandler.disconnectSerial();

        // unbind textbrowser
        uiSerialHandler.unbindFeedbackTextview();
    }
}


void MainWindow::onTerminalCmd() {
    uiSerialHandler.sendCmdViaSerialPort(ui->lineCmd->text());
    ui->lineCmd->clear();
}


void MainWindow::onCalibStart() {
   uiSerialHandler.sendCmdViaSerialPort("c");
}


void MainWindow::onIncreaseCalib() {
    int pos = ui->boxSteering->currentIndex();
    uiCalibration.increaseCalibAngle(pos);
}


void MainWindow::onDecreaseCalib() {
    int pos = ui->boxSteering->currentIndex();
    uiCalibration.decreaseCalibAngle(pos);
}


void MainWindow::onSaveCalib() {
    uiSerialHandler.sendCmdViaSerialPort("s");
}


void MainWindow::onClearCalib() {
    int pos = ui->boxSteering->currentIndex();
    uiCalibration.clearCalibAngle(pos);
}


void MainWindow::onPanelBalance() {
    //TODO
};


void MainWindow::onPanelRecovery() {
    //TODO
};


void MainWindow::onPanelGyro() {
    //TODO
};


void MainWindow::onPanelServos() {
    //TODO
};

void MainWindow::onPosButtomUp() {
    uiMotionControl.doDefaultMotion(::PosButtomUp);
};


void MainWindow::onPosCheckAround() {
    uiMotionControl.doDefaultMotion(::PosCheckAround);
};


void MainWindow::onPosStretch() {
    uiMotionControl.doDefaultMotion(::PosStretch);
};


void MainWindow::onPosGreeting() {
    uiMotionControl.doDefaultMotion(::PosGreeting);
};


void MainWindow::onPosPee() {
    uiMotionControl.doDefaultMotion(::PosPee);
};


void MainWindow::onPosPushup() {
    uiMotionControl.doDefaultMotion(::PosPushup);
};


void MainWindow::onPosRest() {
    uiMotionControl.doDefaultMotion(::PosRest);
};


void MainWindow::onPosSleep() {
    uiMotionControl.doDefaultMotion(::PosSleep);
};


void MainWindow::onPosBackFlip() {
    uiMotionControl.doDefaultMotion(::PosBackFlip);
};


void MainWindow::onPosSitdown() {
    uiMotionControl.doDefaultMotion(::PosSitdown);
};


void MainWindow::onPosBunnyJump() {
    uiMotionControl.doDefaultMotion(::PosBunnyJump);
};


void MainWindow::onPosStepping() {
    uiMotionControl.doDefaultMotion(::PosStepping);
};


void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (ui->tabWidget->currentIndex() == 0) return; // 1st tab skipped

    uiMotionControl.procQtKeyPressedEvent(event);
}


void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if (ui->tabWidget->currentIndex() == 0) return; // 1st tab skipped

    uiMotionControl.procQtKeyReleasedEvent(event);
}
