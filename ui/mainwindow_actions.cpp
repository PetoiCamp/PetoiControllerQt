#include "ui/mainwindow.h"


void MainWindow::posButtomUp() {
    stack->sendCmdViaSerial("kbuttUp");
    runningStatus = STATUS_READY;
};

void MainWindow::posCheckAround() {
    stack->sendCmdViaSerial("kck");
    runningStatus = STATUS_READY;
};

void MainWindow::posStretch() {
    stack->sendCmdViaSerial("kstr");
    runningStatus = STATUS_READY;
};

void MainWindow::posGreeting() {
    stack->sendCmdViaSerial("khi");
    runningStatus = STATUS_READY;
};

void MainWindow::posPee() {
    stack->sendCmdViaSerial("kpee");
    runningStatus = STATUS_READY;
};

void MainWindow::posPushup() {
    stack->sendCmdViaSerial("kpu");
    runningStatus = STATUS_READY;
};

void MainWindow::posRest() {
    stack->sendCmdViaSerial("krest");
    runningStatus = STATUS_READY;
};

void MainWindow::posSleep() {
    stack->sendCmdViaSerial("kstp");
    runningStatus = STATUS_READY;
};

void MainWindow::posBackFlip() {
    stack->sendCmdViaSerial("kbf");
    runningStatus = STATUS_READY;
};

void MainWindow::posSitdown() {
    stack->sendCmdViaSerial("ksit");
    runningStatus = STATUS_READY;
};

void MainWindow::posBunnyJump() {
    stack->sendCmdViaSerial("kbdF");
    runningStatus = STATUS_READY;
}

void MainWindow::posStepping() {
    stack->sendCmdViaSerial("kvt");
    runningStatus = STATUS_READY;
}

int MainWindow::updateStatus() {
    if (!moveFront && !moveBack && !moveLeft && !moveRight && !ctrlActivated && !shiftActivated) {
        return STATUS_READY;
    }

    if (!moveFront && !moveBack && !moveLeft && !moveRight && shiftActivated) {
        return STATUS_STANDBY;
    }

    if (ctrlActivated && moveFront) {
        return STATUS_CRAWL_FORWARD;
    }

    if (ctrlActivated && moveBack) {
        return STATUS_CRAWL_BACKWARD;
    }

    if (ctrlActivated && moveLeft) {
        return STATUS_CRAWL_LEFT;
    }

    if (ctrlActivated && moveRight) {
        return STATUS_CRAWL_RIGHT;
    }

    if (shiftActivated && moveFront) {
        return STATUS_RUN_FORWARD;
    }

    if (shiftActivated && moveBack) {
        return STATUS_RUN_BACKWARD;
    }

    if (shiftActivated && moveLeft) {
        return STATUS_RUN_LEFT;
    }

    if (shiftActivated && moveRight) {
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

void MainWindow::intervalEventChecker() {
    if (runningStatus == updateStatus()) {// nothing have changed
        return;
    } else {
        int updated = updateStatus();
        switch (updated) {
        case STATUS_READY:
            LOG_DEBUG() << "status: kbalance";
            stack->sendCmdViaSerial("kbalance");
            break;

        case STATUS_STANDBY:
            LOG_DEBUG() << "status: kvt";
            stack->sendCmdViaSerial("kvt");
            break;

        case STATUS_CRAWL_FORWARD:
            LOG_DEBUG() << "status: kcrF";
            stack->sendCmdViaSerial("kcrF");
            break;

        case STATUS_CRAWL_BACKWARD:
            LOG_DEBUG() << "status: kbk";
            stack->sendCmdViaSerial("kbk");
            break;

        case STATUS_CRAWL_LEFT:
            LOG_DEBUG() << "status: kcrL";
            stack->sendCmdViaSerial("kcrL");
            break;

        case STATUS_CRAWL_RIGHT:
            LOG_DEBUG() << "status: kcrR";
            stack->sendCmdViaSerial("kcrR");
            break;

        case STATUS_RUN_FORWARD:
            LOG_DEBUG() << "status: ktrF";
            stack->sendCmdViaSerial("ktrF");
            break;

        case STATUS_RUN_BACKWARD:
            LOG_DEBUG() << "status: kbk";
            stack->sendCmdViaSerial("kbk");
            break;

        case STATUS_RUN_LEFT:
            LOG_DEBUG() << "status: ktrL";
            stack->sendCmdViaSerial("ktrL");
            break;

        case STATUS_RUN_RIGHT:
            LOG_DEBUG() << "status: ktrR";
            stack->sendCmdViaSerial("ktrR");
            break;

        case STATUS_NORMAL_FORWARD:
            LOG_DEBUG() << "status: kwkF";
            stack->sendCmdViaSerial("kwkF");
            break;

        case STATUS_NORMAL_BACKWARD:
            LOG_DEBUG() << "status: kbk";
            stack->sendCmdViaSerial("kbk");
            break;

        case STATUS_NORMAL_LEFT:
            LOG_DEBUG() << "status: kwkL";
            stack->sendCmdViaSerial("kwkL");
            break;

        case STATUS_NORMAL_RIGHT:
            LOG_DEBUG() << "status: kwkR";
            stack->sendCmdViaSerial("kwkR");
            break;

        default:
            break;
        }

        runningStatus = updated;
    }
};
