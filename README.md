## Assignment 1 Dungeon Crawler

This is the provided Qt Creator for the the Dungeon Crawler assignment
for the course COMP3023 Software Development with C++.

Please familiarise yourself the content of this project. Also, do not
forget to initialise a git repository in this folder once you have
extracted the folder to your filesystem.

First thing you will need to do is modify the main.cpp file to include
your name (the author) and the name you would like to call the game.
You may call your game whatever you like.

In this project, all of the class declarations have been provided for
you, except for any additional classes you thought necesayr to include
in your design. You will need to complete the classes with the correct
inheritance, data members, member functions, etc.

Some classes already come with some provided code and/or suggested
interfaces. Code that MUST NOT be changed is clearly marked, while
code that you are allowed to change is clearly marked that you are
allowed to or may need to modify it, as some of the provided
examples do not conform to what you need to end up implementing.

Please read the comments in the files, particularly those with
provided implementations as they will tell you what the code is for.

To reduce the number of files included in the project, some of the
classes have been grouped together. For example, all weapons and
enchantment related classes are included in weapons.h and weapons.cpp.

The following is a brief list of the files included in this project and
their purpose:

- basicdungeon.h/.cpp: header and implementation file for concrete classes
                       related to the Basic Dungeon type.
- character.h/.cpp: header and implementation file for the Character class
- commondungeon.h/.cpp: header and implementation file for concrete classes
                        common to both dungeon types, e.g., OpenDoorway
- creatures.h/.cpp: header and implementation file for the Creature class
- creature_types.csv: a CSV file containing the three original creature types;
                      this is the file you will load when you instantiate your
                      creature prototypes from the data file.
- creature_types_sample.csv: a CSV file used by the CsvFile Unit Tests; DO NOT MODIFY
- csvfile.h/.cpp: header and implementation file for the CsvFile class
- door.h/.cpp: header and implementation file for the abstract Door class
- dungeon.h/.cpp: header and implementation file for the abstract Dungeon class
- game.h/.cpp: header and implementation file for the Game class; includes
               a suggested interface, but can be changed. Implemented helper
               functions must not be changed.
- magicaldungeon.h/.cpp: header and implementation file for concrete classes
                         related to the Magical Dungeon type.
- main.cpp: implementation only, includes the main function
- menuinterface.h/.cpp: header and implementation file for the MenuInterface
                        class; fundamentals are implemented, menus and processing
                        must be completed by you to fulfill the assignment specs.
- room.h/.cpp: header and implementation file for the abstract Room class
- testing.h/.cpp: header and implementation file for the simple Unit Testing
                  framework. Includes complete tests for CsvFile, you should
                  implement additional tests for your own work.
- testingsettings.h: header only, includes some macro defintions to enable/disable testing
- wall.h/.cpp: header and implementation file for the abstract Wall class
- weapons.h/.cpp: header and implementation file for the weapon related classes,
                  such as, Weapon, Fists, Enchantment, FlamingEnchantment, etc.
