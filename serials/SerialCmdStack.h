#ifndef SERIALCMDSTACK_H
#define SERIALCMDSTACK_H

/// custom defined headers
#include "serials/SerialHelper.h"

/// QT datastructure
#include <QString>
#include <QStack>
#include <QPair>

#define MOTORS 16

class SerialStackHandler
{
private:
    SerialHelper *helper;
    QStack<QPair<QString, QString>> stack;

public:
    SerialStackHandler(SerialHelper* helper);



public: // calibration relatives

    int motors[MOTORS];

    void calibrationFeedbackCheck();


public:  // normal
    void sendCmdViaSerial(QString cmd);

    bool isEmpty();

    void pushToken(QPair<QString, QString>);

    QPair<QString, QString> popupToken();

public:
    void debugStack();
};

#endif // SERIALCMDSTACK_H
