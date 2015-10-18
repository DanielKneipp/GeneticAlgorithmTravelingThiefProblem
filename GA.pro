TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXX = g++-5

SOURCES += main.cpp \
    ttp/ttpinstance.cpp \
    ttp/item.cpp \
    ttp/city.cpp \
#    generic_ga/individual.cpp \
    ttp/ttpindividual.cpp \
    generic_ga/features.cpp \
    ttp/ttpindividualfeatures.cpp \
#    generic_ga/problem.cpp \
#    generic_ga/evolutionaryoptimizer.cpp \
    ttp/ttpga.cpp \
#    generic_ga/selectionmethods.cpp \
    ttp/ttpmutationmethods.cpp \
    utils/individualrecorder.cpp \
#    generic_ga/mutationmethods.cpp \
#    generic_ga/crossovermethods.cpp \
    ttp/ttpcrossovermethods.cpp

HEADERS += \
    ttp/item.hpp \
    ttp/ttpinstance.hpp \
    ttp/city.hpp \
    generic_ga/individual.hpp \
    ttp/ttpindividual.hpp \
    generic_ga/features.hpp \
    ttp/ttpindividualfeatures.hpp \
    generic_ga/problem.hpp \
    generic_ga/evolutionaryoptimizer.hpp \
    ttp/ttpga.hpp \
    generic_ga/selectionmethods.hpp \
    ttp/ttpmutationmethods.hpp \
    utils/individualrecorder.hpp \
    utils/geneticutils.hpp \
    generic_ga/mutationmethods.hpp \
    generic_ga/crossovermethods.hpp \
    ttp/ttpcrossovermethods.hpp

DISTFILES += \
    .gitignore \
    plotGAData.gp \
    README.md
