QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += -lWs2_32
LIBS+=$$PWD/speex/lib/libspeex.lib

INCLUDEPATH +=./INET
INCLUDEPATH +=./config
INCLUDEPATH +=./Mediator
include(./md5/md5.pri)
include(./audioapi/audioapi.pri)
include(./uiapi/uiapi.pri)
include(./Videoapi/Videoapi.pri)

INCLUDEPATH += ./Videoapi/
INCLUDEPATH += ./md5/
INCLUDEPATH += ./audioapi/
INCLUDEPATH += ./uiapi/

SOURCES += \
    avdialog.cpp \
    chatdialog.cpp \
    chatuserinfo.cpp \
    ckernel.cpp \
    friendselect.cpp \
    logindialog.cpp \
    main.cpp \
    Mediator/TcpMediator.cpp \
    INET/TcpClient.cpp \
    myui.cpp \
    ourchatdialog.cpp \
    ourchatselect.cpp \
    ourchatuserinfo.cpp \
    userinfo.cpp \
    usershow.cpp

HEADERS += \
    avdialog.h \
    chatdialog.h \
    chatuserinfo.h \
    ckernel.h \
    config/config.h \
    INET/INET.h \
    INET/TcpClient.h \
    Mediator/INetMediator.h \
    Mediator/TcpMediator.h \
    friendselect.h \
    logindialog.h \
    myui.h \
    ourchatdialog.h \
    ourchatselect.h \
    ourchatuserinfo.h \
    userinfo.h \
    usershow.h

FORMS += \
    avdialog.ui \
    chatdialog.ui \
    chatuserinfo.ui \
    friendselect.ui \
    logindialog.ui \
    myui.ui \
    ourchatdialog.ui \
    ourchatselect.ui \
    ourchatuserinfo.ui \
    userinfo.ui \
    usershow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

