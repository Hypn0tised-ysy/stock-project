QT += core gui widgets

CONFIG += c++17

win32-msvc*:QMAKE_CXXFLAGS += /utf-8
# QMAKE_LFLAGS += "/MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\""

SOURCES += \
    $$files($$PWD/src/AllWindow/*.cpp) \
    $$files($$PWD/src/database/*.cpp) \
    $$files($$PWD/src/implementation/*.cpp) \
    $$files($$PWD/src/implementation/Accountdata/*.cpp) \
    $$files($$PWD/src/*.cpp)

HEADERS += \
    $$files($$PWD/src/AllWindow/*.h) \
    $$files($$PWD/src/database/*.h) \
    $$files($$PWD/src/implementation/*.h) \
    $$files($$PWD/src/implementation/Accountdata/*.h) \
    $$files($$PWD/src/*.h)

FORMS += \
    $$files($$PWD/src/AllWindow/*.ui)
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target