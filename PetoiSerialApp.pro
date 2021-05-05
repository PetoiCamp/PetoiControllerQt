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
    frame/CJson.cpp \
    frame/FrameAction.cpp \
    frame/PetoiActionFrame.cpp \
    main.cpp \
    serials/SerialCmdStack.cpp \
    serials/SerialHelper.cpp \
    ui/QtUtilities.cpp \
    ui/logger.cpp \
    ui/mainwindow.cpp \
    ui/mainwindow_actions.cpp \
    ui/mainwindow_apx.cpp \
    ui/mainwindow_frames.cpp \
    ui/mainwindow_panel.cpp \
    ui/mainwindow_serial.cpp

HEADERS += \
    frame/CJson.h \
    frame/FrameAction.h \
    frame/PetoiActionFrame.h \
    frame/rapidjson/allocators.h \
    frame/rapidjson/cursorstreamwrapper.h \
    frame/rapidjson/document.h \
    frame/rapidjson/encodedstream.h \
    frame/rapidjson/encodings.h \
    frame/rapidjson/error/en.h \
    frame/rapidjson/error/error.h \
    frame/rapidjson/filereadstream.h \
    frame/rapidjson/filewritestream.h \
    frame/rapidjson/fwd.h \
    frame/rapidjson/internal/biginteger.h \
    frame/rapidjson/internal/clzll.h \
    frame/rapidjson/internal/diyfp.h \
    frame/rapidjson/internal/dtoa.h \
    frame/rapidjson/internal/ieee754.h \
    frame/rapidjson/internal/itoa.h \
    frame/rapidjson/internal/meta.h \
    frame/rapidjson/internal/pow10.h \
    frame/rapidjson/internal/regex.h \
    frame/rapidjson/internal/stack.h \
    frame/rapidjson/internal/strfunc.h \
    frame/rapidjson/internal/strtod.h \
    frame/rapidjson/internal/swap.h \
    frame/rapidjson/istreamwrapper.h \
    frame/rapidjson/memorybuffer.h \
    frame/rapidjson/memorystream.h \
    frame/rapidjson/msinttypes/inttypes.h \
    frame/rapidjson/msinttypes/stdint.h \
    frame/rapidjson/ostreamwrapper.h \
    frame/rapidjson/pointer.h \
    frame/rapidjson/prettywriter.h \
    frame/rapidjson/rapidjson.h \
    frame/rapidjson/reader.h \
    frame/rapidjson/schema.h \
    frame/rapidjson/stream.h \
    frame/rapidjson/stringbuffer.h \
    frame/rapidjson/writer.h \
    rapidjson/allocators.h \
    rapidjson/cursorstreamwrapper.h \
    rapidjson/document.h \
    rapidjson/encodedstream.h \
    rapidjson/encodings.h \
    rapidjson/error/en.h \
    rapidjson/error/error.h \
    rapidjson/filereadstream.h \
    rapidjson/filewritestream.h \
    rapidjson/fwd.h \
    rapidjson/internal/biginteger.h \
    rapidjson/internal/clzll.h \
    rapidjson/internal/diyfp.h \
    rapidjson/internal/dtoa.h \
    rapidjson/internal/ieee754.h \
    rapidjson/internal/itoa.h \
    rapidjson/internal/meta.h \
    rapidjson/internal/pow10.h \
    rapidjson/internal/regex.h \
    rapidjson/internal/stack.h \
    rapidjson/internal/strfunc.h \
    rapidjson/internal/strtod.h \
    rapidjson/internal/swap.h \
    rapidjson/istreamwrapper.h \
    rapidjson/memorybuffer.h \
    rapidjson/memorystream.h \
    rapidjson/msinttypes/inttypes.h \
    rapidjson/msinttypes/stdint.h \
    rapidjson/ostreamwrapper.h \
    rapidjson/pointer.h \
    rapidjson/prettywriter.h \
    rapidjson/rapidjson.h \
    rapidjson/reader.h \
    rapidjson/schema.h \
    rapidjson/stream.h \
    rapidjson/stringbuffer.h \
    rapidjson/writer.h \
    serials/SerialCmdStack.h \
    serials/SerialHelper.h \
    ui/QtUtilities.h \
    ui/logger.h \
    ui/mainwindow.h

FORMS += \
    ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resources.qrc
