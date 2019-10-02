#include "game.h"
#include "testingsettings.h"
#include "dungeonbuilder.h"
#include <sstream>
using namespace core;

// TODO: Add additional implementation here
std::shared_ptr<Game> Game::_game = std::shared_ptr<Game>(new Game); // mustn't use std::make_shared

std::shared_ptr<Character> Game::player() {
	return _character;
}

void Game::setPlayer(std::shared_ptr<Character> character) {
	_character = character;
}

std::shared_ptr<dungeon::Dungeon> Game::dungeon() {
	return _dungeon;
}

std::shared_ptr<dungeon::BasicDungeon> Game::getBasicDungeon() {
	return std::dynamic_pointer_cast<dungeon::BasicDungeon>(_dungeon);
}

std::shared_ptr<dungeon::MagicalDungeon> Game::getMagicalDungeon() {
	return std::dynamic_pointer_cast<dungeon::MagicalDungeon>(_dungeon);
}

std::shared_ptr<dungeon::Room> Game::currentRoom() {
    if (getBasicDungeon()) {
		return getBasicDungeon()->getNowRoom();
    }
    else if (getMagicalDungeon()) {
		return getMagicalDungeon()->getNowRoom();
    }
	return nullptr;
}

bool Game::createDungeon(std::string dungeonType) {
	static std::string previousDungeonType = "";
    if (previousDungeonType != "") {
		dungeonType = previousDungeonType;
    }

	std::shared_ptr<dungeon::DungeonBuilder> builder;
	if (dungeonType == "BasicDungeon") {
		builder = std::make_shared<dungeon::BasicDungeonBuilder>();
		_dungeon = builder->buildDungeon();
		if (_dungeon != nullptr) {
			previousDungeonType = "BasicDungeon";
			return true;
		}
	} else if (dungeonType == "MagicalDungeon") {
		builder = std::make_shared<dungeon::MagicalDungeonBuilder>();
		_dungeon = builder->buildDungeon();
		if (_dungeon != nullptr) {
			previousDungeonType = "MagicalDungeon";
			return true;
		}
	}
	return false;
}

bool Game::enterDungeon() {
    if (_dungeon == nullptr) {
		return false;
    }
	if (getBasicDungeon()) {
		auto entranceRoom = getBasicDungeon()->getEntranceRoom();
        if (entranceRoom == nullptr) {
			return false;
        }
		getBasicDungeon()->setNowRoom(entranceRoom);
		return true;
	} else if (getMagicalDungeon()) {
		auto entranceRoom = getMagicalDungeon()->getEntranceRoom();
        if (entranceRoom == nullptr) {
			return false;
        }
		getMagicalDungeon()->setNowRoom(entranceRoom);
		return true;
	}
	return false;
}

bool Game::navigate(char direction) {
	if (getBasicDungeon()) {
		auto basicDungeon = getBasicDungeon();
		auto room = currentRoom();
		room->checkDirectionVaild(direction);
		auto door = room->getDoor(direction);
        if (door == nullptr) {
			return false;
        }
		basicDungeon->setNowRoom(door->getNeighbourRoom(room));
		return true;
	} else if (getMagicalDungeon()) {
		auto magicalDungeon = getMagicalDungeon();
		auto room = currentRoom();
		room->checkDirectionVaild(direction);
		auto door = room->getDoor(direction);
        if (door == nullptr) {
			return false;
        }
		magicalDungeon->setNowRoom(door->getNeighbourRoom(room));
		return true;
	}
	return false;
}

bool Game::navigateBack() {
	if (getBasicDungeon()) {
		auto basicDungeon = getBasicDungeon();
		basicDungeon->setNowRoom(basicDungeon->path(-2));
		return true;
	} else if (getMagicalDungeon()) {
		auto magicalDungeon = getMagicalDungeon();
		magicalDungeon->setNowRoom(magicalDungeon->path(-2));
		return true;
	}
	return true;
}

void Game::exitLevel() {
    ++_dungeonLevel;
}

void Game::exitDungeon() {
	setPlayer(nullptr);
	setDungeon(nullptr);
	_dungeonLevel = 1;
}

bool Game::canDodge(std::shared_ptr<creatures::Creature> creature) {
	return randomIntBetweenInc(0, 100) <= creature->dodgeChance();
}

