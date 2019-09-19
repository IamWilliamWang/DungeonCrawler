#include "game.h"
#include "testingsettings.h"
#include "dungeonbuilder.h"
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

std::shared_ptr<dungeon::Room> Game::currentRoom()
{
    return getBasicDungeon()->getNowRoom();
}

bool Game::createDungeon(std::string dungeonType)
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
    // 进攻模块
	if (selection == 'a')
	{
        int* damagesHappened = new int[2]; // 储存我方造成的伤害和敌方造成的伤害
		damagesHappened[0] = damagesHappened[1] = 0;

		auto player = _character;
        auto enemy = getBasicDungeon()->getNowRoom()->getCreature();
        // 如果敌方无法躲避
        if (!canDodge(enemy))
		{
            int damage = player->damageWeaponed(); // 获得附魔伤害值
            enemy->setHealthPoint(enemy->getHealthPoint() - damage); // 敌方掉血
            // 敌方有VampirismEnchantment则治疗敌方
            if (enemy->getWeapon()->getSuffixEnchantment()) // 附魔不为空
                if (enemy->getWeapon()->getSuffixEnchantment()->instanceOf("VampirismEnchantment"))
                {
                    auto vampirismEnchantment = std::static_pointer_cast<weapons::VampirismEnchantment>(enemy->getWeapon()->getSuffixEnchantment());
                    enemy->setHealthPoint(enemy->getHealthPoint() + vampirismEnchantment->get(&damage));
                }
            damagesHappened[0] = damage; // 储存我方造成的伤害（不考虑治疗）
		}
        // 如果我方无法躲避
		if (!canDodge(player))
		{
            int damage = enemy->damageWeaponed(); // 获得附魔伤害值
            player->setHealthPoint(player->getHealthPoint() - damage); // 我方掉血
            // 我方有VampirismEnchantment则治疗敌方
            if (player->getWeapon()->getSuffixEnchantment()) // 附魔不为空
                if (player->getWeapon()->getSuffixEnchantment()->instanceOf("VampirismEnchantment"))
                {
                    auto vampirismEnchantment = std::static_pointer_cast<weapons::VampirismEnchantment>(player->getWeapon()->getSuffixEnchantment());
                    player->setHealthPoint(player->getHealthPoint() + vampirismEnchantment->getHealHealthPoints(damage));
                }
            damagesHappened[1] = damage; // 储存敌方造成的伤害（不考虑治疗）
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
            if (playerSuffixEnchantment->instanceOf("HealingEnchantment"))
			{
				auto healingEnchantment = std::static_pointer_cast<weapons::HealingEnchantment>(playerSuffixEnchantment);
                player->setHealthPoint(player->getHealthPoint() + healingEnchantment->get());
				*done = true;
			}
		}
		return done;
	}
    return nullptr;
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

std::shared_ptr<Game> Game::instance()
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
