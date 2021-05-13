QT       += core gui serialport
ICON      = logo.icns

# localization
TRANSLATIONS += English.ts\
                Chinese.ts


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/CalibFeedbackProcedure.cpp \
    src/Config/JsonHandler.cpp \
    src/Config/SerialConnectionPreference.cpp \
    src/DataPacket/DataPacketHandler.cpp \
    src/MainWindow.cpp \
    src/MainWindow_apx.cpp \
    src/Serial/QSerialMessageQueue.cpp \
    src/Serial/RawMessage.cpp \
    src/UiCalibrationCheck.cpp \
    src/UiMotionControl.cpp \
    src/UiSerialHandler.cpp \
    src/main.cpp \
    src/Basics/QtBasics.cpp

HEADERS += \
    src/Basics/QtBasics.h \
    src/CalibFeedbackProcedure.h \
    src/Config/GlobalConfig.h \
    src/Config/JsonHandler.h \
    src/Config/SerialConnectionPreference.h \
    src/Config/rapidjson/allocators.h \
    src/Config/rapidjson/cursorstreamwrapper.h \
    src/Config/rapidjson/document.h \
    src/Config/rapidjson/encodedstream.h \
    src/Config/rapidjson/encodings.h \
    src/Config/rapidjson/error/en.h \
    src/Config/rapidjson/error/error.h \
    src/Config/rapidjson/filereadstream.h \
    src/Config/rapidjson/filewritestream.h \
    src/Config/rapidjson/fwd.h \
    src/Config/rapidjson/internal/biginteger.h \
    src/Config/rapidjson/internal/clzll.h \
    src/Config/rapidjson/internal/diyfp.h \
    src/Config/rapidjson/internal/dtoa.h \
    src/Config/rapidjson/internal/ieee754.h \
    src/Config/rapidjson/internal/itoa.h \
    src/Config/rapidjson/internal/meta.h \
    src/Config/rapidjson/internal/pow10.h \
    src/Config/rapidjson/internal/regex.h \
    src/Config/rapidjson/internal/stack.h \
    src/Config/rapidjson/internal/strfunc.h \
    src/Config/rapidjson/internal/strtod.h \
    src/Config/rapidjson/internal/swap.h \
    src/Config/rapidjson/istreamwrapper.h \
    src/Config/rapidjson/memorybuffer.h \
    src/Config/rapidjson/memorystream.h \
    src/Config/rapidjson/msinttypes/inttypes.h \
    src/Config/rapidjson/msinttypes/stdint.h \
    src/Config/rapidjson/ostreamwrapper.h \
    src/Config/rapidjson/pointer.h \
    src/Config/rapidjson/prettywriter.h \
    src/Config/rapidjson/rapidjson.h \
    src/Config/rapidjson/reader.h \
    src/Config/rapidjson/schema.h \
    src/Config/rapidjson/stream.h \
    src/Config/rapidjson/stringbuffer.h \
    src/Config/rapidjson/writer.h \
    src/DataPacket/DataPacket.h \
    src/DataPacket/DataPacketHandler.h \
    src/DataPacket/Definitions.h \
    src/MainWindow.h \
    src/Serial/QSerialMessageQueue.h \
    src/Serial/RawMessage.h \
    src/UiCalibrationCheck.h \
    src/UiMotionControl.h \
    src/UiSerialHandler.h


FORMS += \
    mainwindow.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resources.qrc
