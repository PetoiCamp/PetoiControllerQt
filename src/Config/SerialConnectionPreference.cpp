#include "SerialConnectionPreference.h"
#include "GlobalConfig.h"
#include "JsonHandler.h"
#include "src/Basics/QtBasics.h"

#include <QString>
#include <QDebug>
#include <QDir>
#include <QStandardPaths>


JsonHandler SerialConnectionPreference::handler;


void preProcessHandler(JsonHandler& handler) {
    QString preference = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)
            + "/petoi/" + PREFER_FILE;

    if (QtBasics::isFile(preference)) { // file exists

        // load json string from file
        std::string json = QtBasics::loadFile(preference).toStdString();
//        qDebug() << QtBasics::loadFile(preference);
        handler.from_json(json);

    } else { // file not exists

        // create an empty file
        QtBasics::touch(preference);

        // with default configuration
        handler.from_json("{ \"port_name\": 0, \"baud_rate\": 7, \"parity\": 0, \"data_bits\": 3, \"stop_bits\": 0 }");
    }
}


void saveUpdatedJson(QString jsonStr) {
    QString preference = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)
            + "/petoi/" + PREFER_FILE;

    if (QtBasics::isFile(preference)) {
        QtBasics::saveFile(preference, jsonStr);
    }
}


void SerialConnectionPreference::getPreferences(
        QComboBox *ports,
        QComboBox *baud,
        QComboBox *parity,
        QComboBox *dataBits,
        QComboBox *stopBits) {

    // pre process json handler
    preProcessHandler(handler);

    // get values from json file
    int default_port, default_baud, default_parity, default_databits, default_stopbits;
    default_port = handler.has_item("port_name") ? handler.get_int("port_name") : 0;
    default_baud = handler.has_item("baud_rate") ? handler.get_int("baud_rate") : 0;
    default_parity = handler.has_item("parity") ? handler.get_int("parity") : 0;
    default_databits = handler.has_item("data_bits") ? handler.get_int("data_bits") : 0;
    default_stopbits = handler.has_item("stop_bits") ? handler.get_int("stop_bits") : 0;

    // update preferences
    ports->setCurrentIndex(default_port);
    baud->setCurrentIndex(default_baud);
    parity->setCurrentIndex(default_parity);
    dataBits->setCurrentIndex(default_databits);
    stopBits->setCurrentIndex(default_stopbits);
};


void SerialConnectionPreference::setPreferences(
        QComboBox *ports,
        QComboBox *baud,
        QComboBox *parity,
        QComboBox *dataBits,
        QComboBox *stopBits) {

    // pre process json handler
    preProcessHandler(handler);

    // save all parameters back to file
    int default_port, default_baud, default_parity, default_databits, default_stopbits;
    default_port = ports->currentIndex();
    default_baud = baud->currentIndex();
    default_parity = parity->currentIndex();
    default_databits = dataBits->currentIndex();
    default_stopbits = stopBits->currentIndex();

    // set or update values
    handler.set_int("port_name", default_port);
    handler.set_int("baud_rate", default_baud);
    handler.set_int("parity", default_parity);
    handler.set_int("data_bits", default_databits);
    handler.set_int("stop_bits", default_stopbits);

    // write back to file
    saveUpdatedJson(handler.to_str(true).c_str());
};
