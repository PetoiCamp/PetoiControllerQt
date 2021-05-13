/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tabSerial;
    QGraphicsView *viewBittleIllustration;
    QGroupBox *groupBoxSerialPort;
    QSplitter *serialSetupSplitter;
    QWidget *layoutWidget_1;
    QHBoxLayout *horizontalLayout_1;
    QLabel *labelSerialPort;
    QComboBox *boxPortNumber;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelBaudRate;
    QComboBox *boxBaudRate;
    QWidget *layoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelStopBits;
    QComboBox *boxStopBits;
    QWidget *layoutWidget_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labelDataBits;
    QComboBox *boxDataBits;
    QWidget *layoutWidget_5;
    QHBoxLayout *horizontalLayout_5;
    QLabel *labelParity;
    QComboBox *boxParity;
    QPushButton *buttonConnect;
    QPushButton *buttonRefresh;
    QGroupBox *groupBoxServosAdjust;
    QSplitter *splitter_2;
    QPushButton *buttonCleanCalibration;
    QPushButton *buttonSaveCalibration;
    QSplitter *splitter;
    QPushButton *buttonCalibration;
    QComboBox *boxSteering;
    QPushButton *buttonIncreaseAngle;
    QPushButton *buttonDecreaseAngle;
    QFrame *line;
    QGroupBox *groupTerminal;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QSplitter *splitter_3;
    QLineEdit *lineCmd;
    QPushButton *buttonSendCmd;
    QTextBrowser *textTerminalOutput;
    QWidget *tabPanel;
    QGroupBox *groupBoxActions;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayoutActions;
    QHBoxLayout *horizontalLayout;
    QPushButton *buttonPosStretch;
    QPushButton *buttonPosButtomUp;
    QPushButton *buttonPosCheckRd;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *buttonPosHi;
    QPushButton *buttonPosPee;
    QPushButton *buttonPosPushUp;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *buttonPosSit;
    QPushButton *buttonPosSleep;
    QPushButton *buttonPosRest;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *buttonPosStepping;
    QPushButton *buttonPosBackFlip;
    QPushButton *buttonPosBunnyJump;
    QGroupBox *groupBoxServosPanel;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *buttonCtrlRestPos;
    QPushButton *buttonCtrlBalance;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *buttonCtrlGyro;
    QPushButton *buttonCtrlServos;
    QTextBrowser *textSpecification;
    QGroupBox *groupBoxCustomActions;
    QSplitter *languageSplitter;
    QLabel *labelLanguage;
    QComboBox *boxLanguage;
    QStatusBar *statusBar;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1000, 720);
        MainWindow->setMinimumSize(QSize(1000, 720));
        MainWindow->setMaximumSize(QSize(1000, 720));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/app/pic/logo.icns"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 39, 981, 651));
        tabSerial = new QWidget();
        tabSerial->setObjectName(QString::fromUtf8("tabSerial"));
        viewBittleIllustration = new QGraphicsView(tabSerial);
        viewBittleIllustration->setObjectName(QString::fromUtf8("viewBittleIllustration"));
        viewBittleIllustration->setGeometry(QRect(579, 10, 391, 591));
        groupBoxSerialPort = new QGroupBox(tabSerial);
        groupBoxSerialPort->setObjectName(QString::fromUtf8("groupBoxSerialPort"));
        groupBoxSerialPort->setGeometry(QRect(0, 10, 561, 291));
        serialSetupSplitter = new QSplitter(groupBoxSerialPort);
        serialSetupSplitter->setObjectName(QString::fromUtf8("serialSetupSplitter"));
        serialSetupSplitter->setGeometry(QRect(10, 20, 541, 221));
        serialSetupSplitter->setOrientation(Qt::Vertical);
        layoutWidget_1 = new QWidget(serialSetupSplitter);
        layoutWidget_1->setObjectName(QString::fromUtf8("layoutWidget_1"));
        horizontalLayout_1 = new QHBoxLayout(layoutWidget_1);
        horizontalLayout_1->setSpacing(6);
        horizontalLayout_1->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_1->setObjectName(QString::fromUtf8("horizontalLayout_1"));
        horizontalLayout_1->setContentsMargins(0, 0, 0, 0);
        labelSerialPort = new QLabel(layoutWidget_1);
        labelSerialPort->setObjectName(QString::fromUtf8("labelSerialPort"));

        horizontalLayout_1->addWidget(labelSerialPort);

        boxPortNumber = new QComboBox(layoutWidget_1);
        boxPortNumber->setObjectName(QString::fromUtf8("boxPortNumber"));
        boxPortNumber->setMinimumSize(QSize(360, 0));

        horizontalLayout_1->addWidget(boxPortNumber);

        serialSetupSplitter->addWidget(layoutWidget_1);
        layoutWidget_2 = new QWidget(serialSetupSplitter);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        labelBaudRate = new QLabel(layoutWidget_2);
        labelBaudRate->setObjectName(QString::fromUtf8("labelBaudRate"));

        horizontalLayout_2->addWidget(labelBaudRate);

        boxBaudRate = new QComboBox(layoutWidget_2);
        boxBaudRate->setObjectName(QString::fromUtf8("boxBaudRate"));
        boxBaudRate->setMinimumSize(QSize(360, 0));

        horizontalLayout_2->addWidget(boxBaudRate);

        serialSetupSplitter->addWidget(layoutWidget_2);
        layoutWidget_3 = new QWidget(serialSetupSplitter);
        layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget_3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        labelStopBits = new QLabel(layoutWidget_3);
        labelStopBits->setObjectName(QString::fromUtf8("labelStopBits"));

        horizontalLayout_3->addWidget(labelStopBits);

        boxStopBits = new QComboBox(layoutWidget_3);
        boxStopBits->setObjectName(QString::fromUtf8("boxStopBits"));
        boxStopBits->setMinimumSize(QSize(360, 0));

        horizontalLayout_3->addWidget(boxStopBits);

        serialSetupSplitter->addWidget(layoutWidget_3);
        layoutWidget_4 = new QWidget(serialSetupSplitter);
        layoutWidget_4->setObjectName(QString::fromUtf8("layoutWidget_4"));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget_4);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        labelDataBits = new QLabel(layoutWidget_4);
        labelDataBits->setObjectName(QString::fromUtf8("labelDataBits"));

        horizontalLayout_4->addWidget(labelDataBits);

        boxDataBits = new QComboBox(layoutWidget_4);
        boxDataBits->setObjectName(QString::fromUtf8("boxDataBits"));
        boxDataBits->setMinimumSize(QSize(360, 0));

        horizontalLayout_4->addWidget(boxDataBits);

        serialSetupSplitter->addWidget(layoutWidget_4);
        layoutWidget_5 = new QWidget(serialSetupSplitter);
        layoutWidget_5->setObjectName(QString::fromUtf8("layoutWidget_5"));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget_5);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        labelParity = new QLabel(layoutWidget_5);
        labelParity->setObjectName(QString::fromUtf8("labelParity"));

        horizontalLayout_5->addWidget(labelParity);

        boxParity = new QComboBox(layoutWidget_5);
        boxParity->setObjectName(QString::fromUtf8("boxParity"));
        boxParity->setMinimumSize(QSize(360, 0));

        horizontalLayout_5->addWidget(boxParity);

        serialSetupSplitter->addWidget(layoutWidget_5);
        buttonConnect = new QPushButton(groupBoxSerialPort);
        buttonConnect->setObjectName(QString::fromUtf8("buttonConnect"));
        buttonConnect->setGeometry(QRect(460, 250, 100, 32));
        buttonConnect->setMinimumSize(QSize(100, 0));
        buttonConnect->setMaximumSize(QSize(100, 16777215));
        buttonRefresh = new QPushButton(groupBoxSerialPort);
        buttonRefresh->setObjectName(QString::fromUtf8("buttonRefresh"));
        buttonRefresh->setGeometry(QRect(10, 250, 100, 32));
        buttonRefresh->setMinimumSize(QSize(100, 0));
        buttonRefresh->setMaximumSize(QSize(100, 16777215));
        groupBoxServosAdjust = new QGroupBox(tabSerial);
        groupBoxServosAdjust->setObjectName(QString::fromUtf8("groupBoxServosAdjust"));
        groupBoxServosAdjust->setGeometry(QRect(0, 300, 561, 111));
        splitter_2 = new QSplitter(groupBoxServosAdjust);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setGeometry(QRect(350, 70, 207, 32));
        splitter_2->setOrientation(Qt::Horizontal);
        buttonCleanCalibration = new QPushButton(splitter_2);
        buttonCleanCalibration->setObjectName(QString::fromUtf8("buttonCleanCalibration"));
        buttonCleanCalibration->setMinimumSize(QSize(100, 0));
        buttonCleanCalibration->setMaximumSize(QSize(100, 16777215));
        splitter_2->addWidget(buttonCleanCalibration);
        buttonSaveCalibration = new QPushButton(splitter_2);
        buttonSaveCalibration->setObjectName(QString::fromUtf8("buttonSaveCalibration"));
        buttonSaveCalibration->setMinimumSize(QSize(100, 0));
        buttonSaveCalibration->setMaximumSize(QSize(100, 16777215));
        splitter_2->addWidget(buttonSaveCalibration);
        splitter = new QSplitter(groupBoxServosAdjust);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(10, 30, 541, 32));
        splitter->setOrientation(Qt::Horizontal);
        buttonCalibration = new QPushButton(splitter);
        buttonCalibration->setObjectName(QString::fromUtf8("buttonCalibration"));
        buttonCalibration->setMinimumSize(QSize(100, 0));
        buttonCalibration->setMaximumSize(QSize(100, 16777215));
        splitter->addWidget(buttonCalibration);
        boxSteering = new QComboBox(splitter);
        boxSteering->setObjectName(QString::fromUtf8("boxSteering"));
        boxSteering->setMinimumSize(QSize(270, 0));
        boxSteering->setMaximumSize(QSize(300, 16777215));
        splitter->addWidget(boxSteering);
        buttonIncreaseAngle = new QPushButton(splitter);
        buttonIncreaseAngle->setObjectName(QString::fromUtf8("buttonIncreaseAngle"));
        buttonIncreaseAngle->setMinimumSize(QSize(64, 0));
        buttonIncreaseAngle->setMaximumSize(QSize(64, 16777215));
        splitter->addWidget(buttonIncreaseAngle);
        buttonDecreaseAngle = new QPushButton(splitter);
        buttonDecreaseAngle->setObjectName(QString::fromUtf8("buttonDecreaseAngle"));
        buttonDecreaseAngle->setMinimumSize(QSize(64, 0));
        buttonDecreaseAngle->setMaximumSize(QSize(64, 16777215));
        splitter->addWidget(buttonDecreaseAngle);
        line = new QFrame(tabSerial);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(560, 10, 20, 620));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        groupTerminal = new QGroupBox(tabSerial);
        groupTerminal->setObjectName(QString::fromUtf8("groupTerminal"));
        groupTerminal->setGeometry(QRect(0, 410, 561, 201));
        layoutWidget = new QWidget(groupTerminal);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 30, 541, 161));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        splitter_3 = new QSplitter(layoutWidget);
        splitter_3->setObjectName(QString::fromUtf8("splitter_3"));
        splitter_3->setOrientation(Qt::Horizontal);
        lineCmd = new QLineEdit(splitter_3);
        lineCmd->setObjectName(QString::fromUtf8("lineCmd"));
        lineCmd->setMinimumSize(QSize(240, 0));
        splitter_3->addWidget(lineCmd);
        buttonSendCmd = new QPushButton(splitter_3);
        buttonSendCmd->setObjectName(QString::fromUtf8("buttonSendCmd"));
        buttonSendCmd->setMinimumSize(QSize(100, 0));
        buttonSendCmd->setMaximumSize(QSize(100, 16777215));
        splitter_3->addWidget(buttonSendCmd);

        verticalLayout->addWidget(splitter_3);

        textTerminalOutput = new QTextBrowser(layoutWidget);
        textTerminalOutput->setObjectName(QString::fromUtf8("textTerminalOutput"));

        verticalLayout->addWidget(textTerminalOutput);

        tabWidget->addTab(tabSerial, QString());
        tabPanel = new QWidget();
        tabPanel->setObjectName(QString::fromUtf8("tabPanel"));
        groupBoxActions = new QGroupBox(tabPanel);
        groupBoxActions->setObjectName(QString::fromUtf8("groupBoxActions"));
        groupBoxActions->setGeometry(QRect(10, 10, 631, 201));
        layoutWidget1 = new QWidget(groupBoxActions);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(11, 31, 611, 160));
        verticalLayoutActions = new QVBoxLayout(layoutWidget1);
        verticalLayoutActions->setSpacing(6);
        verticalLayoutActions->setContentsMargins(11, 11, 11, 11);
        verticalLayoutActions->setObjectName(QString::fromUtf8("verticalLayoutActions"));
        verticalLayoutActions->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        buttonPosStretch = new QPushButton(layoutWidget1);
        buttonPosStretch->setObjectName(QString::fromUtf8("buttonPosStretch"));

        horizontalLayout->addWidget(buttonPosStretch);

        buttonPosButtomUp = new QPushButton(layoutWidget1);
        buttonPosButtomUp->setObjectName(QString::fromUtf8("buttonPosButtomUp"));

        horizontalLayout->addWidget(buttonPosButtomUp);

        buttonPosCheckRd = new QPushButton(layoutWidget1);
        buttonPosCheckRd->setObjectName(QString::fromUtf8("buttonPosCheckRd"));

        horizontalLayout->addWidget(buttonPosCheckRd);


        verticalLayoutActions->addLayout(horizontalLayout);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        buttonPosHi = new QPushButton(layoutWidget1);
        buttonPosHi->setObjectName(QString::fromUtf8("buttonPosHi"));

        horizontalLayout_6->addWidget(buttonPosHi);

        buttonPosPee = new QPushButton(layoutWidget1);
        buttonPosPee->setObjectName(QString::fromUtf8("buttonPosPee"));

        horizontalLayout_6->addWidget(buttonPosPee);

        buttonPosPushUp = new QPushButton(layoutWidget1);
        buttonPosPushUp->setObjectName(QString::fromUtf8("buttonPosPushUp"));

        horizontalLayout_6->addWidget(buttonPosPushUp);


        verticalLayoutActions->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        buttonPosSit = new QPushButton(layoutWidget1);
        buttonPosSit->setObjectName(QString::fromUtf8("buttonPosSit"));

        horizontalLayout_7->addWidget(buttonPosSit);

        buttonPosSleep = new QPushButton(layoutWidget1);
        buttonPosSleep->setObjectName(QString::fromUtf8("buttonPosSleep"));

        horizontalLayout_7->addWidget(buttonPosSleep);

        buttonPosRest = new QPushButton(layoutWidget1);
        buttonPosRest->setObjectName(QString::fromUtf8("buttonPosRest"));

        horizontalLayout_7->addWidget(buttonPosRest);


        verticalLayoutActions->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        buttonPosStepping = new QPushButton(layoutWidget1);
        buttonPosStepping->setObjectName(QString::fromUtf8("buttonPosStepping"));

        horizontalLayout_8->addWidget(buttonPosStepping);

        buttonPosBackFlip = new QPushButton(layoutWidget1);
        buttonPosBackFlip->setObjectName(QString::fromUtf8("buttonPosBackFlip"));

        horizontalLayout_8->addWidget(buttonPosBackFlip);

        buttonPosBunnyJump = new QPushButton(layoutWidget1);
        buttonPosBunnyJump->setObjectName(QString::fromUtf8("buttonPosBunnyJump"));

        horizontalLayout_8->addWidget(buttonPosBunnyJump);


        verticalLayoutActions->addLayout(horizontalLayout_8);

        groupBoxServosPanel = new QGroupBox(tabPanel);
        groupBoxServosPanel->setObjectName(QString::fromUtf8("groupBoxServosPanel"));
        groupBoxServosPanel->setGeometry(QRect(650, 10, 311, 201));
        layoutWidget2 = new QWidget(groupBoxServosPanel);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 30, 291, 32));
        horizontalLayout_9 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        buttonCtrlRestPos = new QPushButton(layoutWidget2);
        buttonCtrlRestPos->setObjectName(QString::fromUtf8("buttonCtrlRestPos"));

        horizontalLayout_9->addWidget(buttonCtrlRestPos);

        buttonCtrlBalance = new QPushButton(layoutWidget2);
        buttonCtrlBalance->setObjectName(QString::fromUtf8("buttonCtrlBalance"));

        horizontalLayout_9->addWidget(buttonCtrlBalance);

        layoutWidget3 = new QWidget(groupBoxServosPanel);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(10, 70, 291, 32));
        horizontalLayout_10 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        buttonCtrlGyro = new QPushButton(layoutWidget3);
        buttonCtrlGyro->setObjectName(QString::fromUtf8("buttonCtrlGyro"));

        horizontalLayout_10->addWidget(buttonCtrlGyro);

        buttonCtrlServos = new QPushButton(layoutWidget3);
        buttonCtrlServos->setObjectName(QString::fromUtf8("buttonCtrlServos"));

        horizontalLayout_10->addWidget(buttonCtrlServos);

        textSpecification = new QTextBrowser(groupBoxServosPanel);
        textSpecification->setObjectName(QString::fromUtf8("textSpecification"));
        textSpecification->setGeometry(QRect(10, 110, 291, 81));
        groupBoxCustomActions = new QGroupBox(tabPanel);
        groupBoxCustomActions->setObjectName(QString::fromUtf8("groupBoxCustomActions"));
        groupBoxCustomActions->setGeometry(QRect(10, 210, 951, 391));
        tabWidget->addTab(tabPanel, QString());
        languageSplitter = new QSplitter(centralWidget);
        languageSplitter->setObjectName(QString::fromUtf8("languageSplitter"));
        languageSplitter->setGeometry(QRect(770, 10, 221, 32));
        languageSplitter->setOrientation(Qt::Horizontal);
        labelLanguage = new QLabel(languageSplitter);
        labelLanguage->setObjectName(QString::fromUtf8("labelLanguage"));
        languageSplitter->addWidget(labelLanguage);
        boxLanguage = new QComboBox(languageSplitter);
        boxLanguage->setObjectName(QString::fromUtf8("boxLanguage"));
        languageSplitter->addWidget(boxLanguage);
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1000, 24));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "PetoiSerialApp", nullptr));
        groupBoxSerialPort->setTitle(QCoreApplication::translate("MainWindow", "Serial Connection", nullptr));
        labelSerialPort->setText(QCoreApplication::translate("MainWindow", "Port Name", nullptr));
        labelBaudRate->setText(QCoreApplication::translate("MainWindow", "Baud Rate", nullptr));
        labelStopBits->setText(QCoreApplication::translate("MainWindow", "Stop Bits", nullptr));
        labelDataBits->setText(QCoreApplication::translate("MainWindow", "Data Bits", nullptr));
        labelParity->setText(QCoreApplication::translate("MainWindow", "Parity", nullptr));
        buttonConnect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        buttonRefresh->setText(QCoreApplication::translate("MainWindow", "Refresh", nullptr));
        groupBoxServosAdjust->setTitle(QCoreApplication::translate("MainWindow", "Calibration", nullptr));
        buttonCleanCalibration->setText(QCoreApplication::translate("MainWindow", "Clean", nullptr));
        buttonSaveCalibration->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        buttonCalibration->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        buttonIncreaseAngle->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        buttonDecreaseAngle->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        groupTerminal->setTitle(QCoreApplication::translate("MainWindow", "Terminal", nullptr));
        buttonSendCmd->setText(QCoreApplication::translate("MainWindow", "Send", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabSerial), QCoreApplication::translate("MainWindow", "Serial", nullptr));
        groupBoxActions->setTitle(QCoreApplication::translate("MainWindow", "Default Actions", nullptr));
        buttonPosStretch->setText(QCoreApplication::translate("MainWindow", "Stretch", nullptr));
        buttonPosButtomUp->setText(QCoreApplication::translate("MainWindow", "Hip Up", nullptr));
        buttonPosCheckRd->setText(QCoreApplication::translate("MainWindow", "Look Around", nullptr));
        buttonPosHi->setText(QCoreApplication::translate("MainWindow", "Greeting", nullptr));
        buttonPosPee->setText(QCoreApplication::translate("MainWindow", "Pee", nullptr));
        buttonPosPushUp->setText(QCoreApplication::translate("MainWindow", "Pushup", nullptr));
        buttonPosSit->setText(QCoreApplication::translate("MainWindow", "Sit Down", nullptr));
        buttonPosSleep->setText(QCoreApplication::translate("MainWindow", "Sleep", nullptr));
        buttonPosRest->setText(QCoreApplication::translate("MainWindow", "Rest", nullptr));
        buttonPosStepping->setText(QCoreApplication::translate("MainWindow", "Stepping", nullptr));
        buttonPosBackFlip->setText(QCoreApplication::translate("MainWindow", "Back Flip", nullptr));
        buttonPosBunnyJump->setText(QCoreApplication::translate("MainWindow", "Bunny Jump", nullptr));
        groupBoxServosPanel->setTitle(QCoreApplication::translate("MainWindow", "Bittle Control", nullptr));
        buttonCtrlRestPos->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        buttonCtrlBalance->setText(QCoreApplication::translate("MainWindow", "Balance", nullptr));
        buttonCtrlGyro->setText(QCoreApplication::translate("MainWindow", "Gyro Off", nullptr));
        buttonCtrlServos->setText(QCoreApplication::translate("MainWindow", "Servos Off", nullptr));
        textSpecification->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'.AppleSystemUIFont'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"justify\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Up: 	W 	Normal: 	U</p>\n"
"<p align=\"justify\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Down:	S 	Run: 	I</p>\n"
"<p align=\"justify\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Left:	A	Crawl: 	O</p>\n"
"<p align=\"justify\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Right:	D</p></body></html>", nullptr));
        groupBoxCustomActions->setTitle(QCoreApplication::translate("MainWindow", "GroupBox", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabPanel), QCoreApplication::translate("MainWindow", "Actions", nullptr));
        labelLanguage->setText(QCoreApplication::translate("MainWindow", "Language", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
