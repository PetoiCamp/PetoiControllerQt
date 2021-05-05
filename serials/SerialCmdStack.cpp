#include "serials/SerialCmdStack.h"
#include "ui/logger.h"

#include <unistd.h>

SerialStackHandler::SerialStackHandler(SerialHelper* helper)
{
    this->helper = helper;

    // motors calibration
    for (int i = 0; i < MOTORS; i++) motors[i] = 0;
}

void SerialStackHandler::sendCmdViaSerial(QString cmd)
{
    QPair<QString, QString> token(cmd, "");

    // always keeps the size to 15;
    if (stack.length() > 15) {
        stack.pop_front();
    }

    pushToken(token);
    helper->send(cmd);

    LOG_DEBUG() << "sent:" << "\t" << cmd;
};


bool SerialStackHandler::isEmpty()
{
    return stack.isEmpty();
};


void SerialStackHandler::debugStack()
{
    qInfo() << "stack info----" << stack.length();
    for (auto& token: stack) {
        qInfo() << ">>>" << token.first << "<<<<>>>" << token.second << "<<<";
    }
}


void SerialStackHandler::pushToken(QPair<QString, QString> item)
{
    if (item.second.contains("\t")) {
        QString replaced = item.second.replace("\t", ",");
        item.second = replaced;
    }

    if (item.second.contains(",,")) {
        QString replaced = item.second.replace(",,", ",");
        item.second = replaced;
    }

    stack.push_back(item);
};


QPair<QString, QString> SerialStackHandler::popupToken()
{
    if (stack.size() > 0) {
        QPair<QString, QString> token = stack.last();
        stack.pop_back();
        return token;
    }

    // default
    return QPair<QString, QString>("", "");
};


void SerialStackHandler::calibrationFeedbackCheck()
{
    qDebug() << "===================================";

    debugStack();

    qDebug() << "===================================";

    while(true) {
        auto token = popupToken();

        if (token.first == "") break;

        if (token.first.contains("c") && token.second.length() > 10) { // found c

            // debug message
            qDebug() << "calibrationFeedbackCheck: " << token.first << "\t---->" << token.second;

            auto splits = token.second.split("\r\n");
            auto deg = splits[2].split(",");

            // convert string to integers
            for (int i = 0; i < MOTORS; i ++) {
                motors[i] = deg[i].toInt();
            }

            break;
        }
    }

    qDebug() << "===================================";

    for (int i = 0; i < MOTORS; i ++) {
        qDebug() << "steering " << i << ": " << motors[i];
    }

};
