#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logger.h"
#include "QtUtilities.h"

#include <QMessageBox>
#include <QDebug>
#include <QThread>
#include <QFileDialog>
#include <QKeyEvent>


const int REPEAT_MILISECONDS = 100;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    eventTimer(new QTimer(this))
{
    // new instances
    ui->setupUi(this);
    helper = new SerialHelper();
    stack = new SerialStackHandler(helper);

    // init buttons
    initButtons();

    // init menus
    initMenu();

    // initialize qt widgets
    initWidgets();

    // initialize qt slots/signals
    bindQtSlots();
}


MainWindow::~MainWindow()
{
    delete ui;
    delete stack;
    delete helper;
}


void MainWindow::initButtons()
{
    // release keyboard before keyboard events listening
    this->releaseKeyboard();

    // initialize all flags
    ctrlActivated = false;
    shiftActivated = false;
    moveFront = false;
    moveLeft = false;
    moveRight = false;
    moveBack = false;

    runningStatus = STATUS_READY;

    if (!eventTimer->isActive()) {
        eventTimer->start(REPEAT_MILISECONDS);
    }
}


void MainWindow::initMenu()
{
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
}


void MainWindow::initWidgets()
{
    // add serial ports information to the comboxes
    initPort();

    // init some valus
//    angle = 0;
    dynamicLanguage = LANGUAGE_CHINESE;

    // set default status
    ui->boxPortNumber->setCurrentIndex(0);
    ui->boxBaudRate->setCurrentIndex(7);
    ui->boxStopBits->setCurrentIndex(0);
    ui->boxDataBits->setCurrentIndex(3);
    ui->boxParity->setCurrentIndex(0);

    // set serial cmd relative widgets
    ui->buttonSendCmd->setEnabled(false);

    // update steerings relative widgets
    ui->buttonSavePos->setEnabled(false);
    ui->buttonCalibration->setEnabled(false);
    ui->buttonInAngle->setEnabled(false);
    ui->buttonDeAngle->setEnabled(false);
    ui->boxSteering->setEnabled(false);
    ui->buttonCleanPos->setEnabled(false);

    // set view and display the image from qt resources
    ui->dogView->setScene(QtUtilities::loadImageFromRes(":/app/pic/illustration.png",
                                                        ui->dogView->width(),
                                                        ui->dogView->height(),
                                                        Qt::AspectRatioMode::KeepAspectRatio));

    // set command panel to invalid
    ui->tabPanel->setEnabled(false);
    ui->textBrowserSpecification->setEnabled(false);
}


void MainWindow::exitApp()
{
    if (eventTimer->isActive()) eventTimer->stop();
    qApp->exit();
}


void MainWindow::translateUi(const char *package)
{
    static QTranslator* translator;
    if (translator != NULL)
    {
        qApp->removeTranslator(translator);
        delete translator;
        translator = NULL;
    }
    translator = new QTranslator;

    if (translator->load(package))
    {
        qApp->installTranslator(translator);
    }

    LOG_DEBUG() << "language package file path: " << package;
    ui->retranslateUi(this);
}

void MainWindow::showAsChn()
{
    translateUi(":/Chinese.qm");
    dynamicLanguage = LANGUAGE_CHINESE;
}


void MainWindow::showAsEng()
{
    translateUi(":/English.qm");
    dynamicLanguage = LANGUAGE_ENGLISH;
}

// override key pressed
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (ui->tabWidget->currentIndex() == 0) return; // 1st tab skipped

    switch(event->key()) {
    case Qt::Key_W:
        LOG_DEBUG() << "pressed up";
        moveFront = true;
        moveBack = false;
        break;

    case Qt::Key_S:
        LOG_DEBUG() << "pressed down";
        moveBack = true;
        moveFront = false;
        break;

    case Qt::Key_A:
        LOG_DEBUG() << "pressed left";
        moveLeft = true;
        moveRight = false;
        break;

    case Qt::Key_D:
        LOG_DEBUG() << "pressed right";
        moveRight = true;
        moveLeft = false;
        break;

    case Qt::Key_Control:
        LOG_DEBUG() << "pressed control";
        ctrlActivated = true;
        break;

    case Qt::Key_Shift:
        LOG_DEBUG() << "pressed shift";
        shiftActivated = true;
        break;

    case Qt::Key_Backspace:
        LOG_DEBUG() << "pressed backspace";
        runningStatus = STATUS_READY;
        break;

    case Qt::Key_G:
        LOG_DEBUG() << "pressed G";
        if (ui->buttonCtrlGyro->text() == tr("关闭陀螺仪")) {
            ui->buttonCtrlGyro->setText(tr("恢复陀螺仪"));
        } else {
            ui->buttonCtrlGyro->setText(tr("关闭陀螺仪"));
        }
        stack->sendCmdViaSerial("g");
        break;

    default:
        break;
    }
};


// override key release
void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (ui->tabWidget->currentIndex() == 0) return; // 1st tab skip

    switch(event->key()) {
    case Qt::Key_W:
        moveFront = false;
        LOG_DEBUG() << "released up";
        break;

    case Qt::Key_S:
        moveBack = false;
        LOG_DEBUG() << "released down";
        break;

    case Qt::Key_A:
        moveLeft = false;
        LOG_DEBUG() << "released left";
        break;

    case Qt::Key_D:
        moveRight = false;
        LOG_DEBUG() << "released right";
        break;

    case Qt::Key_Control:
        ctrlActivated = false;
        LOG_DEBUG() << "released control";
        break;

    case Qt::Key_Shift:
        shiftActivated = false;
        LOG_DEBUG() << "released shift";
        break;

    default:
        break;
    }
};

