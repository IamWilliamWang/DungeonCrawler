#include "menuinterface.h"
#include "game.h"
#include <string>
#include <algorithm>

using namespace core;

MenuInterface::MenuInterface(std::ostream &display, std::istream &input)
  : _display{display}, _input{input}, _currentMenu{Menu::Main} {
}

void MenuInterface::displayWelcome(const std::string &author, const std::string &title) const {
  std::string welcomeText{"Welcome to " + title};
  std::string authorText{"Developed by " + author};
  std::string comp3023{"COMP 3023 Software Development with C++"};

  unsigned int columns{static_cast<unsigned>(std::max(welcomeText.size(), std::max(authorText.size(), comp3023.size())))};

  _display << centre(columns, welcomeText.size()) << welcomeText << std::endl
           << centre(columns, authorText.size()) << authorText << std::endl
           << centre(columns, comp3023.size()) << comp3023 << std::endl;
}

void MenuInterface::run() {
  displayMenu();
  while (processSelection(getCharacterInput()) && _input) {
    displayMenu();
  }
}

void MenuInterface::displayMenu() const {
   waitUntillNewline();

  switch (_currentMenu) {
  case Menu::Main:
    displayMainMenu();
    break;
  case Menu::CharacterDetails:
    characterDetailsMenu();
    break;
  case Menu::DungeonSelect:
    dungeonTypeMenu();
    break;
  case Menu::Action:
    actionMenu();
    break;
  case Menu::Combat:
    combatMenu();
    break;
  }
}

bool MenuInterface::processSelection(char selection) {
  if (!_input) return false; // graceful exit when input ends

  switch (_currentMenu) {
  case Menu::Main:
    return processMainMenu(tolower(selection));
  case Menu::CharacterDetails:
    processCharacterDetails(tolower(selection));
    break;
  case Menu::DungeonSelect:
    processDungeonType(tolower(selection));
    break;
  case Menu::Action:
    processAction(tolower(selection));
    break;
  case Menu::Combat:
    processCombatAction(tolower(selection));
  }

  return true;
}

char MenuInterface::getCharacterInput() const {
  char input;
  _input >> input;
  _input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  echo(input); // for when running the input script
  return input;
}

int MenuInterface::getIntInput() const {
  int input;
  _input >> input;
  _input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  while (!_input) {
    _input.clear();
    warnSelectionInvalid(char(_input.peek()));
    _input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    _input >> input;
    _input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  echo(input); // for when running the input script

  return input;
}

void MenuInterface::warnSelectionInvalid(char selection) const {
  _display << "Sorry, \'" << selection << "\' is not a valid option, please try again."
           << std::endl;
}

void MenuInterface::setMenu(Menu newMenu) {
  _currentMenu = newMenu;
}

void MenuInterface::displayMainMenu() const {
  _display << "What would you like to do?" << std::endl;
  _display << " (p)lay the game" << std::endl;
  _display << " (c)haracter details" << std::endl;
  _display << " (q)uit" << std::endl;
}

bool MenuInterface::processMainMenu(char selection) {
  switch (selection) {
  case 'p':
    playGame();
    break;
  case 'c':
    switchToCharacterMenu();
    break;
  case 'q':
    return quitGame();
  default:
    warnSelectionInvalid(selection);
  }
  return true;
}

void MenuInterface::playGame() {
	createCharacter();

}

void MenuInterface::createCharacter() {
	_display << "You need to create a character... what is your name?" << std::endl;
	std::string name;
	std::getline(_input, name);
	_display << std::endl;
	int restPoints = 6, strength = 0, dexterity = 0, wisdom = 0;
	_display << "Welcome " << name << ", you have *" << restPoints << "* stat points to allocate." << std::endl;
	while (true)
	{
		_display << "A high Strength stat will boost your damage in combat." << std::endl;
		_display << "How many points do you want to add to your Strength (cannot exceed 5)?" << std::endl;
		int strength_tmp = getIntInput();
		strength += strength_tmp;
		restPoints -= strength_tmp;
		if (restPoints <= 0)
			break;
		_display << std::endl;
		_display << "You have *" << restPoints << "* stat points remaining." << std::endl;
		_display << "A high Dexterity stat will increase your ability to dodge creature attacks." << std::endl;
		_display << "How many points do you want to add to your Dexterity (cannot exceed 5)?" << std::endl;
		int dexterity_tmp = getIntInput();
		dexterity += dexterity_tmp;
		restPoints -= dexterity_tmp;
		_display << std::endl;
		if (restPoints <= 0)
			break;
		_display << "You have *" << restPoints << "* stat points remaining." << std::endl;
		_display << "A high Wisdom stat will boost the effectiveness of magical items." << std::endl;
		_display << "How many points do you want to add to your Wisdom (cannot exceed 5)?" << std::endl;
		int wisdom_tmp = getIntInput();
		wisdom += wisdom_tmp;
		restPoints -= wisdom_tmp;
		_display << std::endl;
		if (restPoints <= 0)
			break;
		_display << "You have *" << restPoints << "* stat points remaining." << std::endl;
		_display << "Are you sure you do not want to allocate the remaining points? (y/n)" << std::endl;
		char choice = getCharacterInput();
		if (choice == 'n')
		{
			_display << std::endl;
			_display << "You have *" << restPoints << "* stat points remaining." << std::endl;
			continue;
		}
		break;
	}
	std::shared_ptr<Character> myCharacter = std::make_shared<Character>(name);
	myCharacter->setAttribute(strength, dexterity, wisdom);
    Game::instance()->setPlayer(myCharacter);
	switchToCharacterMenu();
}

void MenuInterface::dungeonTypeMenu() const {
  // TODO: implement this member function.
  _display << "TODO: any key will return to main menu" << std::endl;
}

void MenuInterface::processDungeonType(char selection) {
  // TODO: implement this member function.
  setMenu(Menu::Main);
}

void MenuInterface::switchToCharacterMenu() {
  // TODO: implement this member function
  setMenu(Menu::CharacterDetails);
}

bool MenuInterface::quitGame() const {
  // TODO: complete implementation

  return !confirm("Are you sure you want to quit?");
}

void MenuInterface::characterDetailsMenu() const {
  // TODO: implement this member function.
  _display << "TODO: any key will return to main menu" << std::endl;
}

void MenuInterface::processCharacterDetails(char selection) {
  // TODO: implement this member function.
  setMenu(Menu::Main);
}

void MenuInterface::displayWeaponDetails() {
  // TODO: implement this member function
}

void MenuInterface::actionMenu() const {
  // TODO: implement this member function.
  _display << "TODO: any key will return to main menu" << std::endl;
}

void MenuInterface::processAction(char selection) {
  // TODO: implement this member function.
  setMenu(Menu::Main);
}

void MenuInterface::combatMenu() const {
  // TODO: implement this member function.
  _display << "TODO: any key will return to main menu" << std::endl;
}

void MenuInterface::processCombatAction(char selection) {
  // TODO: implement this member function.
  setMenu(Menu::Main);
}

void MenuInterface::doNavigate() {
  // TODO: implement this member function
}

void MenuInterface::pickupWeapon() {
  // TODO: implement this member function
}

void MenuInterface::compareWeapons() {
  // TODO: implement this member function
}

void MenuInterface::doAttack() {
  // TODO: implement this member function
}

void MenuInterface::useSpecialAbility() {
  // TODO: implement this member function
}

void MenuInterface::leaveDungeon() {
  // TODO: implement this member function
}

bool MenuInterface::confirm(const std::string &confirmationPrompt) const {
  // TODO: implement this member function.
  // Do not forget to validate the user's confirmation selection
  return true;
}
