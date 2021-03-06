#include "UiMotionControl.h"
#include "src/Main/MainWindow.h"

#include <QDebug>


UiMotionControl::UiMotionControl(QObject *parent) :
    QObject(parent),
    timer() {}


UiMotionControl::~UiMotionControl() {};


void UiMotionControl::doDefaultMotion(DefinedMotions motion) {
    switch (motion) {
    case PosButtomUp:
        MainWindow::uiSerialHandler.sendCmdViaSerialPort("kbuttUp");
        break;

    case PosCheckAround:
        MainWindow::uiSerialHandler.sendCmdViaSerialPort("kck");
        break;

    case PosStretch:
        MainWindow::uiSerialHandler.sendCmdViaSerialPort("kstr");
        break;

    case PosGreeting:
        MainWindow::uiSerialHandler.sendCmdViaSerialPort("khi");
        break;

    case PosPee:
        MainWindow::uiSerialHandler.sendCmdViaSerialPort("kpee");
        break;

    case PosPushup:
        MainWindow::uiSerialHandler.sendCmdViaSerialPort("kpu");
        break;

    case PosRest:
        MainWindow::uiSerialHandler.sendCmdViaSerialPort("krest");
        break;

    case PosUpStair:
        MainWindow::uiSerialHandler.sendCmdViaSerialPort("kstp");
        break;

    case PosBackFlip:
        MainWindow::uiSerialHandler.sendCmdViaSerialPort("kbf");
        break;

    case PosSitdown:
        MainWindow::uiSerialHandler.sendCmdViaSerialPort("ksit");
        break;

    case PosBunnyJump:
        MainWindow::uiSerialHandler.sendCmdViaSerialPort("kbdF");
        break;

    case PosStepping:
        MainWindow::uiSerialHandler.sendCmdViaSerialPort("kvt");
        break;

    default:
        break;
    }

    motionStatus = STATUS_READY;
};


int UiMotionControl::updateMotionStatus() {
    if (crawlActivated && moveFront) {
         return STATUS_CRAWL_FORWARD;
    }

     if (crawlActivated && moveBack) {
         return STATUS_CRAWL_BACKWARD;
     }

     if (crawlActivated && moveLeft) {
         return STATUS_CRAWL_LEFT;
     }

     if (crawlActivated && moveRight) {
         return STATUS_CRAWL_RIGHT;
     }

     if (runActivated && moveFront) {
         return STATUS_RUN_FORWARD;
     }

     if (runActivated && moveBack) {
         return STATUS_RUN_BACKWARD;
     }

     if (runActivated && moveLeft) {
         return STATUS_RUN_LEFT;
     }

     if (runActivated && moveRight) {
         return STATUS_RUN_RIGHT;
     }

     if (moveFront) {
         return STATUS_NORMAL_FORWARD;
     }

     if (moveBack) {
         return STATUS_NORMAL_BACKWARD;
     }

     if (moveLeft) {
         return STATUS_NORMAL_LEFT;
     }

     if (moveRight) {
         return STATUS_NORMAL_RIGHT;
     }

     return STATUS_STANDBY;
}


void UiMotionControl::usbDevicesEventCheck() {

    if (motionStatus == updateMotionStatus()) {// nothing have changed
        return;
    } else {
        int updated = updateMotionStatus();
        switch (updated) {

        case STATUS_CRAWL_FORWARD:
//            qDebug() << "status: crawl forward";
            MainWindow::uiSerialHandler.sendCmdViaSerialPort("kcrF");
            break;

        case STATUS_CRAWL_BACKWARD:
//            qDebug() << "status: backward";
            MainWindow::uiSerialHandler.sendCmdViaSerialPort("kbk");
            break;

        case STATUS_CRAWL_LEFT:
//            qDebug() << "status: crawl left";
            MainWindow::uiSerialHandler.sendCmdViaSerialPort("kcrL");
            break;

        case STATUS_CRAWL_RIGHT:
//            qDebug() << "status: crawl right";
            MainWindow::uiSerialHandler.sendCmdViaSerialPort("kcrR");
            break;

        case STATUS_RUN_FORWARD:
//            qDebug() << "status: run forward";
            MainWindow::uiSerialHandler.sendCmdViaSerialPort("ktrF");
            break;

        case STATUS_RUN_BACKWARD:
//            qDebug() << "status: backward";
            MainWindow::uiSerialHandler.sendCmdViaSerialPort("kbk");
            break;

        case STATUS_RUN_LEFT:
//            qDebug() << "status: run left";
            MainWindow::uiSerialHandler.sendCmdViaSerialPort("ktrL");
            break;

        case STATUS_RUN_RIGHT:
//            qDebug() << "status: run right";
            MainWindow::uiSerialHandler.sendCmdViaSerialPort("ktrR");
            break;

        case STATUS_NORMAL_FORWARD:
//            qDebug() << "status: forward";
            MainWindow::uiSerialHandler.sendCmdViaSerialPort("kwkF");
            break;

        case STATUS_NORMAL_BACKWARD:
//            qDebug() << "status: backward";
            MainWindow::uiSerialHandler.sendCmdViaSerialPort("kbk");
            break;

        case STATUS_NORMAL_LEFT:
//            qDebug() << "status: left";
            MainWindow::uiSerialHandler.sendCmdViaSerialPort("kwkL");
            break;

        case STATUS_NORMAL_RIGHT:
//            qDebug() << "status: right";
            MainWindow::uiSerialHandler.sendCmdViaSerialPort("kwkR");
            break;

        default:
//            qDebug() << "status: balance";
            MainWindow::uiSerialHandler.sendCmdViaSerialPort("kbalance");
            break;
        }

        motionStatus = updated;
    }
}


void UiMotionControl::startKeyListen() {
    // connect timer signal/slot
    connect(&timer, SIGNAL(timeout()), this, SLOT(usbDevicesEventCheck()));
    
    // start timer
    if (!timer.isActive()) {
        timer.start(REPEAT_MILLISECONDS); 
    }

    // debug message
    qDebug() << "Start motion control...";
}


void UiMotionControl::stopKeyListen() {
    
    // stop timer
    if (timer.isActive()) { 
        timer.stop(); 
    }

    // disconnect
    disconnect(&timer, SIGNAL(timeout()), this, SLOT(usbDevicesEventCheck()));

    // debug message
    qDebug() << "Stop motion control...";
 }


bool UiMotionControl::isKeyListeningOn() {
    return timer.isActive();
}


void UiMotionControl::procQtKeyPressedEvent(QKeyEvent* key) {

    switch(key->key()) {
    case Qt::Key_W:
        moveFront = true;
        moveBack = false;
        break;

    case Qt::Key_S:
        moveBack = true;
        moveFront = false;
        break;

    case Qt::Key_A:
        moveLeft = true;
        moveRight = false;
        break;

    case Qt::Key_D:
        moveRight = true;
        moveLeft = false;
        break;

    case Qt::Key_1: // normal
        crawlActivated = runActivated = false;
        break;

    case Qt::Key_2: // run
        runActivated = true;
        break;

    case Qt::Key_3: // crawl
        crawlActivated = true;
        break;

    default:
        break;
    }
};


void UiMotionControl::procQtKeyReleasedEvent(QKeyEvent* key) {

    switch(key->key()) {
     case Qt::Key_W:
         moveFront = false;
         break;

     case Qt::Key_S:
         moveBack = false;
         break;

     case Qt::Key_A:
         moveLeft = false;
         break;

     case Qt::Key_D:
         moveRight = false;
         break;

     default:
         break;
     }
};
