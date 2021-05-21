#ifndef QSERIALMESSAGEQUEUE_H
#define QSERIALMESSAGEQUEUE_H

/// serial connector ///
#include <QSerialPort>
#include <QSerialPortInfo>

/// Qt libraries ///
#include <QList>
#include <QString>
#include <QObject>
#include <QQueue>

/// raw and data packet ///
#include "RawMessage.h"

/// C/CPP libraries ///
#include <memory>



class QSerialMessageQueue: public QObject
{
    Q_OBJECT

private:
    QSerialPort serial;
    QQueue<std::shared_ptr<RawMessage>> queue;

public:

    /**
     * @brief QSerialMessageQueue
     */
    explicit QSerialMessageQueue(QObject *parent = nullptr);

    /**
     * @brief connect
     * @param portName
     * @param baudRate
     * @param dataBits
     * @param stopBits
     * @param parity
     */
    bool connect(QString portName,
                 qint32 baudRate,
                 QSerialPort::DataBits dataBits,
                 QSerialPort::StopBits stopBits,
                 QSerialPort::Parity parity);

    /**
     * @brief disconnect
     */
    void disconnect();

    /**
     * @brief searchPorts
     * @return
     */
    QList<QString> searchPorts();


    /**
     * @brief sendViaSerial
     * @param bytes
     * @param sentSize
     * @return
     */
    int sendViaSerial(unsigned char* bytes, int sentSize);


    /**
     * @brief recvViaSerial
     * @param bytes
     * @param maxSize
     * @return
     */
    int recvViaSerial(unsigned char* bytes, int maxSize);


    /**
     * @brief clearBuffer
     */
    void clearBuffer();

public slots:

    /**
     * @brief onSerialAutoRecv
     */
    void onSerialAutoRecv();
};

#endif // QSERIALMESSAGEQUEUE_H
