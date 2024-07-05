QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dingdan.cpp \
    gushi.cpp \
    hangqing.cpp \
    jiaoyi.cpp \
    jiaoyi2.cpp \
    main.cpp \
    stockdetails.cpp \
    trade_details.cpp \
    widget.cpp \
    zhanghu.cpp

HEADERS += \
    dingdan.h \
    gushi.h \
    hangqing.h \
    jiaoyi.h \
    jiaoyi2.h \
    stockdetails.h \
    trade_details.h \
    widget.h \
    zhanghu.h

FORMS += \
    dingdan.ui \
    gushi.ui \
    hangqing.ui \
    jiaoyi.ui \
    jiaoyi2.ui \
    stockdetails.ui \
    trade_details.ui \
    widget.ui \
    zhanghu.ui

TRANSLATIONS += \
    test3_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