void* Game::doActionRound(char selection) {
	// Attack module
	if (selection == 'a') {
		int* damagesHappened = new int[2]; // Store damage done by us and damage done by the enemy
		damagesHappened[0] = damagesHappened[1] = 0;

		auto player = _character;
		std::shared_ptr<creatures::Creature> enemy;
        if (getBasicDungeon()) {
			enemy = getBasicDungeon()->getNowRoom()->getCreature();
        } else {
			enemy = getMagicalDungeon()->getNowRoom()->getCreature();
        }
		// If the enemy cannot dodge
		if (!canDodge(enemy)) {
			int damage = player->damageWeaponed(); // Get enchantment damage
			enemy->setHealthPoint(enemy->getHealthPoint() - damage); // Enemy health reduced
			// If the enemy has VampirismEnchantment, treat him
            if (enemy->getWeapon()->getSuffixEnchantment()) { // Enchantment is not empty
				if (enemy->getWeapon()->getSuffixEnchantment()->instanceOf("VampirismEnchantment")) {
					auto vampirismEnchantment = std::dynamic_pointer_cast<weapons::VampirismEnchantment>(enemy->getWeapon()->getSuffixEnchantment());
					enemy->setHealthPoint(enemy->getHealthPoint() + vampirismEnchantment->get(&damage));
				}
            }
			damagesHappened[0] = damage; // Store the damage player caused (without regard to treatment)
		}
		// If player can't dodge
		if (!canDodge(player)) {
			int damage = enemy->damageWeaponed(); // Get enchantment damage
			player->setHealthPoint(player->getHealthPoint() - damage); // Player health reduced
			// If the player has VampirismEnchantment, treat him
            if (player->getWeapon()->getSuffixEnchantment()) { // Enchantment is not empty
				if (player->getWeapon()->getSuffixEnchantment()->instanceOf("VampirismEnchantment")) {
                    auto vampirismEnchantment = std::dynamic_pointer_cast<weapons::VampirismEnchantment>
                            (player->getWeapon()->getSuffixEnchantment());
                    player->setHealthPoint(player->getHealthPoint()
                                           + vampirismEnchantment->getHealHealthPoints(damage));
				}
            }
			damagesHappened[1] = damage; // Store the damage enemy caused (without regard to treatment)
		}
		return damagesHappened;
	}
	// Special ability module
	if (selection == 'l') {
		bool* done = new bool;
		*done = false;
		auto player = _character;
		if (player->getWeapon()->getName() == "Magic Wand") {
			player->setHealthPoint(player->getMaxHealthPoint());
			*done = true;
			return done;
		} else if (player->getWeapon()->getName() == "Wizard's Staff") {
			*done = true;
			return done;
		}

		auto playerSuffixEnchantment = player->getWeapon()->getSuffixEnchantment();
        if (playerSuffixEnchantment == nullptr) {
			*done = false;
        }
		else {
			if (playerSuffixEnchantment->instanceOf("HealingEnchantment")) {
                auto healingEnchantment = std::dynamic_pointer_cast<weapons::HealingEnchantment>
                        (playerSuffixEnchantment);
				player->setHealthPoint(player->getHealthPoint() + healingEnchantment->get());
				*done = true;
			}
		}
		return done;
	}
	return nullptr;
}

void Game::setDungeon(std::shared_ptr<dungeon::Dungeon> dungeon) {
	_dungeon = dungeon;
	enterDungeon();
}

int Game::getSuccessTimes() {
	return _dungeonLevel - 1;
}

std::shared_ptr<Game> Game::instance() {
	return _game;
}


// Do not change/remove the initialisation of _randomGenerator and _realDistribution, otherwise change as needed.
Game::Game()
    : _randomGenerator{uint32_t(time(nullptr))}, _realDistribution{0.0, 1.0} {

}

// DO NOT modify implementation below this comment

int Game::randomIntBetweenInc(int min, int max) {
#if INPUT_SCRIPT
	return min; // for consistency when using the input script
#else
	if (min == max) return max;
	if (max < min) std::swap(min, max);

	int diff{max + 1 - min};
	return int(_randomGenerator() % unsigned(diff)) + min;
#endif
}

int Game::randomIntBetweenEx(int min, int max) {
#if INPUT_SCRIPT
	return max - 1; // for consistency when using the input script
#else
	if (min == max) return max; // technically invalid for an exclusive range
	if (max < min) std::swap(min, max);

	int diff{max - min};
	return int(_randomGenerator() % unsigned(diff)) + min;
#endif
}

double Game::randomDouble() {
#if INPUT_SCRIPT
	return 1.0; // for consistency when using the input script.
#else
	return _realDistribution(_randomGenerator);
#endif
}
