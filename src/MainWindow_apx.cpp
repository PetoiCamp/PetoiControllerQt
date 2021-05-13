#include "MainWindow.h"
#include "ui_mainwindow.h"

#include "Config/SerialConnectionPreference.h"


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


void MainWindow::onPosButtomUp() {
    uiMotionControl.doDefaultMotion(::PosButtomUp);

    if (uiMotionControl.isKeyListeningOn()) {
        uiMotionControl.stopKeyListen();
    }
};


void MainWindow::onPosCheckAround() {
    uiMotionControl.doDefaultMotion(::PosCheckAround);

    if (uiMotionControl.isKeyListeningOn()) {
        uiMotionControl.stopKeyListen();
    }
};


void MainWindow::onPosStretch() {
    uiMotionControl.doDefaultMotion(::PosStretch);

    if (uiMotionControl.isKeyListeningOn()) {
        uiMotionControl.stopKeyListen();
    }
};


void MainWindow::onPosGreeting() {
    uiMotionControl.doDefaultMotion(::PosGreeting);

    if (uiMotionControl.isKeyListeningOn()) {
        uiMotionControl.stopKeyListen();
    }
};


void MainWindow::onPosPee() {
    uiMotionControl.doDefaultMotion(::PosPee);

    if (uiMotionControl.isKeyListeningOn()) {
        uiMotionControl.stopKeyListen();
    }
};


void MainWindow::onPosPushup() {
    uiMotionControl.doDefaultMotion(::PosPushup);

    if (uiMotionControl.isKeyListeningOn()) {
        uiMotionControl.stopKeyListen();
    }
};


void MainWindow::onPosRest() {
    uiMotionControl.doDefaultMotion(::PosRest);

    if (uiMotionControl.isKeyListeningOn()) {
        uiMotionControl.stopKeyListen();
    }
};


void MainWindow::onPosSleep() {
    uiMotionControl.doDefaultMotion(::PosSleep);

    if (uiMotionControl.isKeyListeningOn()) {
        uiMotionControl.stopKeyListen();
    }
};


void MainWindow::onPosBackFlip() {
    uiMotionControl.doDefaultMotion(::PosBackFlip);

    if (uiMotionControl.isKeyListeningOn()) {
        uiMotionControl.stopKeyListen();
    }
};


void MainWindow::onPosSitdown() {
    uiMotionControl.doDefaultMotion(::PosSitdown);

    if (uiMotionControl.isKeyListeningOn()) {
        uiMotionControl.stopKeyListen();
    }
};


void MainWindow::onPosBunnyJump() {
    uiMotionControl.doDefaultMotion(::PosBunnyJump);

    if (uiMotionControl.isKeyListeningOn()) {
        uiMotionControl.stopKeyListen();
    }
};


void MainWindow::onPosStepping() {
    uiMotionControl.doDefaultMotion(::PosStepping);

    if (uiMotionControl.isKeyListeningOn()) {
        uiMotionControl.stopKeyListen();
    }
};
