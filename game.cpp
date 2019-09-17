#include "game.h"
#include "testingsettings.h"
#include <sstream>

using namespace core;

// TODO: Add additional implementation here
std::shared_ptr<Game> Game::_game = std::shared_ptr<Game>(new Game());

std::shared_ptr<Character> Game::player()
{
	return _character;
}

void Game::setPlayer(std::shared_ptr<Character> character)
{
	_character = character;
}

std::shared_ptr<dungeon::Dungeon> Game::dungeon()
{
	return _dungeon;
}

std::shared_ptr<dungeon::BasicDungeon> Game::getBasicDungeon() // 便捷函数
{
	return std::static_pointer_cast<dungeon::BasicDungeon>(_dungeon);
}

bool Game::createDungeon(std::string dungeonType = "BasicDungeon")
{
	std::shared_ptr<dungeon::DungeonBuilder> builder;
	if (dungeonType == "BasicDungeon")
	{
		builder = std::make_shared<dungeon::BasicDungeonBuilder>();
		_dungeon = builder->buildDungeon();
		return _dungeon != nullptr;
	}
	return false;
}

bool Game::enterDungeon()
{
	if (_dungeon == nullptr)
		return false;
	auto entranceRoom = getBasicDungeon()->getEntranceRoom();
	if (entranceRoom == nullptr)
		return false;
	getBasicDungeon()->setNowRoom(entranceRoom);
	return true;
}

auto Game::currentRoom()
{
	return getBasicDungeon()->getNowRoom();
}

bool Game::navigate(char direction)
{
	auto basic_dungeon = getBasicDungeon();
	auto room = currentRoom();
	room->checkDirectionVaild(direction);
	auto door = room->getDoor(direction);
	if (door == nullptr)
		return false;
	basic_dungeon->setNowRoom(door->getNeighbourRoom(room));
	return true;
}

bool Game::navigateBack()
{
	auto basic_dungeon = getBasicDungeon();
	basic_dungeon->setNowRoom(basic_dungeon->path(-2));
	return true;
}

void Game::exitLevel()
{
	_dungeonLevel++;
}

void Game::exitDungeon()
{
	setPlayer(nullptr);
	setDungeon(nullptr);
	_dungeonLevel = 1;
}

bool Game::canDodge(std::shared_ptr<creatures::Creature> creature)
{
	return randomIntBetweenInc(0, 100) <= creature->dodgeChance();
}

void* Game::doActionRound(char selection)
{
	if (selection == 'a')
	{
		int* damagesHappened = new int[2];
		damagesHappened[0] = damagesHappened[1] = 0;

		auto player = _character;
		auto creature = getBasicDungeon()->getNowRoom()->getCreature();
		if (!canDodge(creature))
		{
			int* damageRange = player->damageWeaponed();
			int damage = randomIntBetweenInc(damageRange[0], damageRange[1]);
			creature->setHealthPoint(creature->getHealthPoint() - damage);
			if (creature->getWeapon()->getSuffixEnchantment()->getEnchantmentType() == "VampirismEnchantment")
			{
				auto vampirismEnchantment = std::static_pointer_cast<weapons::VampirismEnchantment>(creature->getWeapon()->getSuffixEnchantment());
				vampirismEnchantment->doHeal(creature, damage);
			}
			damagesHappened[0] = damage;
		}
		if (!canDodge(player))
		{
			int* damageRange = creature->damageWeaponed();
			int damage = randomIntBetweenInc(damageRange[0], damageRange[1]);
			player->setHealthPoint(player->getHealthPoint() - damage);
			if (player->getWeapon()->getSuffixEnchantment()->getEnchantmentType() == "VampirismEnchantment")
			{
				auto vampirismEnchantment = std::static_pointer_cast<weapons::VampirismEnchantment>(player->getWeapon()->getSuffixEnchantment());
				vampirismEnchantment->doHeal(player, damage);
			}
			damagesHappened[1] = damage;
		}
		return damagesHappened;
	}
	if (selection == 'l')
	{
		bool* done = new bool;
		auto player = _character;
		auto playerSuffixEnchantment = player->getWeapon()->getSuffixEnchantment();
		if (playerSuffixEnchantment == nullptr)
			*done = false;
		else
		{
			if (playerSuffixEnchantment->getEnchantmentType() == "HealingEnchantment")
			{
				auto healingEnchantment = std::static_pointer_cast<weapons::HealingEnchantment>(playerSuffixEnchantment);
				//healingEnchantment->doHeal(player);
				healingEnchantment->getHealHealthPoints
				*done = true;
			}
		}
		return done;
	}
}

void Game::setDungeon(std::shared_ptr<dungeon::Dungeon> dungeon)
{
	_dungeon = dungeon;
	enterDungeon();
}

int Game::getSuccessTimes()
{
	return _dungeonLevel - 1;
}

static std::shared_ptr<Game> Game::instance()
{
	return _game;
}


// Do not change/remove the initialisation of _randomGenerator and _realDistribution, otherwise change as needed.
Game::Game()
  : _randomGenerator{uint32_t(time(nullptr))}, _realDistribution{0.0, 1.0}
{

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
