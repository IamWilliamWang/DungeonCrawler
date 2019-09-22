#include "testing.h"

#include "basicdungeon.h"
#include "character.h"
#include "commondungeon.h"
#include "creatures.h"
#include "csvfile.h"
#include "door.h"
#include "dungeon.h"
#include "dungeonbuilder.h"
#include "game.h"
#include "weapons.h"
#include "magicaldungeon.h"
#include "room.h"
#include "wall.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>
#include <memory>
#include <string>

/*
 * IMPLEMENT your tests in this file as required.
 *
 * You may need to edit the original test implementations as you implement your design.
 * The original test implementations are just simple examples that do not necessarily
 * reflect the final application.
 */

using namespace core;
using namespace data;
using namespace dungeon;
using namespace creatures;
using std::cout;
using std::endl;
using std::setw;

void Testing::runTests() {
  cout << std::left << std::setfill('.');
  csvFileTestSuite(); // Runs all of the CsvFile tests
  cout << setw(72) << "Character class tests " << testCharacter()  << endl;
  cout << setw(72) << "Creature class tests "  << testCreature()   << endl;
  cout << setw(72) << "Door class tests "      << testDoor()       << endl;
  cout << setw(72) << "Dungeon class tests "   << testDungeon()    << endl;
  cout << setw(72) << "Game class tests "      << testGame()       << endl;
  cout << setw(72) << "Weapon class tests "    << testWeapon()     << endl;
  cout << setw(72) << "Room class tests "      << testRoom()       << endl;
  cout << setw(72) << "Wall class tests "      << testWall()       << endl;
}

std::string Testing::testCharacter() {
  _failure = false; // ensure this is at the beggining of each test

  // test Character.name
  std::string name{"Character Name"};
  Character c{name};
  equal<std::string>(name, c.name(),   "Character .name() does not match constructor value");
  // test Character.setAttribute
  c.setAttribute(3, 2, 1);
  equal(3, c.getStrength(), "Failed to set/get strength.");
  equal(2, c.getDexterity(), "Failed to set/get dexterity.");
  equal(1, c.getWisdom(), "Failed to set/get wisdom.");
  // test Character.setAttribute without vaild checking
  c.setAttribute(100, 90, 200, false);
  equal(100, c.getStrength(), "Failed to set/get strength without vaild judgment.");
  equal(90, c.getDexterity(), "Failed to set/get dexterity without vaild judgment.");
  equal(200, c.getWisdom(), "Failed to set/get wisdom without vaild judgment.");
  // test Character.setDescription
  c.setDescription("Character description.");
  equal<std::string>("Character description.", c.getDescription(), "Failed to get description.");
  // test Character.setWeapon
  c.setWeapon(std::make_shared<weapons::MagicWand>());
  equal<std::string>("Magic Wand", c.getWeapon()->getName(), "Failed to get name of Magic Wand.");
  c.setWeapon(std::make_shared<weapons::WizardsStaff>());
  equal<std::string>("Wizard's Staff", c.getWeapon()->getName(), "Failed to get name of Wizard's Staff.");
  // test Character.isAlive
  c.setHealthPoint(-1);
  equal<bool>(false, c.isAlive(), "Failed to die.");

  return passFailText();
}

