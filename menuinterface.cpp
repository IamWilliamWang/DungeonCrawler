#include "menuinterface.h"
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
    if (!_input) {
        return false; // graceful exit when input ends
    }
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
	if (Game::instance()->getSuccessTimes() == 0) {
        if (createCharacter()) {
			setMenu(Menu::DungeonSelect);
        }
	} else {
        if (Game::instance()->createDungeon() && Game::instance()->enterDungeon()) {
			setMenu(Menu::Action);
        }
	}
}

bool MenuInterface::createCharacter() {
	_display << std::endl << "You need to create a character... what is your name?" << std::endl;
	std::string name;
	std::getline(_input, name);
	_display << std::endl;
	int restPoints = 6, strength = 0, dexterity = 0, wisdom = 0;
	_display << "Welcome " << name << ", you have *" << restPoints << "* stat points to allocate." << std::endl;
	while (true) {
		_display << "A high Strength stat will boost your damage in combat." << std::endl;
		_display << "How many points do you want to add to your Strength (cannot exceed 5)?" << std::endl;
		int strength_tmp;
		while (!getVaildInt(strength_tmp, 1, restPoints)); // Loop through when the input is incorrect
		strength += strength_tmp;
		restPoints -= strength_tmp;
		if (restPoints <= 0) {
			_display << "Create player failed! You don't have enough points." << std::endl;
			setMenu(Menu::Main);
			return false;
		}
		_display << std::endl;
		_display << "You have *" << restPoints << "* stat points remaining." << std::endl;
		_display << "A high Dexterity stat will increase your ability to dodge creature attacks." << std::endl;
		_display << "How many points do you want to add to your Dexterity (cannot exceed 5)?" << std::endl;
		int dexterity_tmp;
		while (!getVaildInt(dexterity_tmp, 1, restPoints)); // Loop through when the input is incorrect
		dexterity += dexterity_tmp;
		restPoints -= dexterity_tmp;
		_display << std::endl;
		if (restPoints <= 0) {
			_display << "Create player failed! You don't have enough points." << std::endl;
			setMenu(Menu::Main);
			return false;
		}
		_display << "You have *" << restPoints << "* stat points remaining." << std::endl;
		_display << "A high Wisdom stat will boost the effectiveness of magical items." << std::endl;
		_display << "How many points do you want to add to your Wisdom (cannot exceed 5)?" << std::endl;
		int wisdom_tmp;
		while (!getVaildInt(wisdom_tmp, 1, restPoints)); // Loop through when the input is incorrect
		wisdom += wisdom_tmp;
		restPoints -= wisdom_tmp;
        if (restPoints == 0) {
			break;
        } else if (restPoints < 0) {
            _display << "Create player failed! You don't have enough points." << std::endl;
            setMenu(Menu::Main);
            return false;
        }
		_display << "You have *" << restPoints << "* stat points remaining." << std::endl;
		_display << "Are you sure you do not want to allocate the remaining points? (y/n)" << std::endl;
		char choice = getCharacterInput();
		if (choice == 'n') {
			_display << std::endl;
			_display << "You have *" << restPoints << "* stat points remaining." << std::endl;
			continue;
		}
		break;
	}
	std::shared_ptr<Character> myCharacter = std::shared_ptr<Character>(new Character(name));
    if (!myCharacter->setAttribute(strength + 1, dexterity + 1, wisdom + 1)) {
		_display << "Create player failed!" << std::endl;
    }
	Game::instance()->setPlayer(myCharacter);
	switchToCharacterMenu(_currentMenu);
	return true;
}

void MenuInterface::dungeonTypeMenu() const {
	_display << "While roaming the country side you encounter a strange fork in the road." << std::endl;
	_display << "To the left lies a dark cave, the foul stench of rotting flesh emanates from it." << std::endl;
	_display << "To the right is a mysterious tower, a strange magical energy lights the path." << std::endl;
	_display << "What would you like to do?" << std::endl;
	_display << " Go left: create a (b)asic dungeon" << std::endl;
	_display << " Go right: create a (m)agical dungeon" << std::endl;
	_display << " (r)eturn the way you came: back to main menu" << std::endl;
}

