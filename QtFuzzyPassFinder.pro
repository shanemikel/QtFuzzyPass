HEADERS	  = $$files(inc/*.h)
SOURCES   = $$files(src/*.cpp)
#RESOURCES = qrc/resources.qrc

CONFIG += qt
CONFIG -= app_bundle
QT     += core

OBJECTS_DIR  = out
target.path  = /bin
INSTALLS    += target
