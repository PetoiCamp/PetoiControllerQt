#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/// Qt libraries ///
#include <QMainWindow>
#include <QTranslator>

#include "UiCustomActions.h"
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
    QTranslator         translator;
    QMenu               *fileMenu;
    QMenu               *fileLinguistMenu;

    QAction             *chineseTypeAct;
    QAction             *englishTypeAct;
    QAction             *exitAct;

    bool                isSerialOn;
    bool                isCalibrationOn;
    bool                isActionsOn;

public:
    static UiSerialHandler      uiSerialHandler;
    static UiCalibrationCheck   uiCalibration;
    static UiMotionControl      uiMotionControl;
    static UiCustomActions      uiCustomActions;

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
    void onTerminalEnterPressed();

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

    /// language selection ///
    void onLanguageSelected();

protected slots:

    /**
     * @brief onFileExit
     */
    void onFileExit();

    /**
     * @brief onFileShowAsChn
     */
    void onShowAsChn();

    /**
     * @brief onFileShowAsEng
     */
    void onShowAsEng();

private:

    /**
     * @brief serialSwitch
     */
    void switchSerial();

    /**
     * @brief actionsSwitch
     */
    void switchCalibration();

    /**
     * @brief terminalSwitch
     */
    void switchActions();

    /**
     * @brief setupLanguages
     */
    void setupLanguages();

    /**
     *  @brief setupMenus
     */
    void setupMenus();

    /**
     * @brief translateUi
     * @param package
     */
    void translateUi(QString package);

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