void MenuInterface::processDungeonType(char selection) {
    if (_currentMenu != Menu::DungeonSelect) {
		return;
    }

	selection = tolower(selection);
	bool createSuccess = false;
    if (selection == 'b') {
		createSuccess = Game::instance()->createDungeon("BasicDungeon");
    }
    else if (selection == 'm') {
		createSuccess = Game::instance()->createDungeon("MagicalDungeon");
    }
	else if (selection == 'r') {
		setMenu(Menu::Main);
		return;
    } else {
		warnSelectionInvalid(selection);
    }

	if (createSuccess == false) {
		_display << "Warning: create dungeon failed!" << std::endl;
		setMenu(Menu::Main);
		return;
	}
	Game::instance()->enterDungeon();
	_display << std::endl;
    if (isBasicDungeon()) {
		_display << "You enter a dark cave." << std::endl;
    }
    else if (isMagicalDungeon()) {
		_display << "You pass through a glowing doorway..." << std::endl;
    }
	setMenu(Menu::Action);
}

void MenuInterface::switchToCharacterMenu(Menu retMenuStatus) {
	setMenu(Menu::CharacterDetails);
	processCharacterDetails('c');
	setMenu(retMenuStatus);
}

bool MenuInterface::quitGame() const {
	auto exit = confirm("Are you sure you want to quit?");
    if (exit == false) {
		Game::instance()->exitDungeon();
    }
	return !exit;
}

void MenuInterface::characterDetailsMenu() const {}

void MenuInterface::processCharacterDetails(char selection) {
    if (_currentMenu != Menu::CharacterDetails || selection != 'c') {
		return;
    }

	selection = tolower(selection);

	auto character = Game::instance()->player();
    if (character == nullptr) {
		_display << "There is currently no character to display." << std::endl;
    }
	else {
		_display << std::endl;
		_display << "***Character Summary***" << std::endl;
		_display << *character;
	}
}

void MenuInterface::displayWeaponDetails(std::string title, std::shared_ptr<weapons::Weapon> weapon) {
	_display << std::endl;
    if (title != "") {
		_display << title << std::endl;
    }
	_display << *weapon;
}

void MenuInterface::displayChamber() const {
	_display << "Looking around you see... ";
	std::shared_ptr<dungeon::Room> currRoom;
	if (isBasicDungeon()) {
		currRoom = Game::instance()->getBasicDungeon()->getNowRoom();
        if (currRoom->id() % 2 == 0) {
			_display << "a chamber that glitters like a thousand stars in the torchlight" << std::endl;
        } else {
			_display << "a dark and empty chamber" << std::endl;
        }
	} else {
        if (currRoom->id() % 2 == 0) {
			_display << "your ears are filled with the sounds of numerous elixirs bubbling away over open flames" << std::endl;
        } else {
			_display << "the smell of musty pages and the tingle of magic fills the air" << std::endl;
        }
	}
}

