#include "JsonParementer.h"
#include "src/Config/GlobalConfig.h"

#include <string>
#include <vector>


QList<QPair<QString, QString>>
convertObject(
        std::vector<std::string> objects) {

    // output target
    QList<QPair<QString, QString>> output;

    // parse each sub-token
    for (auto iter = objects.begin();
         iter != objects.end(); iter++) {

        // parse the object in string type
        JsonHandler handler;
        handler.from_json(*iter);

        QString key = handler.get_string("name");
        QString val = handler.get_string("cmd");

        // encapsulate/assemble
        QPair<QString, QString> pair(key, val);

        // push back to the output list
        output.push_back(pair);
    }

    return output;
}



QList<QPair<QString, QString>>
JsonParementer::loadCommands() {
    JsonHandler handler;

    // load configruation
    petoi::loadJson(handler, FRAMES_FILE);

    // convert data type
    auto objects = handler.get_multi_json_lists("actions");

    // return to caller
    return convertObject(objects);
}


std::vector<std::string>
convertObject(
        QList<QPair<QString, QString>> updated) {
    // output target
    std::vector<std::string> output;

    // iterate each token and convert it to the json type
    for (auto iter = updated.begin();
         iter != updated.end(); iter++) {
        JsonHandler handler;

        handler.set_string("name", iter->first.toStdString());
        handler.set_string("cmd", iter->second.toStdString());

        // convert to string and push back to the output list
        output.push_back(handler.to_str());
    }

    // back to caller
    return output;
}


void JsonParementer::saveCommands(
        QList<QPair<QString, QString>> updated) {

    JsonHandler handler;

    // set handler
    auto objects = convertObject(updated);
    handler.set_multi_json_lists("actions", objects);

    // save
    petoi::saveJson(handler, FRAMES_FILE);
};
