#ifndef GLOBALCONFIG_H
#define GLOBALCONFIG_H

#define PREFER_FILE "preference.json"
#define FRAMES_FILE "actions.json"

#include "JsonHandler.h"
#include <QString>

namespace petoi {

    extern void loadJson(JsonHandler& handler, QString file_macro);

    extern void saveJson(JsonHandler& handler, QString file_macro);
};


#endif // GLOBALCONFIG_H