std::string Testing::testCreature() {
  _failure = false; // ensure this is at the beggining of each test

  // test Creature.name
  std::string name{"Creature Name"};
  Creature c{name};
  equal<std::string>(name, c.name(),   "Creature .name() does not match constructor value");
  // test Creature.setAttribute
  c.setAttribute(100, 90, 200, false);
  equal(100, c.getStrength(), "Failed to get/set strength.");
  equal(90, c.getDexterity(), "Failed to get/set dexterity.");
  equal(200, c.getWisdom(), "Failed to get/set wisdom.");
  // test Creature.setDescription
  c.setDescription("Creature description.");
  equal<std::string>("Creature description.", c.getDescription(), "Failed to get description.");
  // test Creature.isAlive
  c.setHealthPoint(-1);
  equal(false, c.isAlive(), "Failed to die.");

  return passFailText();
}
std::string Testing::testDoor() {
  _failure = false; // ensure this is at the beggining of each test

  // test Door.getNeighbourRoom
  std::shared_ptr<dungeon::Room> room1 = std::make_shared<dungeon::Room>(1), room2 = std::make_shared<dungeon::Room>(2);
  dungeon::Door door{room1, room2};
  equal(room1->id(), door.getNeighbourRoom(room2)->id(), "Failed to get neighbour room.");
  equal(room2->id(), door.getNeighbourRoom(room1)->id(), "Failed to get neighbour room.");

  return passFailText();
}
std::string Testing::testDungeon() {
  _failure = false; // ensure this is at the beggining of each test

  int roomId{1};
  std::shared_ptr<Room> room{std::make_shared<Room>(roomId)};

  Dungeon dungeon{};

  // test Dungeon.addRoom&retrieveRoom
  dungeon.addRoom(room);
  equal(room, dungeon.retrieveRoom(roomId), "Dungeon .add/.retrieveRoom() failure, does not return room that was added");
  // test Dungeon.getEntranceRoom
  room->addEntranceOrExit('N', true);
  equal(1, dungeon.getEntranceRoom()->id(), "Failed to get entrance room.");
  // test Dungeon.setNowRoom&getNowRoom
  dungeon.setNowRoom(room);
  equal(1, dungeon.getNowRoom()->id(), "Failed to get now room or room's id.");
  // test Dungeon.path
  equal(1, dungeon.path(-1)->id(), "Failed to get last room in path.");
  equal(1, dungeon.path(1)->id(), "Failed to get first room in path.");

  return passFailText();
}

std::string Testing::testGame() {
  _failure = false;

  Game game = *Game::instance();

  // test Game.setPlayer&player
  game.setPlayer(std::shared_ptr<Character>(new Character("testing")));
  equal<std::string>("testing", game.player()->name(), "The saved player has no name.");

  // test Game.createDungeon&getBasicDungeon&&getMagicalDungeon
  equal(true, game.createDungeon("BasicDungeon"), "Create basic dungeon failed.");
  equal(true, game.getBasicDungeon() != nullptr, "Get basic dungeon failed.");
  equal(false, game.getMagicalDungeon() != nullptr, "Converte basic dungeon to magical dungeon is not allowed.");

  // test DungeonBuilder.buildDungeon
  auto magicalDungeonBulider = std::make_shared<MagicalDungeonBuilder>();
  game.setDungeon(magicalDungeonBulider->buildDungeon());
  equal(false, game.getBasicDungeon() != nullptr, "Converte magical dungeon to basic dungeon is not allowed.");
  equal(true, game.getMagicalDungeon() != nullptr, "Get magical dungeon failed.");

  // test Game.getMagicalDungeon&enterDungeon&navigate&navigateBack&currentRoom
  auto room1 = std::make_shared<Room>(1), room2 = std::make_shared<Room>(2);
  auto door = std::make_shared<Door>(room1, room2);
  equal(true, room1->addDoor('E', door), "Failed to add door.");
  equal(true, room2->addDoor('W', door), "Failed to add door.");
  equal(true, game.getMagicalDungeon()->addRoom(room1), "Failed to add room.");
  equal(true, game.getMagicalDungeon()->addRoom(room2), "Failed to add room.");
  equal(true, game.enterDungeon(), "Failed to enter dungeon.");
  equal(true, game.navigate('E'), "Failed to navigate to east.");
  equal(true, game.navigateBack(), "Failed to navigate back.");
  equal(1, game.currentRoom()->id(), "Failed to get current room.");

  // test Game.exitDungeon
  game.exitDungeon();
  equal(true, game.player() == nullptr, "Not cleaning up player after exiting the dungeon.");
  equal(true, game.dungeon() == nullptr, "Not cleaning up dungeon after exiting the dungeon.");

  // The following tests the random number generation.
  int value{game.randomIntBetweenInc(5, 0)};
  greaterThan(-1, value, "Swapping the min and max (incl.) did not work. Got negative value.");
  lessThan(6, value, "Swapping the min and max (incl.) did not work. value out of range.");

  value = game.randomIntBetweenEx(5, 0);
  greaterThan(-1, value, "Swapping the min and max (excl.) did not work. Got negative value.");
  lessThan(5, value, "Swapping the min and max (excl.) did not work. value out of range.");

  for (int i{0}; i < 1000; ++i) {
    // Not really a good test for this, but just in case.
    int value = game.randomIntBetweenInc(2, 5);
    greaterThan(1, value, "Game .randomIntBetweenInc somehow generated a value out of range");
    lessThan(6, value, "Game .randomIntBetweenInc somehow generated a value out of range");
  }

  for (int i{0}; i < 1000; ++i) {
    // Not really a good test for this, but just in case.
    int value = game.randomIntBetweenEx(2, 5);
    greaterThan(1, value, "Game .randomIntBetweenEx somehow generated a value out of range");
    lessThan(5, value, "Game .randomIntBetweenEx somehow generated a value out of range");
  }

  for (int i{0}; i < 1000; ++i) {
    // Not really a good test for this, but just in case.
    double value = game.randomDouble();
    double tinyValueBelow1{std::nextafter(0.0, std::numeric_limits<double>::min())};
    greaterThan(tinyValueBelow1, value, "Game .randomDouble somehow generated a value out of range");
    lessThan(1.0, value, "Game .randomDouble somehow generated a value out of range");
  }

  return passFailText();
}

