HEADERS	  = $$files(inc/*.hpp)
SOURCES   = $$files(src/*.cpp)
RESOURCES = qrc/resources.qrc

CONFIG += qt
CONFIG -= app_bundle
QT     += core
QT     += widgets

INCLUDEPATH    += $$PWD/inc
QMAKE_CXXFLAGS += -std=c++17
QMAKE_CXXFLAGS += -Wextra -Wdeprecated
OBJECTS_DIR     = out

target.path     = /bin
INSTALLS       += target
