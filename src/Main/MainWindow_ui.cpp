#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Components/Serials/SerialConnectionPreference.h"

#include <QDebug>


UiSerialHandler     MainWindow::uiSerialHandler;    // handler for serial connection and message send/recv
UiCalibrationCheck  MainWindow::uiCalibration;      // calibration
UiMotionControl     MainWindow::uiMotionControl;    // default actions
UiCustomActions     MainWindow::uiCustomActions;    // user-defined action or command


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
    SerialConnectionPreference::getPreference(
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

    // setup custom actions/commands panel
    uiCustomActions.setupViewTable(ui->tableCustomActions);
    uiCustomActions.setupControlPanel(ui->buttonCmdAdd);

    // init menu
    setupMenus();

    // init languages
    setupLanguages();

    // switch
    isSerialOn = isCalibrationOn = isActionsOn = false;
    switchActions();
    switchCalibration();
    switchSerial();
}


void MainWindow::switchCalibration() {
    if (isCalibrationOn) {
        ui->buttonCalibration->setEnabled(false);
        ui->buttonIncreaseAngle->setEnabled(true);
        ui->buttonDecreaseAngle->setEnabled(true);
        ui->buttonSaveCalibration->setEnabled(true);
        ui->buttonCleanCalibration->setEnabled(true);
        ui->boxSteering->setEnabled(true);
    } else {
        ui->buttonCalibration->setEnabled(true);
        ui->buttonIncreaseAngle->setEnabled(false);
        ui->buttonDecreaseAngle->setEnabled(false);
        ui->buttonSaveCalibration->setEnabled(false);
        ui->buttonCleanCalibration->setEnabled(false);
        ui->boxSteering->setEnabled(false);
    }
}


void MainWindow::switchSerial() {
    if (isSerialOn) {
        ui->boxPortNumber->setEnabled(false);
        ui->boxBaudRate->setEnabled(false);
        ui->boxDataBits->setEnabled(false);
        ui->boxStopBits->setEnabled(false);
        ui->boxParity->setEnabled(false);
        ui->buttonRefresh->setEnabled(false);

        ui->lineCmd->setEnabled(true);
        ui->buttonSendCmd->setEnabled(true);
        ui->textTerminalOutput->setEnabled(true);

        ui->buttonCalibration->setEnabled(true);
    } else {
        ui->boxPortNumber->setEnabled(true);
        ui->boxBaudRate->setEnabled(true);
        ui->boxDataBits->setEnabled(true);
        ui->boxStopBits->setEnabled(true);
        ui->boxParity->setEnabled(true);
        ui->buttonRefresh->setEnabled(true);

        ui->lineCmd->setEnabled(false);
        ui->buttonSendCmd->setEnabled(false);
        ui->textTerminalOutput->setEnabled(false);

        ui->buttonCalibration->setEnabled(false);
    }
}


void MainWindow::switchActions() {
    if (isActionsOn) {
        ui->buttonPosBackFlip->setEnabled(true);
        ui->buttonPosBunnyJump->setEnabled(true);
        ui->buttonPosButtomUp->setEnabled(true);
        ui->buttonPosCheckRd->setEnabled(true);
        ui->buttonPosHi->setEnabled(true);
        ui->buttonPosPee->setEnabled(true);
        ui->buttonPosPushUp->setEnabled(true);
        ui->buttonPosRest->setEnabled(true);
        ui->buttonPosSit->setEnabled(true);
        ui->buttonPosSleep->setEnabled(true);
        ui->buttonPosStepping->setEnabled(true);
        ui->buttonPosStretch->setEnabled(true);
    } else {
        ui->buttonPosBackFlip->setEnabled(false);
        ui->buttonPosBunnyJump->setEnabled(false);
        ui->buttonPosButtomUp->setEnabled(false);
        ui->buttonPosCheckRd->setEnabled(false);
        ui->buttonPosHi->setEnabled(false);
        ui->buttonPosPee->setEnabled(false);
        ui->buttonPosPushUp->setEnabled(false);
        ui->buttonPosRest->setEnabled(false);
        ui->buttonPosSit->setEnabled(false);
        ui->buttonPosSleep->setEnabled(false);
        ui->buttonPosStepping->setEnabled(false);
        ui->buttonPosStretch->setEnabled(false);
    }
}


void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (ui->tabWidget->currentIndex() == 0) return; // 1st tab skipped
    if (!isActionsOn) return;

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
    if (!isActionsOn) return;

    uiMotionControl.procQtKeyReleasedEvent(event);
}


void MainWindow::translateUi(QString package) {

    if (translator.load(package))
    {
        qApp->installTranslator(&translator);
    }

    qDebug() << "language package file path: " << package;
    ui->retranslateUi(this);
}


void MainWindow::setupLanguages() {
    QStringList languages;
    languages << "English" << "Chinese";

    ui->boxLanguage->addItems(languages);
}


void MainWindow::setupMenus() {
    fileMenu = new QMenu(tr("&File"), this);
    fileLinguistMenu = new QMenu(tr("&Language"), this);

    chineseTypeAct = new QAction(tr("&Chinese"),this);   chineseTypeAct->setShortcut(tr("Ctrl+["));
    englishTypeAct = new QAction(tr("&English"), this);  englishTypeAct->setShortcut(tr("Ctrl+]"));

    fileLinguistMenu->addAction(chineseTypeAct);
    fileLinguistMenu->addAction(englishTypeAct);

    exitAct = new QAction(tr("&Exit"), this); exitAct->setShortcut(tr("Ctrl+Q"));

    fileMenu->addMenu(fileLinguistMenu);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->setNativeMenuBar(true);

    // connect menu
    connect(exitAct, SIGNAL(triggered(bool)), this, SLOT(onFileExit()));
    connect(englishTypeAct, SIGNAL(triggered(bool)), SLOT(onShowAsEng()));
    connect(chineseTypeAct, SIGNAL(triggered(bool)), this, SLOT(onShowAsChn()));
}


void MainWindow::onFileExit() {
    qApp->exit();
}


void MainWindow::onShowAsChn() {
    translateUi(":/res/Chinese.qm");
};


void MainWindow::onShowAsEng() {
    translateUi(":/res/English.qm");
};
