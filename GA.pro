TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ttpinstance.cpp \
    item.cpp \
    city.cpp

HEADERS += \
    item.hpp \
    ttpinstance.hpp \
    city.hpp

DISTFILES += \
    .gitignore