std::string Testing::testWeapon() {
  _failure = false; // ensure this is at the beggining of each test

  // test Weapon.getDescription&getLongDescription&get
  auto fists = std::make_shared<weapons::Fists>();
  equal<std::string>("you look down at your fists and shrug, \"these will do\"", fists->getDescription(), "Failed to get description of Fists.");
  equal<std::string>("Fists are the weapon of choice for someone who has nothing else.", fists->getLongDescription(), "Failed to get long description of Fists.");
  equal(4, fists->get(), "Failed to get damage of Fists.");

  // test Weapon.getDamageRange
  auto battleAxe = std::make_shared<weapons::BattleAxe>();
  auto damageRange = battleAxe->getDamageRange();
  equal(10, damageRange[0], "Failed to get min damage of Battle Axe.");
  equal(15, damageRange[1], "Failed to get max damage of Battle Axe.");

  // test Weapon.setPrefixEnchantment&setSuffixEnchantment&getFullName&getSpecialAbilityDescription
  auto magicWand = std::make_shared<weapons::MagicWand>();
  magicWand->setPrefixEnchantment(std::make_shared<weapons::ElectricityEnchantment>());
  magicWand->setSuffixEnchantment(std::make_shared<weapons::VampirismEnchantment>());
  equal<std::string>("Electrified Magic Wand of Vampirism", magicWand->getFullName(), "Failed to get full name of Magic Wand.");
  equal<std::string>("Healing: returns character to full health.", magicWand->getSpecialAbilityDescription(), "Failed to get special ability desccription of Magic Wand");

  return passFailText();
}

std::string Testing::testRoom() {
    _failure = false;

    // test Room.id
    int roomId{1};
    Room room{roomId};
    equal(roomId, room.id(), "Room .id() does not match constructor value");

    // test Room.addEntranceOrExit&getEntranceDirection&existEntranceOrExit&addDoor&findDoorDirections
    auto room1 = std::make_shared<Room>(1), room2 = std::make_shared<Room>(2), room3 = std::make_shared<Room>(3), room4 = std::make_shared<Room>(4);
    room1->addEntranceOrExit('N', true);
    equal('N', room1->getEntranceDirection(), "Failed to get entrance direction.");
    equal(true, room1->existEntranceOrExit(), "Failed to set entrance direcion.");
    room.addDoor('S', std::shared_ptr<Door>(new Door(room1, room2)));
    equal<int>(1, static_cast<int>(room.getDoorDirections().size()), "Can't find direction of door(s).");

    return passFailText();
}

std::string Testing::testWall() {
  _failure = false; // ensure this is at the beggining of each test

  Wall wall{};
  return passFailText();
}

// TODO: implement the rest of your tests here


