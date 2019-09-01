TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG += qt
CONFIG += file_copies

macx:QMAKE_CXXFLAGS += -std=c++17 # override for clang > 3.4 on mac (latest version do not necessarily need this anymore)

#TARGET = dungeon_crawler

HEADERS += \
    csvfile.h \
    dungeonbuilder.h \
    game.h \
    menuinterface.h \
    testingsettings.h \
    testing.h \
    character.h \
    dungeon.h \
    room.h \
    wall.h \
    door.h \
    basicdungeon.h \
    magicaldungeon.h \
    commondungeon.h \
    creatures.h \
    weapons.h

SOURCES += \
    csvfile.cpp \
    dungeonbuilder.cpp \
    main.cpp \
    game.cpp \
    menuinterface.cpp \
    testing.cpp \
    character.cpp \
    dungeon.cpp \
    room.cpp \
    wall.cpp \
    door.cpp \
    basicdungeon.cpp \
    magicaldungeon.cpp \
    commondungeon.cpp \
    creatures.cpp \
    weapons.cpp

INCLUDEPATH +=

#DEFINES =

DISTFILES += \
    README.md \
    creature_types.csv \
    creature_types_sample.csv \
    input_script.txt

COPIES += data_files
data_files.files = $$files(*.csv)
data_files.files += input_script.txt
data_files.path = $$OUT_PWD
