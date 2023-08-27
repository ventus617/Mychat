TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lpthread -lmysqlclient

SOURCES += \
        ../myqq/INET/TcpNet.cpp \
        ../myqq/Mediator/TcpMediator.cpp \
        ../myqq/kernel/kernel.cpp \
        ../myqq/md5/md5.cpp \
        INet.cpp \
        INetMediator.cpp \
        main.cpp \
        mysql.cpp

DISTFILES += \
    ../myqq/md5/md5.pri

HEADERS += \
    ../myqq/INET/INET.h \
    ../myqq/INET/TcpNet.h \
    ../myqq/Mediator/INetMediator.h \
    ../myqq/Mediator/TcpMediator.h \
    ../myqq/config/config.h \
    ../myqq/kernel/kernel.h \
    ../myqq/md5/md5.h \
    mysql.h

