#include "ui/mainwindow.h"
#include "ui_mainwindow.h"


void MainWindow::panelBalance() {
    stack->sendCmdViaSerial("kbalance");
};

void MainWindow::panelPause() {
    stack->sendCmdViaSerial("p");
};

void MainWindow::panelRecovery() {
    stack->sendCmdViaSerial("krc");
};

void MainWindow::panelGyro() {
    if (ui->buttonCtrlGyro->text() == tr("关闭陀螺仪")) {
        ui->buttonCtrlGyro->setText(tr("恢复陀螺仪"));
    } else {
        ui->buttonCtrlGyro->setText(tr("关闭陀螺仪"));
    }
    stack->sendCmdViaSerial("g");
};

void MainWindow::panelServos() {
    if (ui->buttonCtrlServos->text() == tr("关闭舵机")) {
        ui->buttonCtrlServos->setText(tr("恢复舵机"));
    } else {
        ui->buttonCtrlServos->setText(tr("关闭舵机"));
    }

    stack->sendCmdViaSerial("d");
};
