#ifndef UIMOTIONCONTROL_H
#define UIMOTIONCONTROL_H

/// Qt libraries ///
#include <QObject>
#include <QPair>
#include <QTimer>
#include <QKeyEvent>


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


#define REPEAT_MILLISECONDS     100

enum DefinedMotions {
    PosButtomUp,
    PosCheckAround,
    PosStretch,
    PosGreeting,
    PosPee,
    PosPushup,
    PosRest,
    PosSleep,
    PosBackFlip,
    PosSitdown,
    PosBunnyJump,
    PosStepping
};


class UiMotionControl : public QObject
{
    Q_OBJECT

private:
    bool            crawlActivated;     // crawl command activated
    bool            runActivated;       // run command activated
    bool            moveFront;          // if W pressed
    bool            moveLeft;           // if A pressed
    bool            moveRight;          // if D pressed
    bool            moveBack;           // if S pressed

    int             motionStatus;       // motion status
    QTimer          timer;

public:

    explicit UiMotionControl(QObject *parent = nullptr);

    ~UiMotionControl();

    /**
     * @brief doDefaultMotion
     * @param motion
     */
    void doDefaultMotion(DefinedMotions motion);

    /**
     * @brief keyPressEvent
     * @param keyPressed
     */
    void procQtKeyPressedEvent(QKeyEvent* key);

    /**
     * @brief procQtKeyReleasedEvent
     * @param key
     */
    void procQtKeyReleasedEvent(QKeyEvent* key);

private:

    /**
     * @brief updateMotionStatus
     * @return
     */
    int updateMotionStatus();

protected slots:

    /**
     * @brief usbDevicesEventCheck
     */
    void usbDevicesEventCheck();
};

#endif // UIMOTIONCONTROL_H