void MenuInterface::actionMenu() const {
	std::shared_ptr<dungeon::Room> currRoom;
    if (isBasicDungeon()) {
		currRoom = Game::instance()->getBasicDungeon()->getNowRoom();
    } else if (isMagicalDungeon()) {
		currRoom = Game::instance()->getMagicalDungeon()->getNowRoom();
    }

	displayChamber();
	// initialize output lines.
	std::vector<std::string> outputs(4);
	// output entrance and exit
	if (currRoom->existEntranceOrExit()) {
		char entranceDirection = currRoom->getEntranceDirection();
		char exitDirection = currRoom->getExitDirection();
		if (entranceDirection != '\0') {
			switch (entranceDirection) {
			case 'N':
				outputs[0] = ("To the NORTH you see the entrance by which you came in.");
				break;
			case 'S':
				outputs[1] = ("To the SOUTH you see the entrance by which you came in.");
				break;
			case 'W':
				outputs[2] = ("To the WEST you see the entrance by which you came in.");
				break;
			case 'E':
				outputs[3] = ("To the EAST you see the entrance by which you came in.");
				break;
			default:
				_display << "extrance direction invaild!" << std::endl;
                break;
			}
		} else if (exitDirection != '\0') {
			switch (exitDirection) {
			case 'N':
				outputs[0] = ("To the NORTH you see a stairway to a another level.");
				break;
			case 'S':
				outputs[1] = ("To the SOUTH you see a stairway to a another level.");
				break;
			case 'W':
				outputs[2] = ("To the WEST you see a stairway to a another level.");
				break;
			case 'E':
				outputs[3] = ("To the EAST you see a stairway to a another level.");
				break;
			default:
				_display << "exit direction invaild!" << std::endl;
			}
		} else _display << "Unsuspected error occurred!" << std::endl;
	}
	// output doors
	std::list<char> doorDirections;
    if (isBasicDungeon()) {
		doorDirections = Game::instance()->getBasicDungeon()->getNowRoom()->getDoorDirections();
    } else {
		doorDirections = Game::instance()->getMagicalDungeon()->getNowRoom()->getDoorDirections();
    }
	for (auto direction : doorDirections) {
		switch (direction) {
		case 'N':
			outputs[0] = "To the NORTH you see an opening to another chamber";
			break;
		case 'S':
			outputs[1] = "To the SOUTH you see an opening to another chamber";
			break;
		case 'W':
			outputs[2] = "To the WEST you see an opening to another chamber";
			break;
		case 'E':
			outputs[3] = "To the EAST you see an opening to another chamber";
			break;
		default:
			break;
		}
	}
	// write down into screen
    for (int i = 0; i < 4; ++i) {
        if (outputs[static_cast<unsigned>(i)] != "") {
			_display << outputs[static_cast<unsigned>(i)] << std::endl;
        }
	}
	_display << "What would you like to do?" << std::endl;
	_display << " Go (n)orth" << std::endl;
	_display << " Go (e)ast" << std::endl;
	_display << " Go (s)outh" << std::endl;
	_display << " Go (w)est" << std::endl;
	_display << " Go (b)ack the way you came" << std::endl;
	if (!currRoom->getCreature() && currRoom->getWeapon()) {
		_display << " (p)ick-up item." << std::endl;
		_display << " c(o)mpare items." << std::endl;
	}
	_display << " use specia(l) ability" << std::endl;
	_display << " View your (c)haracter stats" << std::endl;
	_display << " Return to the main (m)enu" << std::endl;
}

void MenuInterface::processAction(char selection) {
    if (_currentMenu != Menu::Action) {
		return;
    }

	selection = tolower(selection);
	// get selection
	std::shared_ptr<dungeon::Room> currRoom;
    if (isBasicDungeon()) {
		currRoom = Game::instance()->getBasicDungeon()->getNowRoom();
    } else {
		currRoom = Game::instance()->getMagicalDungeon()->getNowRoom();
    }
    if (selection == 'n') {
		_display << "Heading North..." << std::endl;
    } else if (selection == 's') {
		_display << "Heading South..." << std::endl;
    } else if (selection == 'w') {
		_display << "Heading West..." << std::endl;
    } else if (selection == 'e') {
		_display << "Heading East..." << std::endl;
    } else if (selection == 'b') {
		doNavigateBack();
		return;
	} else if (selection == 'p') {
		pickupWeapon();
		return;
	} else if (selection == 'o') {
		compareWeapons();
		return;
	} else if (selection == 'l') {
		useSpecialAbility();
		return;
	} else if (selection == 'c') {
		switchToCharacterMenu(_currentMenu);
		_display << std::endl;
		_display << "What would you like to do?" << std::endl;
		_display << " View (w)eapon info." << std::endl;
		_display << " Return to the previous (m)enu" << std::endl;
		auto selection = getCharacterInput();
		if (selection == 'w') {
			displayWeaponDetails("***Weapon Summary***");
			return;
		} else if (selection == 'm')
			return;
        else {
			_display << "Sorry, '" << selection << "' is not a valid option, please try again." << std::endl;
        }
	} else if (selection == 'm') {
		leaveDungeon();
		return;
    } else {
		warnSelectionInvalid(selection);
    }

	// walk into wall is not allowed
	currRoom->checkDirectionVaild(selection);
	if (currRoom->existEntranceOrExit()) {
		if (currRoom->getEntranceDirection() == selection) {
			Game::instance()->exitDungeon();
            _display << "After exploring *" << Game::instance()->getSuccessTimes()
                     << "* levels, you run out of the cave as quickly as your legs can carry you." << std::endl;
			_display << "As you emerge from the darkness you are startled by the bright light and pause while your eyes adjust." << std::endl;
			setMenu(Menu::Main);
			return;
		} else if (currRoom->getExitDirection() == selection) {
			Game::instance()->exitLevel();
			_display << "You take the stairs, what awaits you do not know..." << std::endl;
			setMenu(Menu::Main);
			return;
		}
	}
    if (currRoom->getDoor(selection) == nullptr) {
		_display << "out of the darkness looms a jagged formation of rock: you cannot go that way" << std::endl;
    }
	else {
		// navigation
		doNavigate(selection);
		_display << "You pass through the doorway..." << std::endl;
	}
	// if player will combat in the next room, switch Menu
	if (isBasicDungeon()) {
        if (Game::instance()->getBasicDungeon()->getNowRoom()->getCreature() != nullptr) {
			setMenu(Menu::Combat);
        }
	} else {
        if (Game::instance()->getMagicalDungeon()->getNowRoom()->getCreature() != nullptr) {
			setMenu(Menu::Combat);
        }
	}
}