// CsvFile tests: Do NOT modify! (except in the following suggestion)
// It is recommended that you perform the following:
// - Comment out all but the first test.
// - Once the first test passes, activate the second while leaving the first
//   test active.
// - Once the second test passes, move to the third test, etc.
// Doing it this way will incrementally build up the functionality of your
// CsvFile class while ensuring all of the previous tests still pass as you
// make changes to your implementation.
void Testing::csvFileTestSuite()
{
  cout << setw(72) << "CsvFile: Test Empty CSV file " << testLoadFailureForEmptyCsvFile() << endl;
  cout << setw(72) << "CsvFile: Test CSV file with Header but no rows " << testLoadSuccessForHeaderButNoDataCsvFile() << endl;
  cout << setw(72) << "CsvFile: Test Out of Range Returns Empty string " << testOutOfRangeReturnsEmptyString() << endl;
  cout << setw(72) << "CsvFile: Test Correct Header Fields read in " << testHeaderFieldsCorrectlyRead() << endl;
  cout << setw(72) << "CsvFile: Test Correct Row data read in and accessible " << testCommaSeparatedRowDataAccessible() << endl;
  cout << setw(72) << "CsvFile: Test Multi-Row CSV data is accessible " << testMultipleRowsOfData() << endl;
  cout << setw(72) << "CsvFile: Test Load failure for differing number of columns " << testLoadFailureOnRowWithDifferingNumberOfColumns() << endl;
  cout << setw(72) << "CsvFile: Test preservation of whitespace in fields " << testPreservationOfWhitespaceInFields() << endl;
  cout << setw(72) << "CsvFile: Test line endings of last line " << testLineEndingOnLastLine() << endl;
  cout << setw(72) << "CsvFile: Test double quoted fields (no internal quotes) " << testDoubleQuotedFields() << endl;
  cout << setw(72) << "CsvFile: Test double quoted fields (mixed some quoted,some not) " << testDoubleQuotedFieldsMixedWithUnquoted() << endl;
  cout << setw(72) << "CsvFile: Test replace of '\\n' with newline character in quoted fields " << testReplacementOfBlackslashNInQuotedFieldsWithNewline() << endl;
  cout << setw(72) << "CsvFile: Test double quotes within fields " << testDoubleQuotesWithinFields() << endl;
  cout << setw(72) << "CsvFile: Test putting it all together, load sample creature file " << testReadingCsvDataFromFile() << endl;
}

std::string Testing::testLoadFailureForEmptyCsvFile()
{
  std::stringstream data{""};
  CsvFile csvFile{data};

  equal(-1, csvFile.numberOfRows(), "numberOfRows() must indicate load failure for empty input data");
  equal(-1, csvFile.numberOfColumns(), "numberOfColumns() must indicate load failure for empty input data");
  equal<std::string>("", csvFile.at(1, 1), "at(int,int) must return empty string for empty input data");
  equal<std::string>("", csvFile.headerAt(1), "headerAt(int) must return empty string for empty input data");
  equal(-1, csvFile.columnIndexOf("Name"), "columnIndexOf(string) must return -1 for empty input data");

  return passFailText();
}

std::string Testing::testLoadSuccessForHeaderButNoDataCsvFile()
{
  std::stringstream data{"Header"};
  CsvFile csvFile{data};

  equal(0, csvFile.numberOfRows(), "numberOfRows() must indicate the number of rows in the data for successful load");
  equal(1, csvFile.numberOfColumns(), "numberOfColumns() must indicate the number of columns for successful load");
  equal<std::string>("", csvFile.at(1, 1), "at(int,int) must return empty string for empty no rows (out of range)");
  equal<std::string>("Header", csvFile.headerAt(1), "headerAt(int) must return the column name for successful load");
  equal(1, csvFile.columnIndexOf("Header"), "columnIndexOf(string) must return index for for successful load");

  return passFailText();
}

std::string Testing::testOutOfRangeReturnsEmptyString()
{
  std::stringstream data{R":(Header1,Header2
Cell 1,Cell 2
):"};
  CsvFile csvFile{data};

  equal<std::string>("", csvFile.headerAt(3), "headerAt() must return empty string when index out of range");
  equal<std::string>("", csvFile.headerAt(0), "headerAt() must return empty string when index out of range (zero is out of range)");
  equal<std::string>("", csvFile.at(2,1), "at() must return empty string when row index out of range");
  equal<std::string>("", csvFile.at(0,1), "at() must return empty string when row index out of range (zero is out of range)");
  equal<std::string>("", csvFile.at(1,3), "at() must return empty string when column index out of range");
  equal<std::string>("", csvFile.at(1,0), "at() must return empty string when column index out of range (zero is out of range)");

  return  passFailText();
}

