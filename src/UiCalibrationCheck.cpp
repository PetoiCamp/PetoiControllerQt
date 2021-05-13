#include "UiCalibrationCheck.h"
#include "MainWindow.h"

#include "src/Basics/QtBasics.h"

#include <QDebug>
#include <QStringList>

#include "CalibFeedbackProcedure.h"


UiCalibrationCheck::UiCalibrationCheck(QObject *parent) :
    QObject(parent),
    servos()
{
    // head
    servos.append(QPair<QString, int>(tr("0"), 0));

    // upper arm and leg
    servos.append(QPair<QString, int>(tr("8"), 0));
    servos.append(QPair<QString, int>(tr("9"), 0));
    servos.append(QPair<QString, int>(tr("10"), 0));
    servos.append(QPair<QString, int>(tr("11"), 0));

    // lower arm and leg
    servos.append(QPair<QString, int>(tr("12"), 0));
    servos.append(QPair<QString, int>(tr("13"), 0));
    servos.append(QPair<QString, int>(tr("14"), 0));
    servos.append(QPair<QString, int>(tr("15"), 0));
}


bool UiCalibrationCheck::increaseCalibAngle(int pos) {
    int current_angle = servos[pos].second;
    QString name = servos[pos].first;

    // increase one degree
    if ((current_angle += 1) > 9) {
        return false;
    }

    // send updated-angle
    QString updated = QString("c%1 %2").arg(name).arg(current_angle);
    MainWindow::uiSerialHandler.sendCmdViaSerialPort(updated);

    // update record
    servos[pos].second = current_angle;
    return true;
}


bool UiCalibrationCheck::decreaseCalibAngle(int pos) {
    int current_angle = servos[pos].second;
    QString name = servos[pos].first;

    // increase one degree
    if ((current_angle -= 1) < -9) {
        return false;
    }

    // send updated-angle
    QString updated = QString("c%1 %2").arg(name).arg(current_angle);
    MainWindow::uiSerialHandler.sendCmdViaSerialPort(updated);

    // update record
    servos[pos].second = current_angle;
    return true;
}


void UiCalibrationCheck::clearCalibAngle(int pos) {
    QString name = servos[pos].first;

    // send updated-angle
    QString updated = QString("c%1 %2").arg(name).arg(0);
    MainWindow::uiSerialHandler.sendCmdViaSerialPort(updated);

    // update record
    servos[pos].second = 0;
}


void UiCalibrationCheck::updateCalibrationInfo(QString feedback) {
    feedback = petoi::preprocessCalibString(feedback);
    feedback = petoi::distillValidCalibString(feedback);

    if (feedback != "") { // found valid data

        // split the string into lists
        auto servos_list = feedback.split(",");
        servos[0].second = servos_list[0].toInt();

        servos[1].second = servos_list[8].toInt();
        servos[2].second = servos_list[9].toInt();
        servos[3].second = servos_list[10].toInt();
        servos[4].second = servos_list[11].toInt();

        servos[5].second = servos_list[12].toInt();
        servos[6].second = servos_list[13].toInt();
        servos[7].second = servos_list[14].toInt();
        servos[8].second = servos_list[15].toInt();
    }
}


void UiCalibrationCheck::setupServosSelections(QComboBox *combox) {

    QStringList servosList;

    QList<QPair<QString, int>>::Iterator it = servos.begin();
    while(it != servos.end()) {

        QString servo = QString("servo %1").arg(it->first);
        servosList << servo;
        it++;
    }

    combox->addItems(servosList);
}


void UiCalibrationCheck::setupIllustration(QGraphicsView *view) {
    view->setScene(QtBasics::loadImageFromRes(
                       ":/app/pic/res/illustration.png",
                        view->width(),
                        view->height(),
                        Qt::AspectRatioMode::KeepAspectRatio));
}
