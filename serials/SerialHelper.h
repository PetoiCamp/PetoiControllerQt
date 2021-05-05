#ifndef SERIALHELPER_H
#define SERIALHELPER_H

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <QList>

class SerialHelper
{
private:
    QSerialPort serial;

public:
    SerialHelper();

public:
    void connect(QString portName, qint32 baudRate, QSerialPort::DataBits dataBits,
                 QSerialPort::StopBits stopBits, QSerialPort::Parity parity);

    void disconnect();

    bool connected();

    bool available();

    QSerialPort* getInstance();

    void send(QString msg);

    QString recv();

    QString errormsg();

    QList<QString> searchPorts();
};

#endif // SERIALHELPER_H
