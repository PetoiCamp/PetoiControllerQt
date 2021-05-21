#include "GlobalConfig.h"
#include "src/Basics/QtBasics.h"

#include <QDir>
#include <QDebug>
#include <QStandardPaths>


void petoi::loadJson(JsonHandler& handler, QString file_macro) {
    QString preference =
            QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)
            + "/petoi/" + file_macro;

    if (QtBasics::isFile(preference)) { // file exists

        // load json string from file
        std::string json = QtBasics::loadFile(preference).toStdString();
        handler.from_json(json);

    } else { // file not exists

        // create an empty file
        QtBasics::touch(preference);

        // with default configuration
        handler.from_json("{}");
    }
};


void petoi::saveJson(JsonHandler& handler, QString file_macro) {
    QString preference =
            QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)
            + "/petoi/" + file_macro;

    if (!QtBasics::isFile(preference)) {

        // create an empty file
        QtBasics::touch(preference);
    } else {

        // remove and touch a new
        QtBasics::remove(preference);

        // create an empty file
        QtBasics::touch(preference);
    }

    // convert to qt string data type
    QString string(handler.to_str().c_str());

    // save to file
    QtBasics::saveFile(preference, string);
};
