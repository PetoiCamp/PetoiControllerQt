#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "UiSerialHandler.h"
#include "UiCalibrationCheck.h"
#include "UiMotionControl.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow*     ui;

public:
    static UiSerialHandler      uiSerialHandler;    // handler for serial connection and message send/recv
    static UiCalibrationCheck   uiCalibration;
    static UiMotionControl      uiMotionControl;

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

public slots:

    /// serial connection ///
    void onSerialConnection();
    void onSerialRefresh();

    /// calibration ///
    void onCalibStart();
    void onIncreaseCalib();
    void onDecreaseCalib();
    void onClearCalib();
    void onSaveCalib();

    /// terminal ///
    void onTerminalCmd();

    /// motions and postures ///
    void onPosButtomUp();
    void onPosCheckAround();
    void onPosStretch();
    void onPosGreeting();
    void onPosPee();
    void onPosPushup();
    void onPosRest();
    void onPosSleep();
    void onPosBackFlip();
    void onPosSitdown();
    void onPosBunnyJump();
    void onPosStepping();

private:

    /**
     * @brief setupWidgets
     */
    void setupWidgets();

    /**
     * @brief bindQtSlots
     */
    void bindQtSlots();

    /**
     * @brief unbindQtSlots
     */
    void unbindQtSlots();

    /**
     * @brief keyPressEvent
     * @param event
     */
    void keyPressEvent(QKeyEvent *event);

    /**
     * @brief keyReleaseEvent
     * @param event
     */
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
