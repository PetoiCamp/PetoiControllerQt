#ifndef JSONPAREMENTER_H
#define JSONPAREMENTER_H

#include "src/Json/JsonHandler.h"

#include <QList>
#include <QString>
#include <QPair>


class JsonParementer
{
public:

    /**
     * @brief loadCommands
     * @return
     */
    static QList<QPair<QString, QString>> loadCommands();

    /**
     * @brief saveCommands
     * @param updated
     */
    static void saveCommands(QList<QPair<QString, QString>> updated);

};

#endif // JSONPAREMENTER_H
