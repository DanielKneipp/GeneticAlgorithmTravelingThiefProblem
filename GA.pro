TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ttpinstance.cpp \
    item.cpp \
    city.cpp \
    individual.cpp \
    ttpindividual.cpp \
    features.cpp \
    ttpindividualfeatures.cpp \
    problem.cpp \
    evolutionaryoptimizer.cpp \
    ttpga.cpp \
    selectionmethods.cpp \
    ttpmutationmethods.cpp \
    ttpcrossingmethods.cpp

HEADERS += \
    item.hpp \
    ttpinstance.hpp \
    city.hpp \
    individual.hpp \
    ttpindividual.hpp \
    features.hpp \
    ttpindividualfeatures.hpp \
    problem.hpp \
    evolutionaryoptimizer.hpp \
    ttpga.hpp \
    selectionmethods.hpp \
    ttpmutationmethods.hpp \
    ttpcrossingmethods.hpp

DISTFILES += \
    .gitignore

