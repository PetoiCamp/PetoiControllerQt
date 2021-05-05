#include "serials/SerialHelper.h"

SerialHelper::SerialHelper() : serial()
{

}


void SerialHelper::connect(QString portName, qint32 baudRate, QSerialPort::DataBits dataBits,
             QSerialPort::StopBits stopBits, QSerialPort::Parity parity)
{
    serial.setPortName(portName);
    serial.setBaudRate(baudRate);
    serial.setStopBits(stopBits);
    serial.setDataBits(dataBits);
    serial.setParity(parity);

    // connect to remote device via serial port
    serial.open(QIODevice::ReadWrite);
};

void SerialHelper::disconnect()
{
    serial.clear();
    serial.close();
};

bool SerialHelper::connected()
{
    return serial.isOpen();
};

bool SerialHelper::available()
{
    return serial.isOpen() & serial.isWritable() & serial.isReadable();
};

QSerialPort* SerialHelper::getInstance()
{
    return &serial;
};

void SerialHelper::send(QString msg)
{
    serial.write(msg.toLocal8Bit());
};

QString SerialHelper::recv()
{
    auto buf = serial.readAll();
    if (!buf.isEmpty()) {
        QString msg = QString::fromLocal8Bit(buf); //支持中文显示
        buf.clear();
        return msg;
    }

    buf.clear();
    return "read data failed";
};

QString SerialHelper::errormsg()
{
    return serial.errorString();
}

QList<QString> SerialHelper::searchPorts()
{
    const auto infos = QSerialPortInfo::availablePorts();
    QList<QString> portNames;

    for(const QSerialPortInfo &info : infos) {
        portNames.append(info.portName());
    }
    return portNames;
};
