#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/// qt window
#include <QMainWindow>

/// qt widgets
#include <QLabel>
#include <QTimer>
#include <QString>
#include <QDebug>

/// qt data structures
#include <QList>
#include <QPair>

#include "logger.h"
#include "serials/SerialHelper.h"
#include "serials/SerialCmdStack.h"

#include "frame/PetoiActionFrame.h"


using namespace std;


#define STATUS_READY            0x00
#define STATUS_STANDBY          0x01

#define STATUS_NORMAL_FORWARD   0x11
#define STATUS_NORMAL_BACKWARD  0x12
#define STATUS_NORMAL_LEFT      0x13
#define STATUS_NORMAL_RIGHT     0x14

#define STATUS_CRAWL_FORWARD    0x21
#define STATUS_CRAWL_BACKWARD   0x22
#define STATUS_CRAWL_LEFT       0x23
#define STATUS_CRAWL_RIGHT      0x24

#define STATUS_RUN_FORWARD      0x31
#define STATUS_RUN_BACKWARD     0x32
#define STATUS_RUN_LEFT         0x33
#define STATUS_RUN_RIGHT        0x34

#define LANGUAGE_CHINESE        0x00
#define LANGUAGE_ENGLISH        0x01


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

protected slots:
    // connect remote via serial
    void onConnectRemoteButtonPressed();

    // refresh remote ports list
    void onRefreshDevicesButtonPressed();

    // send cmd/msg via serial
    void onSendButtonPressed();

    // read cmd/msg via serial
    void onRecvMsgViaSerial();

    // send cmd/msg via serial when user pressed enter button
    void onEnterButtonPressed();

    // send calibration command via serial
    void onCalibrationButtonPressed();

    // send c0 command via serial
    void onClearupButtonPressed();

    // send save steering angle positions via serial
    void onSaveAnglesButtonPressed();

    // fine tunne
    void onIncreaseFineTunne();
    void onDecreaseFineTunne();

    // steering engine selector changed event
    void onSteeringChanged(int value);

private:
    // initialize serial port communication
    void initPort();

    // initialize qt widgets
    void initWidgets();

    // init main window menu
    void initMenu();

    // init buttons
    void initButtons();

    // translate ui for localization
    void translateUi(const char *package);

    // bind qt signal/slot
    void bindQtSlots();

    // baud rates
    void initBaudRates(QStringList& baudList);

    // stopbits
    void initStopBits(QStringList& stopBits);

    // parities
    void initParities(QStringList& paritis);

    // databits
    void initDataBits(QStringList& dataBits);

    // inititlize steering engines
    void initSteerings(QStringList& baudList);

    // override key pressed
    void keyPressEvent(QKeyEvent *event);

    // override key release
    void keyReleaseEvent(QKeyEvent *event);

private:
    /**
     * actions 
     */
    QMenu *fileMenu;
    QMenu *fileLinguistMenu;

    QAction *chineseTypeAct;
    QAction *englishTypeAct;
    QAction *exitAct;


protected slots:
    /**
     * menus 
     */
    void exitApp();
    void showAsChn();
    void showAsEng();

    /**
     * motions and postures 
     */
    void posButtomUp();
    void posCheckAround();
    void posStretch();
    void posGreeting();
    void posPee();
    void posPushup();
    void posRest();
    void posSleep();
    void posBackFlip();
    void posSitdown();
    void posBunnyJump();
    void posStepping();

    /**
     * global controlling panel 
     */
    void panelBalance();
    void panelPause();
    void panelRecovery();
    void panelGyro();
    void panelServos();

    /**
      * keyboard event interval checker
      */
    void intervalEventChecker();

    /**
     * @brief updateMultiServos, send updated servos angles
     */
    void updateCalibratedServors();
    void updatedActionFrame(char* frames);

    /**
    * send defined action frames
    */
    void sendActionFrame01();
    void sendActionFrame02();
    void sendActionFrame03();
    void sendActionFrame04();
    void sendActionFrame05();
    void sendActionFrame06();
    void sendActionFrame07();
    void sendActionFrame08();
    void sendActionFrame09();
    void sendActionFrame10();

private:
    Ui::MainWindow      *ui;
    SerialHelper        *helper;
    SerialStackHandler  *stack;


//    qint32          angle;
    QString         feedback;
//    int             motors[MOTORS];

    bool            ctrlActivated;  // crawl command activated
    bool            shiftActivated; // run command activated
    bool            moveFront;
    bool            moveLeft;
    bool            moveRight;
    bool            moveBack;

    int             runningStatus;  // running status
    int             updateStatus(); // update running status
    QTimer          *eventTimer;
    int             dynamicLanguage;

    PetoiActionFrame    *action;

protected:
    QList<QPair<QString, qint32>> serialBaudRatesList;
    QList<QPair<QString, QSerialPort::DataBits>> serialDataBitsList;
    QList<QPair<QString, QSerialPort::Parity>> serialParitiesList;
    QList<QPair<QString, QSerialPort::StopBits>> serialStopBitsList;

    QList<QPair<QString, QString>> steeringMotorList;
};
#endif // MainWindow_H

