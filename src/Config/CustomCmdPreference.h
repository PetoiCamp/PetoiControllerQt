#ifndef CUSTOMCMDPREFERENCE_H
#define CUSTOMCMDPREFERENCE_H

#include "JsonHandler.h"
#include "src/Basics/QtBasics.h"

#include <QTableView>


class CustomCmdPreference
{
public:
    static void getPreferences(QTableView* view);

    static void setPreferences(QTableView* view);

private:
    static JsonHandler handler;
};

#endif // CUSTOMCMDPREFERENCE_H
