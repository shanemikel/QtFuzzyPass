HEADERS	  = $$files(inc/*.h)
SOURCES   = $$files(src/*.cpp)
RESOURCES = qrc/resources.qrc

CONFIG += qt
CONFIG -= app_bundle
QT     += core

OBJECTS_DIR     = out
target.path     = /bin
INSTALLS       += target
QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS += -Wno-endif-labels