std::string Testing::testHeaderFieldsCorrectlyRead()
{
  std::stringstream data{R":(Header1,Header2,Header3):"};
  CsvFile csvFile{data};

  equal(0, csvFile.numberOfRows(), "numberOfRows() must indicate zero, as only the header is present");
  equal(3, csvFile.numberOfColumns(), "numberOfColumns() must indicate 3 columns for the three header fields");
  equal<std::string>("Header1", csvFile.headerAt(1), "headerAt(1) must return the first header field");
  equal<std::string>("Header2", csvFile.headerAt(2), "headerAt(2) must return the second header field");
  equal<std::string>("Header3", csvFile.headerAt(3), "headerAt(3) must return the third header field");

  return passFailText();
}

std::string Testing::testCommaSeparatedRowDataAccessible()
{
  std::stringstream data{R":(Header1,Header2,Header3
Field1,Field2,Field3):"};
  CsvFile csvFile{data};

  equal(1, csvFile.numberOfRows(), "numberOfRows() must indicate 1, as the header + 1 row is present");
  equal(3, csvFile.numberOfColumns(), "numberOfColumns() must indicate 3 columns for the three fields");
  equal<std::string>("Field1", csvFile.at(1,1), "at(1,1) must return the first field of the first row");
  equal<std::string>("Field2", csvFile.at(1,2), "at(1,2) must return the second field of the first row");
  equal<std::string>("Field3", csvFile.at(1,3), "at(1,3) must return the third field of the first row");

  return passFailText();
}

std::string Testing::testMultipleRowsOfData()
{
  std::stringstream data{R":(Header1,Header2,Header3
Row1Field1,Row1Field2,Row1Field3
Row2Field1,Row2Field2,Row2Field3
Row3Field1,Row3Field2,Row3Field3):"};
  CsvFile csvFile{data};

  equal(3, csvFile.numberOfRows(), "numberOfRows() must indicate 3, as the header + 3 rows are present");
  equal(3, csvFile.numberOfColumns(), "numberOfColumns() must indicate 3 columns for the three fields");

  equal<std::string>("Row1Field1", csvFile.at(1,1), "at(1,1) must return the first field of the first row");
  equal<std::string>("Row1Field2", csvFile.at(1,2), "at(1,2) must return the second field of the first row");
  equal<std::string>("Row1Field3", csvFile.at(1,3), "at(1,3) must return the third field of the first row");

  equal<std::string>("Row2Field1", csvFile.at(2,1), "at(2,1) must return the first field of the second row");
  equal<std::string>("Row2Field2", csvFile.at(2,2), "at(2,2) must return the second field of the second row");
  equal<std::string>("Row2Field3", csvFile.at(2,3), "at(2,3) must return the third field of the second row");

  equal<std::string>("Row3Field1", csvFile.at(3,1), "at(3,1) must return the first field of the third row");
  equal<std::string>("Row3Field2", csvFile.at(3,2), "at(3,2) must return the second field of the third row");
  equal<std::string>("Row3Field3", csvFile.at(3,3), "at(3,3) must return the third field of the third row");

  return passFailText();
}

std::string Testing::testLoadFailureOnRowWithDifferingNumberOfColumns()
{
  std::stringstream dataExtraColumnInRow{R":(Header1,Header2
Field1,Field2,Field3Error):"};
  CsvFile csvFile{dataExtraColumnInRow};

  equal(-1, csvFile.numberOfRows(), "numberOfRows() must indicate load failure for row with extra column");
  equal(-1, csvFile.numberOfColumns(), "numberOfColumns() must indicate load failure for row with extra column");

  std::stringstream dataMissingColumnInRow{R":(Header1,Header2
Field1):"};
  csvFile = CsvFile{dataMissingColumnInRow};

  equal(-1, csvFile.numberOfRows(), "numberOfRows() must indicate load failure for row with missing column");
  equal(-1, csvFile.numberOfColumns(), "numberOfColumns() must indicate load failure for row with missing column");

  return passFailText();
}