void MenuInterface::combatMenu() const {
	auto currRoom = Game::instance()->currentRoom();
	auto currCreature = currRoom->getCreature();
	displayChamber();
    _display << "Blocking your path stands a " << currCreature->name() << ": "
             << currCreature->getDescription() << std::endl;
	_display << std::endl;
	_display << "What would you like to do?" << std::endl;
	_display << " Go (b)ack the way you came" << std::endl;
	_display << " (a)ttack with your weapon" << std::endl;
	_display << " use specia(l) ability" << std::endl;
	_display << " View your (c)haracter stats" << std::endl;
	_display << " Return to the main (m)enu" << std::endl;
}

void MenuInterface::processCombatAction(char selection) {
    if (_currentMenu != Menu::Combat) {
		return;
    }

	selection = tolower(selection);
	if (selection == 'b') {
		doNavigateBack();
		return;
	} else if (selection == 'a') {
		doAttack();
		return;
	} else if (selection == 'l') {
		useSpecialAbility();
		return;
	} else if (selection == 'c') {
		switchToCharacterMenu(_currentMenu);
		_display << std::endl;
		_display << "What would you like to do?" << std::endl;
		_display << " View (w)eapon info." << std::endl;
		_display << " Return to the previous (m)enu" << std::endl;
		auto selection = getCharacterInput();
		if (selection == 'w') {
			displayWeaponDetails("***Weapon Summary***");
			return;
        } else if (selection == 'm') {
			return;
        }
        else {
			_display << "Sorry, '" << selection << "' is not a valid option, please try again." << std::endl;
        }
	} else if (selection == 'm') {
		leaveDungeon();
		return;
    } else {
		warnSelectionInvalid(selection);
    }

}

void MenuInterface::doNavigate(char navigateDirection) {
	Game::instance()->navigate(navigateDirection);
}

void MenuInterface::doNavigateBack() {
	if (!Game::instance()->navigateBack()) {
		_display << "NavigateBack failed!" << std::endl;
		return;
	}
    if (isBasicDungeon()) {
		setMenu(Game::instance()->getBasicDungeon()->getNowRoom()->getCreature() ? Menu::Combat : Menu::Action);
    } else {
		setMenu(Game::instance()->getMagicalDungeon()->getNowRoom()->getCreature() ? Menu::Combat : Menu::Action);
    }
	_display << "You head back the way you came..." << std::endl;
	_display << "You pass through the doorway..." << std::endl;
}

void MenuInterface::pickupWeapon() {
	std::shared_ptr<dungeon::Room> currRoom;
    if (isBasicDungeon()) {
		currRoom = Game::instance()->getBasicDungeon()->getNowRoom();
    } else {
		currRoom = Game::instance()->getMagicalDungeon()->getNowRoom();
    }
	_display << "This action will drop your current item. Are you sure? (y/n)" << std::endl;
	char selection = tolower(getCharacterInput());
	if (selection == 'y') {
		auto newWeapon = currRoom->getWeapon();
		auto prefixEnchantment = newWeapon->getPrefixEnchantment();
		auto suffixEnchantment = newWeapon->getSuffixEnchantment();
		_display << "You picked up a ";
		_display << newWeapon->getFullName() << std::endl;
		Game::instance()->player()->setWeapon(newWeapon);
		currRoom->setWeapon(nullptr);
	}
}

void MenuInterface::compareWeapons() {
	std::shared_ptr<dungeon::Room> currRoom;
    if (isBasicDungeon()) {
		currRoom = Game::instance()->getBasicDungeon()->getNowRoom();
    } else {
		currRoom = Game::instance()->getMagicalDungeon()->getNowRoom();
    }
	displayWeaponDetails("***Weapon Comparison***\n--Room", currRoom->getWeapon());
	_display << std::endl;
	displayWeaponDetails("--Equipped");
	_display << std::endl;
}

