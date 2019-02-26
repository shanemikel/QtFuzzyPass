HEADERS	  = $$files(inc/*.hpp)
SOURCES   = $$files(src/*.cpp)
RESOURCES = qrc/resources.qrc

CONFIG += qt
QT     += core
QT     += widgets

CONFIG -= app_bundle
#ICON    = qrc/keychain.icns

INCLUDEPATH    += $$PWD/inc
QMAKE_CXXFLAGS += -std=c++14
#QMAKE_CXXFLAGS += -Wextra -Wdeprecated
OBJECTS_DIR     = out

target.path     = /bin
INSTALLS       += target
