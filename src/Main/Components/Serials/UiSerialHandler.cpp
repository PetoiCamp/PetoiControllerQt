#include "UiSerialHandler.h"
#include "src/Main/MainWindow.h"

#include <QDebug>
#include <QString>
#include <QSerialPortInfo>
#include <QSerialPort>


UiSerialHandler::UiSerialHandler(QObject* parent):
    QObject(parent), timer(), queue() {}


UiSerialHandler::~UiSerialHandler() {}



void UiSerialHandler::setupSerialParametersSelections(
        QComboBox *ports, QComboBox *baud,
        QComboBox *parity, QComboBox *dataBits,
        QComboBox *stopBits) {

    QStringList portsList;      // ports
    QStringList baudList;       // baud rates
    QStringList parityList;     // parities
    QStringList dataBitsList;   // data bits
    QStringList stopBitsList;   // stop bits

    // 1. ports
    initPorts(portsList);
    ports->addItems(portsList);

    // 2. baud rates
    initBaudRates(baudList);
    baud->addItems(baudList);

    // 3. parity
    initParities(parityList);
    parity->addItems(parityList);

    // 4. data bits
    initDataBits(dataBitsList);
    dataBits->addItems(dataBitsList);

    // 5. stop bits
    initStopBits(stopBitsList);
    stopBits->addItems(stopBitsList);
};


void UiSerialHandler::clearSerialParametersSelections(
        QComboBox *ports,
        QComboBox *baud,
        QComboBox *parity,
        QComboBox *dataBits,
        QComboBox *stopBits) {

    // clear list
    serialBaudRatesList.clear();
    serialDataBitsList.clear();
    serialParitiesList.clear();
    serialStopBitsList.clear();

    // clear combox
    ports->clear();
    baud->clear();
    parity->clear();
    dataBits->clear();
    stopBits->clear();
};


void UiSerialHandler::connectSerial(QString port, int baud,
                              int databits, int stopbits, int parity) {

    qint32                  baudRate = serialBaudRatesList[baud].second;
    QSerialPort::DataBits   dataBits = serialDataBitsList[databits].second;
    QSerialPort::StopBits   stopBits = serialStopBitsList[stopbits].second;
    QSerialPort::Parity     parties = serialParitiesList[parity].second;

    // connect to the serial port
    queue.connect(port, baudRate, dataBits, stopBits, parties);
};


void UiSerialHandler::disconnectSerial() {

    // disconnect from the serial port
    queue.disconnect();
}


void UiSerialHandler::bindFeedbackTextview(QTextBrowser *browser) {

    // set browser ptr
    textview_ptr = browser;

    // connect timer signal/slot
    connect(&timer, SIGNAL(timeout()), this, SLOT(onUpdateTextview()));

    // run timer, and let UiSerialHandler every 10ms check the message via serial port
    if (!timer.isActive()) {
        timer.start(10);
    }
}


void UiSerialHandler::unbindFeedbackTextview() {

    // set browser ptr to nullptr
    textview_ptr = nullptr;

    // disconnect timer signal/slot
    disconnect(&timer, SIGNAL(timeout()), this, SLOT(onUpdateTextview()));

    // stop timer
    if (timer.isActive()) {
        timer.stop();
    }
}


void UiSerialHandler::onUpdateTextview() {
    if (textview_ptr != nullptr) {

        QString plantText = textview_ptr->toPlainText();
        char buffer[1024] = { 0 };

        int result = queue.recvViaSerial((unsigned char*)buffer, 1024);
        if (result > 0) {

            // update output
            QString feedback(buffer);
            feedback = plantText + feedback;
            textview_ptr->setText(feedback);

            if (isCalibrated) {
                MainWindow::uiCalibration.updateCalibrationInfo(feedback);
            }
        }
    }
};


void UiSerialHandler::sendCmdViaSerialPort(QString cmd) {

    std::string msg = cmd.toStdString();
    queue.sendViaSerial((unsigned char*)msg.c_str(), msg.length());

    // user sent "c"
    isCalibrated = msg == "c" ? true : false;

    // clear output
    if (textview_ptr) {
        textview_ptr->clear();
    }
}


void UiSerialHandler::initPorts(QStringList &portList) {
    auto names = queue.searchPorts();

    QList<QString>::Iterator it = names.begin();
    while(it != names.end()) {
        portList << *it;
        it++;
    }
}


void UiSerialHandler::initBaudRates(QStringList &baudList) {
    serialBaudRatesList.append(QPair<QString, qint32>("1200", QSerialPort::Baud1200));
    serialBaudRatesList.append(QPair<QString, qint32>("2400", QSerialPort::Baud2400));
    serialBaudRatesList.append(QPair<QString, qint32>("4800", QSerialPort::Baud4800));
    serialBaudRatesList.append(QPair<QString, qint32>("9600", QSerialPort::Baud9600));
    serialBaudRatesList.append(QPair<QString, qint32>("19200", QSerialPort::Baud19200));
    serialBaudRatesList.append(QPair<QString, qint32>("38400", QSerialPort::Baud38400));
    serialBaudRatesList.append(QPair<QString, qint32>("57600", QSerialPort::Baud57600));
    serialBaudRatesList.append(QPair<QString, qint32>("115200", QSerialPort::Baud115200));


    QList<QPair<QString, qint32>>::Iterator it = serialBaudRatesList.begin();
    while(it != serialBaudRatesList.end()) {
        baudList << it->first;
        it++;
    }
};


void UiSerialHandler::initStopBits(QStringList &stopBits) {
    serialStopBitsList.append(QPair<QString, QSerialPort::StopBits>("0", QSerialPort::UnknownStopBits));
    serialStopBitsList.append(QPair<QString, QSerialPort::StopBits>("1", QSerialPort::OneStop));
    serialStopBitsList.append(QPair<QString, QSerialPort::StopBits>("2", QSerialPort::TwoStop));

    QList<QPair<QString, QSerialPort::StopBits>>::Iterator it = serialStopBitsList.begin();
    while(it != serialStopBitsList.end()) {
        stopBits << it->first;
        it++;
    }
};


void UiSerialHandler::initParities(QStringList &paritis) {
    serialParitiesList.append(QPair<QString, QSerialPort::Parity>(tr("None"), QSerialPort::NoParity));
    serialParitiesList.append(QPair<QString, QSerialPort::Parity>(tr("Odd"), QSerialPort::EvenParity));
    serialParitiesList.append(QPair<QString, QSerialPort::Parity>(tr("Even"), QSerialPort::OddParity));

    QList<QPair<QString, QSerialPort::Parity>>::Iterator it = serialParitiesList.begin();
    while(it != serialParitiesList.end()) {
        paritis << it->first;
        it++;
    }
};


void UiSerialHandler::initDataBits(QStringList &dataBits) {
    serialDataBitsList.append(QPair<QString, QSerialPort::DataBits>("5", QSerialPort::Data5));
    serialDataBitsList.append(QPair<QString, QSerialPort::DataBits>("6", QSerialPort::Data6));
    serialDataBitsList.append(QPair<QString, QSerialPort::DataBits>("7", QSerialPort::Data7));
    serialDataBitsList.append(QPair<QString, QSerialPort::DataBits>("8", QSerialPort::Data8));

    QList<QPair<QString, QSerialPort::DataBits>>::Iterator it =  serialDataBitsList.begin();
    while(it != serialDataBitsList.end()) {
        dataBits << it->first;
        it++;
    }
};
