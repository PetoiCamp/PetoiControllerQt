#include "ui/mainwindow.h"
#include "ui_mainwindow.h"
#include "ui/logger.h"

#include <QMessageBox>
#include <QDebug>
#include <QThread>
#include <QFileDialog>


void MainWindow::initPort()
{
    QStringList baudList;       // baud rates
    QStringList parityList;     // parities
    QStringList dataBitsList;   // data bits
    QStringList stopBitsList;   // stop bits

    QStringList steeringList;   // steerings

    // 1. baud rates
    initBaudRates(baudList);
    ui->boxBaudRate->addItems(baudList);

    // 2. parity
    initParities(parityList);
    ui->boxParity->addItems(parityList);

    // 3. data bits
    initDataBits(dataBitsList);
    ui->boxDataBits->addItems(dataBitsList);

    // 4. stop bits
    initStopBits(stopBitsList);
    ui->boxStopBits->addItems(stopBitsList);

    // 5. steering motors
    initSteerings(steeringList);
    ui->boxSteering->addItems(steeringList);
}


void MainWindow::onRecvMsgViaSerial()
{
    auto msg = helper->recv();

    if (!stack->isEmpty()) {

        // update token value
        auto topCmd = stack->popupToken();
        topCmd.second = msg;

        // push updated token back to stack
        stack->pushToken(topCmd);
        stack->debugStack();
    }

    // update the textbrowser
    ui->textBrowserTerminal->clear();
    ui->textBrowserTerminal->setText(msg);
}



void MainWindow::onSendButtonPressed()
{
    stack->sendCmdViaSerial(ui->lineEdit->text());

    // clean up the line
    ui->lineEdit->clear();
}


void MainWindow::onEnterButtonPressed()
{
    if (ui->lineEdit->hasFocus()) {
        stack->sendCmdViaSerial(ui->lineEdit->text());
        ui->lineEdit->clear();
    }
}


void MainWindow::onRefreshDevicesButtonPressed()
{
    auto names = helper->searchPorts();

    // clean port box
    ui->boxPortNumber->clear();

    // add new ports to box
    if (names.count() > 0)
    {
        for (auto& port: names)
        {
            ui->boxPortNumber->addItem(port);
        }
    } else {
        QMessageBox::information(this, tr("Info"), tr("No available serial ports found"));
    }
};


void MainWindow::onConnectRemoteButtonPressed()
{
    if (ui->buttonConnect->text() == tr("打开串口"))
    {
        // derive properties from comboxes
        QString portName = ui->boxPortNumber->currentText();
        qint32                  btr = serialBaudRatesList[ui->boxBaudRate->currentIndex()].second;
        QSerialPort::StopBits   stp = serialStopBitsList[ui->boxStopBits->currentIndex()].second;
        QSerialPort::DataBits   dbs = serialDataBitsList[ui->boxDataBits->currentIndex()].second;
        QSerialPort::Parity     pty = serialParitiesList[ui->boxParity->currentIndex()].second;

        // setup serial properties
        helper->connect(portName, btr, dbs, stp, pty);

        // if connection is available
        if(helper->available())
        {
            // update serial relative widget
            ui->buttonConnect->setText(tr("关闭串口"));
            ui->boxPortNumber->setEnabled(false);
            ui->boxBaudRate->setEnabled(false);
            ui->boxStopBits->setEnabled(false);
            ui->boxDataBits->setEnabled(false);
            ui->boxParity->setEnabled(false);
            ui->buttonSendCmd->setEnabled(true);
            ui->buttonRefresh->setEnabled(false);

            // update steerings relative widgets
            ui->buttonCalibration->setEnabled(true);

            // open actions panel
            ui->tabPanel->setEnabled(true);
        }
        else
        {
            QMessageBox::critical(this, tr("Error"), helper->errormsg());
        }
    }
    else
    {
        // disconnect to remote device
        helper->disconnect();

        // serial adjusting widgets
        ui->buttonConnect->setText(tr("打开串口"));

        ui->buttonSendCmd->setEnabled(false);
        ui->boxPortNumber->setEnabled(true);
        ui->boxBaudRate->setEnabled(true);
        ui->boxStopBits->setEnabled(true);
        ui->boxDataBits->setEnabled(true);
        ui->boxParity->setEnabled(true);
        ui->buttonRefresh->setEnabled(true);

        // update steerings relative widgets
        ui->buttonCalibration->setText(tr("开始校准"));

        ui->buttonCalibration->setEnabled(false);
        ui->buttonSavePos->setEnabled(false);
        ui->buttonInAngle->setEnabled(false);
        ui->buttonDeAngle->setEnabled(false);
        ui->boxSteering->setEnabled(false);
        ui->buttonCleanPos->setEnabled(false);

        // disable actions panel
        ui->tabPanel->setEnabled(false);
    }
}


