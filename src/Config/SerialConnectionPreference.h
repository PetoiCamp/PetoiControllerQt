#ifndef SERIALCONNECTIONPREFERENCE_H
#define SERIALCONNECTIONPREFERENCE_H

#include <QComboBox>

#include "JsonHandler.h"


class SerialConnectionPreference
{
public:
    static void getPreferences(
        QComboBox *ports, QComboBox *baud,
        QComboBox *parity, QComboBox *dataBits,
        QComboBox *stopBits
    );

    static void setPreferences(
        QComboBox *ports, QComboBox *baud,
        QComboBox *parity, QComboBox *dataBits,
        QComboBox *stopBits
    );


private:
    static JsonHandler handler;
};

#endif // SERIALCONNECTIONPREFERENCE_H
