QT       += core gui serialport multimedia
ICON      = logo.icns

# localization
TRANSLATIONS += English.ts\
                Chinese.ts


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES +=  \
    src/Basics/QtBasics.cpp \
    src/Config/GlobalConfig.cpp \
    src/DataPacket/DataPacketHandler.cpp \
    src/Json/JsonHandler.cpp \
    src/Main/Components/Calibration/CalibFeedbackProcedure.cpp \
    src/Main/Components/Calibration/UiCalibrationCheck.cpp \
    src/Main/Components/CustomCmds/DialogCustomActions.cpp \
    src/Main/Components/CustomCmds/UiCustomActions.cpp \
    src/Main/Components/DefaultControls/UiMotionControl.cpp \
    src/Main/Components/Serials/SerialConnectionPreference.cpp \
    src/Main/Components/Serials/UiSerialHandler.cpp \
    src/Main/MainWindow_apx.cpp \
    src/Main/MainWindow_ui.cpp \
    src/Serial/QSerialMessageQueue.cpp \
    src/Serial/RawMessage.cpp \
    src/main.cpp
  

HEADERS +=  \
    src/Basics/QtBasics.h \
    src/Config/GlobalConfig.h \
    src/DataPacket/DataPacket.h \
    src/DataPacket/DataPacketHandler.h \
    src/DataPacket/Definitions.h \
    src/Json/JsonHandler.h \
    src/Json/rapidjson/allocators.h \
    src/Json/rapidjson/cursorstreamwrapper.h \
    src/Json/rapidjson/document.h \
    src/Json/rapidjson/encodedstream.h \
    src/Json/rapidjson/encodings.h \
    src/Json/rapidjson/error/en.h \
    src/Json/rapidjson/error/error.h \
    src/Json/rapidjson/filereadstream.h \
    src/Json/rapidjson/filewritestream.h \
    src/Json/rapidjson/fwd.h \
    src/Json/rapidjson/internal/biginteger.h \
    src/Json/rapidjson/internal/clzll.h \
    src/Json/rapidjson/internal/diyfp.h \
    src/Json/rapidjson/internal/dtoa.h \
    src/Json/rapidjson/internal/ieee754.h \
    src/Json/rapidjson/internal/itoa.h \
    src/Json/rapidjson/internal/meta.h \
    src/Json/rapidjson/internal/pow10.h \
    src/Json/rapidjson/internal/regex.h \
    src/Json/rapidjson/internal/stack.h \
    src/Json/rapidjson/internal/strfunc.h \
    src/Json/rapidjson/internal/strtod.h \
    src/Json/rapidjson/internal/swap.h \
    src/Json/rapidjson/istreamwrapper.h \
    src/Json/rapidjson/memorybuffer.h \
    src/Json/rapidjson/memorystream.h \
    src/Json/rapidjson/msinttypes/inttypes.h \
    src/Json/rapidjson/msinttypes/stdint.h \
    src/Json/rapidjson/ostreamwrapper.h \
    src/Json/rapidjson/pointer.h \
    src/Json/rapidjson/prettywriter.h \
    src/Json/rapidjson/rapidjson.h \
    src/Json/rapidjson/reader.h \
    src/Json/rapidjson/schema.h \
    src/Json/rapidjson/stream.h \
    src/Json/rapidjson/stringbuffer.h \
    src/Json/rapidjson/writer.h \
    src/Main/Components/Calibration/CalibFeedbackProcedure.h \
    src/Main/Components/Calibration/UiCalibrationCheck.h \
    src/Main/Components/CustomCmds/DialogCustomActions.h \
    src/Main/Components/CustomCmds/UiCustomActions.h \
    src/Main/Components/DefaultControls/UiMotionControl.h \
    src/Main/Components/Serials/SerialConnectionPreference.h \
    src/Main/Components/Serials/UiSerialHandler.h \
    src/Main/MainWindow.h \
    src/Serial/QSerialMessageQueue.h \
    src/Serial/RawMessage.h


FORMS += \
    ui/DialogCustomActions.ui \
    ui/MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resources.qrc
