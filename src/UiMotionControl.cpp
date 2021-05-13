#include "UiMotionControl.h"
#include "MainWindow.h"

#include <QDebug>


UiMotionControl::UiMotionControl(QObject *parent) :
    QObject(parent),
    timer() {

    // connect timer signal/slot
    connect(&timer, SIGNAL(timeout()), this, SLOT(usbDevicesEventCheck()));

    // start to listen usb devices events
    if (!timer.isActive()) {
        timer.start(REPEAT_MILLISECONDS);
    }
}


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

    case PosSleep:
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
            qDebug() << "status: kcrF";
            MainWindow::uiSerialHandler.sendCmdViaSerialPort("kcrF");
            break;

        case STATUS_CRAWL_BACKWARD:
            qDebug() << "status: kbk";
            MainWindow::uiSerialHandler.sendCmdViaSerialPort("kbk");
            break;

        case STATUS_CRAWL_LEFT:
            qDebug() << "status: kcrL";
            MainWindow::uiSerialHandler.sendCmdViaSerialPort("kcrL");
            break;

        case STATUS_CRAWL_RIGHT:
            qDebug() << "status: kcrR";
            MainWindow::uiSerialHandler.sendCmdViaSerialPort("kcrR");
            break;

        case STATUS_RUN_FORWARD:
            qDebug() << "status: ktrF";
            MainWindow::uiSerialHandler.sendCmdViaSerialPort("ktrF");
            break;

        case STATUS_RUN_BACKWARD:
            qDebug() << "status: kbk";
            MainWindow::uiSerialHandler.sendCmdViaSerialPort("kbk");
            break;

        case STATUS_RUN_LEFT:
            qDebug() << "status: ktrL";
            MainWindow::uiSerialHandler.sendCmdViaSerialPort("ktrL");
            break;

        case STATUS_RUN_RIGHT:
            qDebug() << "status: ktrR";
            MainWindow::uiSerialHandler.sendCmdViaSerialPort("ktrR");
            break;

        case STATUS_NORMAL_FORWARD:
            qDebug() << "status: kwkF";
            MainWindow::uiSerialHandler.sendCmdViaSerialPort("kwkF");
            break;

        case STATUS_NORMAL_BACKWARD:
            qDebug() << "status: kbk";
            MainWindow::uiSerialHandler.sendCmdViaSerialPort("kbk");
            break;

        case STATUS_NORMAL_LEFT:
            qDebug() << "status: kwkL";
            MainWindow::uiSerialHandler.sendCmdViaSerialPort("kwkL");
            break;

        case STATUS_NORMAL_RIGHT:
            qDebug() << "status: kwkR";
            MainWindow::uiSerialHandler.sendCmdViaSerialPort("kwkR");
            break;

        default:
            qDebug() << "status: kbalance";
            MainWindow::uiSerialHandler.sendCmdViaSerialPort("kbalance");
            break;
        }

        motionStatus = updated;
    }
}


void UiMotionControl::procQtKeyPressedEvent(QKeyEvent* key) {
    switch(key->key()) {
    case Qt::Key_W:
        qDebug() << "pressed W";
        moveFront = true;
        moveBack = false;
        break;

    case Qt::Key_S:
        qDebug() << "pressed S";
        moveBack = true;
        moveFront = false;
        break;

    case Qt::Key_A:
        qDebug() << "pressed A";
        moveLeft = true;
        moveRight = false;
        break;

    case Qt::Key_D:
        qDebug() << "pressed D";
        moveRight = true;
        moveLeft = false;
        break;

    case Qt::Key_U: // normal
        crawlActivated = runActivated = false;
        qDebug() << "pressed U";
        break;

    case Qt::Key_I: // run
        qDebug() << "pressed shift";
        runActivated = true;
        break;

    case Qt::Key_O: // crawl
        qDebug() << "pressed control";
        crawlActivated = true;
        break;

    case Qt::Key_Backspace:
        qDebug() << "pressed backspace";
        motionStatus = STATUS_READY;
        break;

    case Qt::Key_G:
        qDebug() << "pressed G";
        MainWindow::uiSerialHandler.sendCmdViaSerialPort("g");
        break;

    default:
        break;
    }
};


void UiMotionControl::procQtKeyReleasedEvent(QKeyEvent* key) {
    switch(key->key()) {
     case Qt::Key_W:
         moveFront = false;
         qDebug() << "released up";
         break;

     case Qt::Key_S:
         moveBack = false;
         qDebug() << "released down";
         break;

     case Qt::Key_A:
         moveLeft = false;
         qDebug() << "released left";
         break;

     case Qt::Key_D:
         moveRight = false;
         qDebug() << "released right";
         break;

     default:
         break;
     }
};