void MenuInterface::doAttack() {
	auto player = Game::instance()->player();
	auto myPrefixEnchantment = player->getWeapon()->getPrefixEnchantment();
	auto mySuffixEnchantment = player->getWeapon()->getSuffixEnchantment();
	std::shared_ptr<creatures::Creature> enemy;
    if (isBasicDungeon()) {
		enemy = Game::instance()->getBasicDungeon()->getNowRoom()->getCreature();
    } else {
		enemy = Game::instance()->getMagicalDungeon()->getNowRoom()->getCreature();
    }
	auto enemyPrefixEnchantment = enemy->getWeapon()->getPrefixEnchantment();
	auto enemySuffixEnchantment = enemy->getWeapon()->getSuffixEnchantment();

	// Execute each attack and get damage points
	int* damagesHappened = static_cast<int*>(Game::instance()->doActionRound('a'));
	// Display battle results section
	_display << std::endl;
	// Player start to attack
	_display << "You attack the creature..." << std::endl;
	_display << (damagesHappened[0] < 15 ? "*jab* *jab* *cross*" : "*hu, ahhhhhhhh, smash*"); // Fighting description
    if (player->getWeapon()->getName() == "Wizard's Staff") {
		_display << " (the staff seems ineffective)";
    }
	_display << std::endl;
    if (damagesHappened[0] != 0) { // Show dodge or not
		_display << "The attack deals *" << damagesHappened[0] << "* damage..." << std::endl;
    } else {
		_display << "Creature dodged the attack" << std::endl;
    }
	// Unreasonable weapon tips
	if (!isMagicalDungeon() && (player->getWeapon()->getName() == "Wizard's Staff"
                                || player->getWeapon()->getName() == "Magic Wand")) {
		_display << "Warning: you are in a basic dungeon, but you are holding a magical dungeon weapon" << std::endl;
    }
	// Player attack when prefix enchant display
	if (damagesHappened[0] != 0 && myPrefixEnchantment) {
        if (myPrefixEnchantment->instanceOf("FlameEnchantment")) {
			_display << "The target bursts into flames taking an extra 5 damage" << std::endl;
        } else if (myPrefixEnchantment->instanceOf("ElectricityEnchantment")) {
			_display << "As the weapon connects, a bolt of lightning strikes the target dealing 5 damage" << std::endl;
        }
	}
	// Enchant enemy suffix when player attack
	if (damagesHappened[0] != 0 && enemySuffixEnchantment) {
        if (enemySuffixEnchantment->instanceOf("VampirismEnchantment")) {
            _display << "A feeling of warmth flows through creature and it heals "
                     << damagesHappened[0] / 2 << " health" << std::endl;
        }
	}
	_display << std::endl;
	// Check enemy death
	if (!enemy->isAlive()) {
		_display << std::endl;
		_display << "You win the Fight!" << std::endl;
		_display << "Digging through the remains of the creature you find something interesting." << std::endl;
		std::shared_ptr<dungeon::Room> room;
        if (isBasicDungeon()) {
			room = Game::instance()->getBasicDungeon()->getNowRoom();
        } else {
			room = Game::instance()->getMagicalDungeon()->getNowRoom();
        }
		room->setWeapon(room->getCreature()->getWeapon());
		room->setCreature(nullptr);
		setMenu(Menu::Action);
		return;
	}
	// Enemy attack
	_display << "The creature attacks... ";
	_display << (damagesHappened[1] < 15 ? "*jab* *jab* *cross*" : "*hu, ahhhhhhhh, smash*"); // Fighting description
    if (enemy->getWeapon()->getName() == "Wizard's Staff") {
		_display << " (the staff seems ineffective)";
    }
	_display << std::endl;
    if (damagesHappened[1] != 0) { // Show dodge or not
		_display << "The attack deals *" << damagesHappened[1] << "* damage..." << std::endl;
    } else {
		_display << Game::instance()->player()->name() << " dodged the attack" << std::endl;
    }
	// Prefix enchant when enemy attacks
	if (damagesHappened[1] != 0 && enemyPrefixEnchantment) {
        if (enemyPrefixEnchantment->instanceOf("FlameEnchantment")) {
			_display << "You burst into flames taking an extra 5 damage" << std::endl;
        } else if (enemyPrefixEnchantment->instanceOf("ElectricityEnchantment")) {
			_display << "As the weapon connects, a bolt of lightning strikes you dealing 5 damage" << std::endl;
        }
	}
	// Player's suffix enchant display when enemy attacks
	if (damagesHappened[1] != 0 && mySuffixEnchantment) {
        if (mySuffixEnchantment->instanceOf("VampirismEnchantment")) {
            _display << "A feeling of warmth flows through you and you heal "
                     << damagesHappened[1] / 2 << " health" << std::endl;
        }
	}
	// Check if player is dead
    if (!player->isAlive()) { // player died
		_display << std::endl;
		_display << "You died. Game Over Man!" << std::endl << std::endl;
		_display << "You died after exploring *" << Game::instance()->getSuccessTimes() << "* levels" << std::endl;
		setMenu(Menu::Main);
		leaveDungeon(false);
		return;
	}
}

