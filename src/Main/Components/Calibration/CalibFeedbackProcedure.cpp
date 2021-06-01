#include "CalibFeedbackProcedure.h"

#include <QRegularExpression>


QString distillOnceMore(QString calibString) {
    QString pattern("(([-\\+]?\\d),\\s)+");
    QRegularExpression reg(pattern);

    QRegularExpressionMatch match = reg.match(calibString);

    if (match.hasMatch()) {
        int startOffset = match.capturedStart();
        int endOffset = match.capturedEnd();

        QString purity_str = calibString.mid(startOffset, endOffset);
        return purity_str.replace(" ", "").replace(", ", ",");
    }

    return "";
}


QString petoi::distillValidCalibString(QString calibString) {
    QString pattern("(0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15)\\s+(([-\\+]?\\d),\\s)+");
    QRegularExpression reg(pattern);

    QRegularExpressionMatch match = reg.match(calibString);

    if (match.hasMatch()) {
        int startOffset = match.capturedStart();
        int endOffset = match.capturedEnd();

        QString impurity_str = calibString.mid(startOffset, endOffset);
        if (impurity_str != "") return distillOnceMore(impurity_str);
    }

    return "";
};


QString petoi::preprocessCalibString(QString calibString) {
    QString newCalibString = calibString.replace("\r", " ")
            .replace("\n", " ")
            .replace("\t", " ");

    return newCalibString;
};



bool petoi::isValidAngleDegree(QString angle) {
    QString pattern("^([-|+]?\\d+)$");
    QRegularExpression reg(pattern);

    QRegularExpressionMatch match = reg.match(angle);
    return match.hasMatch();
}
