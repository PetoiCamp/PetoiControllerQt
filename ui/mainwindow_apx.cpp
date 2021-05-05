#include "ui/mainwindow.h"
#include "ui_mainwindow.h"


void MainWindow::initBaudRates(QStringList &baudList)
{
    serialBaudRatesList.append(QPair<QString, qint32>("1200", QSerialPort::Baud1200));
    serialBaudRatesList.append(QPair<QString, qint32>("2400", QSerialPort::Baud2400));
    serialBaudRatesList.append(QPair<QString, qint32>("4800", QSerialPort::Baud4800));
    serialBaudRatesList.append(QPair<QString, qint32>("9600", QSerialPort::Baud9600));
    serialBaudRatesList.append(QPair<QString, qint32>("19200", QSerialPort::Baud19200));
    serialBaudRatesList.append(QPair<QString, qint32>("38400", QSerialPort::Baud38400));
    serialBaudRatesList.append(QPair<QString, qint32>("57600", QSerialPort::Baud57600));
    serialBaudRatesList.append(QPair<QString, qint32>("115200", QSerialPort::Baud115200));


    QList<QPair<QString, qint32>>::Iterator it = serialBaudRatesList.begin();
    while(it != serialBaudRatesList.end())
    {
        baudList << it->first;
        it++;
    }
}


void MainWindow::initStopBits(QStringList& stopBits)
{
    serialStopBitsList.append(QPair<QString, QSerialPort::StopBits>("0", QSerialPort::UnknownStopBits));
    serialStopBitsList.append(QPair<QString, QSerialPort::StopBits>("1", QSerialPort::OneStop));
    serialStopBitsList.append(QPair<QString, QSerialPort::StopBits>("2", QSerialPort::TwoStop));

    QList<QPair<QString, QSerialPort::StopBits>>::Iterator it = serialStopBitsList.begin();
    while(it != serialStopBitsList.end())
    {
        stopBits << it->first;
        it++;
    }
};


void MainWindow::initParities(QStringList& paritis)
{
    serialParitiesList.append(QPair<QString, QSerialPort::Parity>(tr("None"), QSerialPort::NoParity));
    serialParitiesList.append(QPair<QString, QSerialPort::Parity>(tr("Odd"), QSerialPort::EvenParity));
    serialParitiesList.append(QPair<QString, QSerialPort::Parity>(tr("Even"), QSerialPort::OddParity));

    QList<QPair<QString, QSerialPort::Parity>>::Iterator it = serialParitiesList.begin();
    while(it != serialParitiesList.end())
    {
        paritis << it->first;
        it++;
    }
};


void MainWindow::initDataBits(QStringList& dataBits)
{
    serialDataBitsList.append(QPair<QString, QSerialPort::DataBits>("5", QSerialPort::Data5));
    serialDataBitsList.append(QPair<QString, QSerialPort::DataBits>("6", QSerialPort::Data6));
    serialDataBitsList.append(QPair<QString, QSerialPort::DataBits>("7", QSerialPort::Data7));
    serialDataBitsList.append(QPair<QString, QSerialPort::DataBits>("8", QSerialPort::Data8));

    QList<QPair<QString, QSerialPort::DataBits>>::Iterator it =  serialDataBitsList.begin();
    while(it != serialDataBitsList.end())
    {
        dataBits << it->first;
        it++;
    }
};


void MainWindow::initSteerings(QStringList &steerings)
{
    steeringMotorList.append(QPair<QString, QString>(tr("Servo 0"), "0"));

    steeringMotorList.append(QPair<QString, QString>(tr("Servo 8"), "8"));
    steeringMotorList.append(QPair<QString, QString>(tr("Servo 9"), "9"));
    steeringMotorList.append(QPair<QString, QString>(tr("Servo 10"), "10"));
    steeringMotorList.append(QPair<QString, QString>(tr("Servo 11"), "11"));

    steeringMotorList.append(QPair<QString, QString>(tr("Servo 12"), "12"));
    steeringMotorList.append(QPair<QString, QString>(tr("Servo 13"), "13"));
    steeringMotorList.append(QPair<QString, QString>(tr("Servo 14"), "14"));
    steeringMotorList.append(QPair<QString, QString>(tr("Servo 15"), "15"));

    QList<QPair<QString, QString>>::Iterator it = steeringMotorList.begin();
    while(it != steeringMotorList.end())
    {
        steerings << it->first;
        it++;
    }
}