std::string Testing::testPreservationOfWhitespaceInFields()
{
  std::stringstream data{"  Header1,  Header2,Header3  ,Header  4,  Header  5  ,Header6  \n"
"  Field1,  Field2,Field3  ,Field  4,  Field  5  ,Field6  "};
  CsvFile csvFile{data};

  equal(1, csvFile.numberOfRows(), "numberOfRows() must be 1 for whitespace test");
  equal(6, csvFile.numberOfColumns(), "numberOfColumns() must be 6 for whitespace test");

  equal<std::string>("  Header1", csvFile.headerAt(1), "headerAt(1) must preserve whitespace at line beginning");
  equal<std::string>("  Header2", csvFile.headerAt(2), "headerAt(2) must preserve whitespace after comma");
  equal<std::string>("Header3  ", csvFile.headerAt(3), "headerAt(3) must preserve whitespace before comma");
  equal<std::string>("Header  4", csvFile.headerAt(4), "headerAt(4) must preserve internal whitespace");
  equal<std::string>("  Header  5  ", csvFile.headerAt(5), "headerAt(5) must preserve all whitespace");
  equal<std::string>("Header6  ", csvFile.headerAt(6), "headerAt(6) must preserve whitespace at line end");

  equal<std::string>("  Field1", csvFile.at(1,1), "at(1, 1) must preserve whitespace at line beginning");
  equal<std::string>("  Field2", csvFile.at(1,2), "at(1, 2) must preserve whitespace after comma");
  equal<std::string>("Field3  ", csvFile.at(1, 3), "at(1, 3) must preserve whitespace before comma");
  equal<std::string>("Field  4", csvFile.at(1, 4), "at(1, 4) must preserve internal whitespace");
  equal<std::string>("  Field  5  ", csvFile.at(1, 5), "at(1, 5) must preserve all whitespace");
  equal<std::string>("Field6  ", csvFile.at(1,6), "at(1, 6) must preserve whitespace at line end");

  return passFailText();
}

std::string Testing::testLineEndingOnLastLine()
{
  std::stringstream data{R":(Header1
Field1):"};
  CsvFile csvFile{data};

  equal(1, csvFile.numberOfRows(), "numberOfRows() must be 1 for line ending test, without extra CRLF");
  equal(1, csvFile.numberOfColumns(), "numberOfColumns() must be 1 for line ending test, without extra CRLF");

  data = std::stringstream{R":(Header1
Field1
):"};
  csvFile = CsvFile{data};

  equal(1, csvFile.numberOfRows(), "numberOfRows() must be 1 for line ending test, WITH extra CRLF");
  equal(1, csvFile.numberOfColumns(), "numberOfColumns() must be 1 for line ending test, WITH extra CRLF");

  return passFailText();
}

std::string Testing::testDoubleQuotedFields()
{
  std::stringstream data{R":("Header,1","Header,2","Header,3","  Header  4  "
"Field,1","Field,2","Field,3","  Field  4  "):"};
  CsvFile csvFile{data};

  equal(1, csvFile.numberOfRows(), "numberOfRows() must indicate 1, as the header + 1 row is present (double quote test)");
  equal(4, csvFile.numberOfColumns(), "numberOfColumns() must indicate 4 columns for the four fields (double quote test)");

  equal<std::string>("Header,1", csvFile.headerAt(1), "headerAt(1) must return the first header without quotes");
  equal<std::string>("Header,2", csvFile.headerAt(2), "headerAt(2) must return the second header without quotes");
  equal<std::string>("Header,3", csvFile.headerAt(3), "headerAt(3) must return the third header without quotes");
  equal<std::string>("  Header  4  ", csvFile.headerAt(4), "headerAt(4) must return the fourth header without quotes, preserving whitespace");

  equal<std::string>("Field,1", csvFile.at(1,1), "at(1,1) must return the first field without quotes");
  equal<std::string>("Field,2", csvFile.at(1,2), "at(1,2) must return the second field without quotes");
  equal<std::string>("Field,3", csvFile.at(1,3), "at(1,3) must return the third field without quotes");
  equal<std::string>("  Field  4  ", csvFile.at(1,4), "at(1,4) must return the fourth field without quotes, preserving whitespace");

  data = std::stringstream{R":( "Header1"
  "Field1"):"};
  csvFile = CsvFile{data};

  equal(-1, csvFile.numberOfRows(), "numberOfRows() must indicate load failure for whitespace outside double quotes (before quote)");
  equal(-1, csvFile.numberOfColumns(), "numberOfColumns() must indicate load failure for whitespace outside double quotes (before quote)");

  data = std::stringstream{R":("Header1"  ,Header2
"Field1"  ,Field2):"};
  csvFile = CsvFile{data};

  equal(-1, csvFile.numberOfRows(), "numberOfRows() must indicate load failure for whitespace outside double quotes (after quote)");
  equal(-1, csvFile.numberOfColumns(), "numberOfColumns() must indicate load failure for whitespace outside double quotes (after quote)");

  return passFailText();
}

