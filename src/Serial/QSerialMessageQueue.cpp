#include "QSerialMessageQueue.h"
#include <math.h>
#include <QDebug>


QSerialMessageQueue::QSerialMessageQueue(QObject *parent) : QObject(parent), serial() {}


void QSerialMessageQueue::connect(
        QString portName,
        qint32 baudRate,
        QSerialPort::DataBits dataBits,
        QSerialPort::StopBits stopBits,
        QSerialPort::Parity parity) {

    serial.setPortName(portName);
    serial.setBaudRate(baudRate);
    serial.setStopBits(stopBits);
    serial.setDataBits(dataBits);
    serial.setParity(parity);

    // connect to remote device via serial port
    serial.open(QIODevice::ReadWrite);

    // connect to qt signal/slot
    QObject::connect(&serial, SIGNAL(readyRead()), this, SLOT(onSerialAutoRecv()));
}


void QSerialMessageQueue::disconnect() {
    // disconnect to qt signal/slot
    QObject::disconnect(&serial, SIGNAL(readyRead()), this, SLOT(onSerialAutoRecv()));

    // clear up serial buffer and close connection
    serial.clear();
    serial.close();
}


int QSerialMessageQueue::sendViaSerial(unsigned char *bytes, int sentSize) {
    return serial.write((char*)bytes, sentSize);
}


int QSerialMessageQueue::recvViaSerial(unsigned char *bytes, int maxSize) {
    if (queue.size() > 0) {
        std::shared_ptr<RawMessage> shared_ptr = queue.first();
        int result = shared_ptr->copy(bytes, maxSize);
        queue.pop_front();
        return result;
    }

    // failed
    return -1;
}


void QSerialMessageQueue::clearBuffer() {
    queue.clear();
}


void QSerialMessageQueue::onSerialAutoRecv() {
    auto buf = serial.readAll();

    if (!buf.isEmpty()) {
        char* data = buf.data();
        auto len = buf.length();

        // copy and wrap
        if (data && len > 0) {

            RawMessage* ptr = new RawMessage((unsigned char*)data, len);

            std::shared_ptr<RawMessage> shared_ptr(ptr);
            queue.push_back(shared_ptr);
        }
    }

    // clear
    buf.clear();
}


QList<QString> QSerialMessageQueue::searchPorts()
{
    const auto infos = QSerialPortInfo::availablePorts();
    QList<QString> portNames;

    for(const QSerialPortInfo &info : infos) {
        portNames.append(info.portName());
    }
    return portNames;
};
