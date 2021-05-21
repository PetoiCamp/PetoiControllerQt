#ifndef SERIALCONNECTIONPREFERENCE_H
#define SERIALCONNECTIONPREFERENCE_H

#include <QComboBox>

#include "JsonHandler.h"


class SerialConnectionPreference
{
public:
    static void getPreference(
        QComboBox *ports, QComboBox *baud,
        QComboBox *parity, QComboBox *dataBits,
        QComboBox *stopBits
    );

    static void setPreference(
        QComboBox *ports, QComboBox *baud,
        QComboBox *parity, QComboBox *dataBits,
        QComboBox *stopBits
    );
};

#endif // SERIALCONNECTIONPREFERENCE_H