std::string Testing::testDoubleQuotedFieldsMixedWithUnquoted()
{
  std::stringstream data{R":("Header,1",Header2,"Header,3",Header4
"Field,1",Field2,"Field,3",Field4):"};
  CsvFile csvFile{data};

  equal(1, csvFile.numberOfRows(), "numberOfRows() must indicate 1, as the header + 1 row is present (mixed test)");
  equal(4, csvFile.numberOfColumns(), "numberOfColumns() must indicate 4 columns for the three fields (mixed test)");

  equal<std::string>("Header,1", csvFile.headerAt(1), "headerAt(1) must return the first header without quotes (mixed test)");
  equal<std::string>("Header2", csvFile.headerAt(2), "headerAt(2) must return the second header without quotes (mixed test)");
  equal<std::string>("Header,3", csvFile.headerAt(3), "headerAt(3) must return the third header without quotes (mixed test)");
  equal<std::string>("Header4", csvFile.headerAt(4), "headerAt(4) must return the fourth header without quotes (mixed test)");

  equal<std::string>("Field,1", csvFile.at(1,1), "at(1,1) must return the first field without quotes (mixed test)");
  equal<std::string>("Field2", csvFile.at(1,2), "at(1,2) must return the second field without quotes (mixed test)");
  equal<std::string>("Field,3", csvFile.at(1,3), "at(1,3) must return the third field without quotes (mixed test)");
  equal<std::string>("Field4", csvFile.at(1,4), "at(1,4) must return the fourth field without quotes (mixed test)");

  return passFailText();
}

std::string Testing::testReplacementOfBlackslashNInQuotedFieldsWithNewline()
{
  std::stringstream data{R":("Header\n1","He\nader\n2",Header\n3
"Field\n1","Fi\neld\n2",Field\n3):"};
  CsvFile csvFile{data};

  equal<std::string>("Header\n1", csvFile.headerAt(1), "headerAt(1) must return the first header with '\\n' replaced with newline");
  equal<std::string>("He\nader\n2", csvFile.headerAt(2), "headerAt(2) must return the second header with '\\n' replaced with newline");
  equal<std::string>("Header\\n3", csvFile.headerAt(3), "headerAt(3) must return the thord header WITHOUT '\\n' replaced with newline, since it is unquoted");

  equal<std::string>("Field\n1", csvFile.at(1,1), "at(1,1) must return the first field with '\\n' replaced with newline");
  equal<std::string>("Fi\neld\n2", csvFile.at(1,2), "at(1,2) must return the second field with '\\n' replaced with newline");
  equal<std::string>("Field\\n3", csvFile.at(1,3), "at(1,3) must return the third field WITHOUT '\\n' replaced with newline, since it is unquoted");

  return passFailText();
}

std::string Testing::testDoubleQuotesWithinFields()
{
  std::stringstream data{R":("Header""1"
"Field""1"):"};
  CsvFile csvFile{data};

  equal(1, csvFile.numberOfRows(), "numberOfRows() must indicate 1, as the header + 1 row is present (double quote test)");
  equal(1, csvFile.numberOfColumns(), "numberOfColumns() must indicate 4 columns for the three fields (double quote test)");

  equal<std::string>("Header\"1", csvFile.headerAt(1), "headerAt(1) must return the first header with internal quotes maintained, no outer quotes");
  equal<std::string>("Field\"1", csvFile.at(1,1), "at(1,1) must return the first field with internal quotes maintained, no outer quotes");

  data = std::stringstream{R":("Header"",""1"
"Field"",""1"):"};
  csvFile = CsvFile{data};

  equal(1, csvFile.numberOfRows(), "numberOfRows() must indicate 1, as the header + 1 row is present (double quote test with comma)");
  equal(1, csvFile.numberOfColumns(), "numberOfColumns() must indicate 4 columns for the three fields (double quote test with comma)");

  equal<std::string>("Header\",\"1", csvFile.headerAt(1), "headerAt(1) must return the first header with internal quotes maintained, no outer quotes, and internal commas preserved");
  equal<std::string>("Field\",\"1", csvFile.at(1,1), "at(1,1) must return the first field with internal quotes maintained, no outer quotes, and internal commas preserved");

  return passFailText();
}