void MainWindow::bindQtSlots()
{
    /**
     * serial ports and communications
     */
    connect(ui->buttonConnect, SIGNAL(clicked(bool)), this, SLOT(onConnectRemoteButtonPressed()));
    connect(ui->buttonRefresh, SIGNAL(clicked(bool)), this, SLOT(onRefreshDevicesButtonPressed()));

    /**
     * calibrations
     */
    connect(ui->buttonCalibration, SIGNAL(clicked(bool)), this, SLOT(onCalibrationButtonPressed()));
    connect(ui->buttonSavePos, SIGNAL(clicked(bool)), this, SLOT(onSaveAnglesButtonPressed()));
    connect(ui->buttonInAngle, SIGNAL(clicked(bool)), this, SLOT(onIncreaseFineTunne()));
    connect(ui->buttonDeAngle, SIGNAL(clicked(bool)), this, SLOT(onDecreaseFineTunne()));
    connect(ui->buttonCleanPos, SIGNAL(clicked(bool)), this, SLOT(onClearupButtonPressed()));
    connect(ui->boxSteering, SIGNAL(currentIndexChanged(int)), this, SLOT(onSteeringChanged(int)));

    /**
     * terminal
     */
    connect(ui->buttonSendCmd, SIGNAL(clicked(bool)), this, SLOT(onSendButtonPressed()));
    connect(ui->lineEdit, SIGNAL(editingFinished()), this, SLOT(onEnterButtonPressed()));
    connect(helper->getInstance(), SIGNAL(readyRead()), this, SLOT(onRecvMsgViaSerial()));

    /**
     * menus and actions
     */
    connect(exitAct, SIGNAL(triggered(bool)), this, SLOT(exitApp()));
    connect(englishTypeAct, SIGNAL(triggered(bool)), SLOT(showAsEng()));
    connect(chineseTypeAct, SIGNAL(triggered(bool)), this, SLOT(showAsChn()));

    /**
     * motions and postures
     */
    connect(ui->buttonPosBackFlip, SIGNAL(clicked(bool)), this, SLOT(posBackFlip()));
    connect(ui->buttonPosButtomUp, SIGNAL(clicked(bool)), this, SLOT(posButtomUp()));
    connect(ui->buttonPosCheckRd, SIGNAL(clicked(bool)), this, SLOT(posCheckAround()));
    connect(ui->buttonPosHi, SIGNAL(clicked(bool)), this, SLOT(posGreeting()));
    connect(ui->buttonPosPee, SIGNAL(clicked(bool)), this, SLOT(posPee()));
    connect(ui->buttonPosPushUp, SIGNAL(clicked(bool)), this, SLOT(posPushup()));
    connect(ui->buttonPosRest, SIGNAL(clicked(bool)), this, SLOT(posRest()));
    connect(ui->buttonPosSit, SIGNAL(clicked(bool)), this, SLOT(posSitdown()));
    connect(ui->buttonPosSleep, SIGNAL(clicked(bool)), this, SLOT(posSleep()));
    connect(ui->buttonPosStretch, SIGNAL(clicked(bool)), this, SLOT(posStretch()));
    connect(ui->buttonPosBunnyJump, SIGNAL(clicked(bool)), this, SLOT(posBunnyJump()));
    connect(ui->buttonPosStepping, SIGNAL(clicked(bool)), this, SLOT(posStepping()));

    /**
     * global controlling panel
     */
    connect(ui->buttonCtrlBalance, SIGNAL(clicked(bool)), this, SLOT(panelBalance()));
    connect(ui->buttonCtrlGyro, SIGNAL(clicked(bool)), this, SLOT(panelGyro()));
    connect(ui->buttonCtrlRestPos, SIGNAL(clicked(bool)), this, SLOT(panelRecovery()));
    connect(ui->buttonCtrlServos, SIGNAL(clicked(bool)), this, SLOT(panelServos()));

    /**
      * keyboard event interval checker
      */
    connect(eventTimer, SIGNAL(timeout()), this, SLOT(intervalEventChecker()));
}