void MenuInterface::useSpecialAbility() {
	auto player = Game::instance()->player();
	if (*static_cast<bool*>(Game::instance()->doActionRound('l'))) {
		if (player->getWeapon()->getSuffixEnchantment()) {
            if (player->getWeapon()->getSuffixEnchantment()->instanceOf("HealingEnchantment")) {
                _display << "An aura of light comes from within you. You are healed for 6 health points. Now your have "
                         << player->getHealthPoint() << "/" << player->getMaxHealthPoint() << " health points" << std::endl;
            }
		} else if (player->getWeapon()->getName() == "Wizard's Staff") {
			auto enemy = Game::instance()->getMagicalDungeon()->getNowRoom()->getCreature();
			if (enemy) {
				auto damage = Game::instance()->randomIntBetweenInc(10, 20);
				enemy->setHealthPoint(enemy->getHealthPoint() - damage);
                _display << "A large fireball flies out from the top of the staff, charring everything in its path and dealing "
                         << damage << " damage" << std::endl;
                if (!enemy->isAlive()) { // The enemy killed
					_display << std::endl;
					_display << "You win the Fight!" << std::endl;
					_display << "Digging through the remains of the creature you find something interesting." << std::endl;
					auto room = Game::instance()->getMagicalDungeon()->getNowRoom();
					room->setWeapon(room->getCreature()->getWeapon());
					room->setCreature(nullptr);
					setMenu(Menu::Action);
				}
			} else {
				_display << "A large fireball flies out from the top of the staff and explodes against the wall." << std::endl;
			}
		} else if (player->getWeapon()->getName() == "Magic Wand") {
			_display << "A bright light fills you entire being. As it subsides you feel fully restored." << std::endl;
		}
	} else {
		_display << "You hold your weapon high and shout..." << std::endl;
		_display << "Nothing happens..." << std::endl;
	}
}

void MenuInterface::leaveDungeon(bool displayFailureMessage) {
	Game::instance()->exitDungeon();
	if (displayFailureMessage) {
        _display << "After exploring *" << Game::instance()->getSuccessTimes()
                 << "* levels, you run out of the cave as quickly as your legs can carry you." << std::endl;
		_display << "As you emerge from the darkness you are startled by the bright light and pause while your eyes adjust." << std::endl;
	}
	setMenu(Menu::Main);
}

bool MenuInterface::confirm(const std::string &confirmationPrompt) const {
	_display << "You have successfully completed *" << Game::instance()->getSuccessTimes() << "* levels so far." << std::endl;
	_display << confirmationPrompt << " (y/n)" << std::endl;
	char selection = getCharacterInput();
	return selection == 'y';
}

char MenuInterface::tolower(const char ch) {
	char c = ch;
	if (c >= 'A' && c <= 'Z')
		c -= 'a' - 'A';
	return c;
}

bool MenuInterface::isBasicDungeon() const {
	return Game::instance()->getBasicDungeon() != nullptr;
}

bool MenuInterface::isMagicalDungeon() const {
	return Game::instance()->getMagicalDungeon() != nullptr;
}

bool MenuInterface::getVaildInt(int& value, int min, int max) {
	int tmpValue = getIntInput();
	if (tmpValue < min) {
		_display << "Warning: the number cannot be less than " << min << ", please input again." << std::endl;
		return false;
	}
	if (tmpValue > max) {
		_display << "Warning: the number cannot be more than " << max << ", please input again." << std::endl;
		return false;
	}
	value = tmpValue;
	return true;
}