std::string Testing::testReadingCsvDataFromFile()
{
  std::ifstream dataFile{"creature_types_sample.csv"};
  CsvFile csvFile{dataFile};
  dataFile.close(); // Ensure you close the file stream after loading the data

  equal(3, csvFile.numberOfRows(), "numberOfRows() the example file contains three rows");
  equal(8, csvFile.numberOfColumns(), "numberOfColumns() the example file contains 8 columns");

  equal<std::string>("Maximum Health", csvFile.headerAt(1), "First column of creature file must be Maximum Health");
  equal<std::string>("Name", csvFile.headerAt(2), "Second column of creature file must be Name");
  equal<std::string>("Description", csvFile.headerAt(3), "Third column of creature file must be Description");
  equal<std::string>("Strength", csvFile.headerAt(4), "Fourth column of creature file must be Strength");
  equal<std::string>("Dexterity", csvFile.headerAt(5), "Fifth column of creature file must be Dexterity");
  equal<std::string>("Wisdom", csvFile.headerAt(6), "Sixth column of creature file must be Wisdom");
  equal<std::string>("Weapon", csvFile.headerAt(7), "Seventh column of creature file must be Weapon");
  equal<std::string>("Dungeon Type", csvFile.headerAt(8), "Eighth column of creature file must be Dungeon Type");

  equal<std::string>("20", csvFile.at(1,1), "First creature must have 20 Maximum Health");
  equal<std::string>("Goblin", csvFile.at(1,2), "First creature must be named Goblin");
  equal<std::string>("a small nimble creature who favours the short sword", csvFile.at(1,3), "First creature has the wrong Description");
  equal<std::string>("2", csvFile.at(1,4), "First creature must have 2 Strength");
  equal<std::string>("4", csvFile.at(1,5), "First creature must have 4 Dexterity");
  equal<std::string>("1", csvFile.at(1,6), "First creature must have 1 Wisdom");
  equal<std::string>("ShortSword", csvFile.at(1,7), "First creature must have a ShortSword Weopn");
  equal<std::string>("All", csvFile.at(1,8), "First creature must have be for All Dungeon Type");

  equal<std::string>("30", csvFile.at(2,1), "Second creature must have 20 Maximum Health");
  equal<std::string>("Werewolf", csvFile.at(2,2), "Second creature must be named Werewolf");
  equal<std::string>("glowing red eyes peer our from behind a long nose and sharp teeth", csvFile.at(2,3), "Second creature has the wrong Description");
  equal<std::string>("5", csvFile.at(2,4), "Second creature must have 5 Strength");
  equal<std::string>("2", csvFile.at(2,5), "Second creature must have 2 Dexterity");
  equal<std::string>("1", csvFile.at(2,6), "Second creature must have 1 Wisdom");
  equal<std::string>("Fists", csvFile.at(2,7), "Second creature must have a Fists Weapon");
  equal<std::string>("BasicDungeon", csvFile.at(2,8), "Second creature must have be for Basic Dungeon Type");

  equal<std::string>("20", csvFile.at(3,1), "Third creature must have 20 Maximum Health");
  equal<std::string>("Evil Wizard", csvFile.at(3,2), "Third creature must be named Evil Wizard");
  equal<std::string>("cackling over an old tome, this wizard seems insanely evil;\n or maybe just insane? it is hard to tell", csvFile.at(3,3), "Third creature has the wrong Description");
  equal<std::string>("1", csvFile.at(3,4), "Third creature must have 1 Strength");
  equal<std::string>("2", csvFile.at(3,5), "Third creature must have 2 Dexterity");
  equal<std::string>("5", csvFile.at(3,6), "Third creature must have 5 Wisdom");
  equal<std::string>("WizardsStaff", csvFile.at(3,7), "Third creature must have a WizardsStaff");
  equal<std::string>("MagicalDungeon", csvFile.at(3,8), "Third creature must have be for Magical Dungeon Type");

  return passFailText();
}
