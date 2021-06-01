#ifndef CALIBFEEDBACKPROCEDURE_H
#define CALIBFEEDBACKPROCEDURE_H

#include <QString>

namespace petoi {

    /**
     * @brief distillValidCalibString
     * @param calibString
     * @return
     */
    extern QString distillValidCalibString(QString calibString);


    /**
     * @brief preprocessCalibString
     * @param calibString
     * @return
     */
    extern QString preprocessCalibString(QString calibString);


    /**
     * @brief isValidAngle
     * @param angle
     * @return
     */
    extern bool isValidAngleDegree(QString angle);
}

#endif // CALIBFEEDBACKPROCEDURE_H
