#ifndef UICALIBRATIONCHECK_H
#define UICALIBRATIONCHECK_H

/// Qt libraries ///
#include <QObject>
#include <QList>
#include <QString>
#include <QPair>

/// Qt UI ///
#include <QComboBox>
#include <QGraphicsView>


class UiCalibrationCheck : public QObject
{
    Q_OBJECT

private:
    QList<QPair<QString, int>>  servos;

public:
    explicit UiCalibrationCheck(QObject *parent = nullptr);

    /**
     * @brief count
     * @return
     */
    inline int count() { return servos.count(); }

    /**
     * @brief operator []
     * @param pos
     * @return
     */
    inline int operator[] (int pos) { return servos[pos].second; }

    /**
     * @brief name
     * @param pos
     * @return
     */
    inline QString name(int pos) { return servos[pos].first; }

    /**
     * @brief angle
     * @param pos
     * @return
     */
    inline int angle(int pos) { return servos[pos].second; }

    /**
     * @brief increaseCalibAngle
     * @param pos
     */
    bool increaseCalibAngle(int pos);

    /**
     * @brief decreaseCalibAngle
     * @param pos
     */
    bool decreaseCalibAngle(int pos);

    /**
     * @brief updateCalibrationInfo
     * @param feedback
     * @return
     */
    bool updateCalibrationInfo(QString feedback);

    /**
     * @brief angleToZero
     * @param pos
     */
    void clearCalibAngle(int pos);

    /**
     * @brief setServos
     * @param servos
     */
    void setupServosSelections(QComboBox *servos);

    /**
     * @brief setupIllustration
     */
    void setupIllustration(QGraphicsView* view);
};

#endif // UICALIBRATIONCHECK_H