void MainWindow::onCalibrationButtonPressed()
{
    if (ui->buttonCalibration->text() == tr("开始校准")) {
        stack->sendCmdViaSerial("c");
        ui->buttonCalibration->setText(tr("加载数据"));
        ui->boxSteering->setEnabled(false);
        ui->buttonInAngle->setEnabled(false);
        ui->buttonDeAngle->setEnabled(false);
        ui->buttonSavePos->setEnabled(false);
        ui->buttonCleanPos->setEnabled(false);
    } else if (ui->buttonCalibration->text() == tr("加载数据")) {
//        angle = 0;
        stack->calibrationFeedbackCheck();

        ui->boxSteering->setEnabled(true);
        ui->buttonInAngle->setEnabled(true);
        ui->buttonDeAngle->setEnabled(true);
        ui->buttonSavePos->setEnabled(true);
        ui->buttonCleanPos->setEnabled(true);

        ui->buttonCalibration->setEnabled(false);
    }
};


void MainWindow::onSaveAnglesButtonPressed()
{
    ui->buttonCalibration->setEnabled(true);
    ui->buttonCalibration->setText(tr("开始校准"));

    ui->boxSteering->setEnabled(false);
    ui->buttonInAngle->setEnabled(false);
    ui->buttonDeAngle->setEnabled(false);
    ui->buttonSavePos->setEnabled(false);
    ui->buttonCleanPos->setEnabled(false);

    // save back to stack
//    for (int i = 0; i < MOTORS; i++) {
//        stack->motors[i] = motors[i];
//    }

    stack->sendCmdViaSerial("s");
};


void MainWindow::onSteeringChanged(int value)
{
//    angle = 0;
    LOG_DEBUG() << "selected motor " << steeringMotorList[value].second;
};


void MainWindow::onIncreaseFineTunne()
{
    // prepare fine tunne command
    QString cmotor = steeringMotorList[ui->boxSteering->currentIndex()].second;
    auto motor_id = cmotor.toInt();

    // increase by 1
    stack->motors[motor_id] += 1;

    // check valid angle
    if (stack->motors[motor_id] > 9) {
        QMessageBox::warning(this, tr("Error"), tr("已达到最大微调角度"));
        stack->motors[motor_id] = 9;
        return;
    }

    // generate final command
    QString m_angle = QString("c%1 %2").arg(cmotor).arg(stack->motors[motor_id]);

    // send fine angle to remote via serial
    stack->sendCmdViaSerial(m_angle);
};


void MainWindow::onDecreaseFineTunne()
{
    // prepare fine tunne command
    QString cmotor = steeringMotorList[ui->boxSteering->currentIndex()].second;
    auto motor_id = cmotor.toInt();

    // increase by 1
    stack->motors[motor_id] -= 1;

    // check valid angle
    if (stack->motors[motor_id] < -9) {
        QMessageBox::warning(this, tr("Error"), tr("已达到最大微调角度"));
        stack->motors[motor_id] = -9;
        return;
    }

    // generate final command
    QString m_angle = QString("c%1 %2").arg(cmotor).arg(stack->motors[motor_id]);

    // send fine angle to remote via serial
    stack->sendCmdViaSerial(m_angle);

};


void MainWindow::onClearupButtonPressed()
{
    // prepare fine tunne command
    QString cmotor = steeringMotorList[ui->boxSteering->currentIndex()].second;
    auto motor_id = cmotor.toInt();

    // set servo to zero
    stack->motors[motor_id] = 0;

    // generate final command
    QString m_angle = QString("c%1 %2").arg(cmotor).arg(stack->motors[motor_id]);

    // send fine angle to remote via serial
    stack->sendCmdViaSerial(m_angle);
}
