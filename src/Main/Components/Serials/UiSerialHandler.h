#ifndef UISERIALHANDLER_H
#define UISERIALHANDLER_H

#include "src/Serial/QSerialMessageQueue.h"

/// Qt UI ///
#include <QComboBox>
#include <QTextBrowser>

/// Qt objects ///
#include <QList>
#include <QPair>
#include <QTimer>

#include <QSerialPort>
#include <QSerialPortInfo>


class UiSerialHandler: public QObject
{
    Q_OBJECT

private:
    QTimer                                          timer;
    QSerialMessageQueue                             queue;
    QTextBrowser*                                   textview_ptr;

    QList<QPair<QString, qint32>>                   serialBaudRatesList;
    QList<QPair<QString, QSerialPort::DataBits>>    serialDataBitsList;
    QList<QPair<QString, QSerialPort::Parity>>      serialParitiesList;
    QList<QPair<QString, QSerialPort::StopBits>>    serialStopBitsList;

    bool isCalibrated;


public:
    explicit UiSerialHandler(QObject* parent=nullptr);

    ~UiSerialHandler();

    /**
     * @brief setupSerialParametersSelections
     * @param ports
     * @param baud
     * @param parity
     * @param dataBits
     * @param stopBits
     */
    void setupSerialParametersSelections(
            QComboBox* ports,
            QComboBox* baud,
            QComboBox* parity,
            QComboBox* dataBits,
            QComboBox* stopBits);

    /**
     * @brief clearSerialParametersSelections
     * @param ports
     * @param baud
     * @param parity
     * @param dataBits
     * @param stopBits
     */
    void clearSerialParametersSelections(
            QComboBox *ports,
            QComboBox *baud,
            QComboBox *parity,
            QComboBox *dataBits,
            QComboBox *stopBits);

    /**
     * @brief connectSerial
     * @param port
     * @param baud
     * @param databits
     * @param stopbits
     * @param parity
     */
    bool connectSerial(QString port, int baud, int databits, int stopbits, int parity);

    /**
     * @brief disconnectSerial
     */
    void disconnectSerial();

    /**
     * @brief setFeedbackTextview
     * @param browser
     */
    void bindFeedbackTextview(QTextBrowser* browser);

    /**
     * @brief unbindFeedbackTextview
     */
    void unbindFeedbackTextview();

    /**
     * @brief sendCmdViaSerialPort
     * @param cmd
     */
    void sendCmdViaSerialPort(QString cmd);


protected slots:

    void onUpdateTextview();

private:

    /**
     * @brief initPorts
     * @param portList
     */
    void initPorts(QStringList& portList);

    /**
     * @brief initBaudRates
     * @param baudList
     */
    void initBaudRates(QStringList& baudList);

    /**
     * @brief initStopBits
     * @param stopBits
     */
    void initStopBits(QStringList& stopBits);

    /**
     * @brief initParities
     * @param paritis
     */
    void initParities(QStringList& paritis);

    /**
     * @brief initDataBits
     * @param dataBits
     */
    void initDataBits(QStringList& dataBits);
};

#endif // UISERIALHANDLER_H
