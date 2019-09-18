#ifndef WEAPONS_H
#define WEAPONS_H
#include <string>
#include <memory>
namespace core {
namespace weapons {
/**
 * @brief The Interface class 用作装饰器使用的接口
 */
class Interface
{
    virtual int get(void* args = nullptr) = 0; // 接口的函数
};

/**
 * @brief TODO The Enchantment class 附魔基类
 */
class Enchantment : public Interface
{
public:
    /**
     * @brief Enchantment 附魔基类
     */
    Enchantment();

    /**
     * @brief getEnchantmentType 获得类名
     * @return
     */
    std::string getEnchantmentType();

protected:
    std::string _enchantmentType; // 储存类名
};

/**
 * @brief TODO The FlameEnchantment class
 */
class FlameEnchantment : public Enchantment
{
public:
    /**
     * @brief FlameEnchantment 火焰附魔
     */
    FlameEnchantment();

    /**
     * @brief getExtraDamage 获得额外的伤害值
     * @return
     */
    int getExtraDamage();

    /**
     * @brief get 获得额外的伤害值(等同于getExtraDamage)
     * @return
     */
    int get(void* args = nullptr);
};

/**
 * @brief TODO The ElectricityEnchantment class
 */
class ElectricityEnchantment : public Enchantment
{
public:
    /**
     * @brief ElectricityEnchantment 带电附魔
     */
    ElectricityEnchantment();
    /**
     * @brief getExtraDamage 获得额外的伤害值
     * @return
     */
    int getExtraDamage();

    /**
     * @brief get 获得额外的伤害值(等同于getExtraDamage)
     * @return
     */
    int get(void* args = nullptr);
};

/**
 * @brief TODO The HealingEnchantment class
 */
class HealingEnchantment : public Enchantment
{
public:
    /**
     * @brief HealingEnchantment 治疗附魔
     */
    HealingEnchantment();

    /**
     * @brief getHealHealthPoints 获得治疗值
     * @return
     */
    int getHealHealthPoints();

    /**
     * @brief get 获得治疗值(等同于getHealHealthPoints)
     * @return
     */
    int get(void* args = nullptr);
};

/**
 * @brief TODO The VampirismEnchantment class
 */
class VampirismEnchantment : public Enchantment
{
public:
    /**
     * @brief VampirismEnchantment
     */
    VampirismEnchantment();

    /**
     * @brief getHealHealthPoints 获得本回合治疗值
     * @param damagedThisRound
     * @return
     */
    int getHealHealthPoints(int damagedThisRound);

    /**
     * @brief get 获得本回合治疗值(等同于getHealHealthPoints)
     * @return
     */
    int get(void* args = nullptr);
};

/**
 * @brief TODO The Weapon class 武器的基类
 */
class Weapon : public Interface
{
public:
    /**
     * @brief Weapon 武器的构造函数
     */
	Weapon();

    /**
     * @brief Weapon 武器的构造函数
     * @param name
     * @param description
     */
	Weapon(std::string &name, std::string &description);

    /**
     * @brief Weapon 武器的构造函数
     * @param name
     * @param description
     * @param longDescription
     */
	Weapon(std::string &name, std::string &description, std::string &longDescription);

    /**
     * @brief Weapon 武器的构造函数
     * @param name
     * @param description
     * @param longDescription
     * @param minDamage
     * @param maxDamage
     */
	Weapon(std::string &name, std::string &description, std::string &longDescription, int minDamage, int maxDamage);

    /**
     * @brief getName 获得名字
     * @return
     */
	std::string getName();

	std::string getFullName();

    /**
     * @brief setName 设置名字
     * @param name
     */
	void setName(std::string name);

    /**
     * @brief getDescription 获得短描述
     * @return
     */
    std::string getDescription();

    /**
     * @brief setDescription 设置短描述
     * @param description
     */
    void setDescription(std::string description);

    /**
     * @brief getLongDescription 获得长描述
     * @return
     */
    std::string getLongDescription();

    /**
     * @brief setLongDescription 设置长描述
     * @param longDescription
     */
    void setLongDescription(std::string longDescription);

    /**
     * @brief getDamageRange 获得武器（包括附魔加成）的最小攻击力和最大攻击力
     * @return
     */
    int* getDamageRange();

    /**
     * @brief setDamageRange 设置武器的最小攻击力和最大攻击力
     * @param minDamage
     * @param maxDamage
     */
	void setDamageRange(int minDamage, int maxDamage);

    /**
     * @brief getSpecialAbilityDescription 获得特殊技能描述
     * @return
     */
	std::string getSpecialAbilityDescription();

    /**
     * @brief setSpecialAbilityDescription 设置特殊技能描述
     * @param specialAbilityDescription
     */
    void setSpecialAbilityDescription(std::string specialAbilityDescription);

    /**
     * @brief getPrefixEnchantment 获得前缀附魔
     * @return
     */
    std::shared_ptr<Enchantment> getPrefixEnchantment();

    /**
     * @brief getSuffixEnchantment 获得后缀附魔
     * @return
     */
    std::shared_ptr<Enchantment> getSuffixEnchantment();

    /**
     * @brief get 使用getDamageRange()的结果随机取一个伤害值
     * @param args
     * @return
     */
    int get(void* args = nullptr);
private:
    /**
     * @brief getEnchantmentDamage
     * @return
     */
	int getEnchantmentDamage();

	std::string _name = "";
	std::string _description = "";
	std::string _longDescription = "";
	int _minDamage = -1;
	int _maxDamage = -1;
	std::string _specialAbilityDescription = "";
	std::shared_ptr<Enchantment> _prefixEnchantment;
	std::shared_ptr<Enchantment> _suffixEnchantment;
};

/**
 * @brief TODO The Fists class
 */
class Fists : public Weapon
{
public:
    /**
     * @brief Fists
     */
	Fists();
};

/**
 * @brief TODO The Boomerang class
 */
class Boomerang : public Weapon
{
public:
    /**
     * @brief Boomerang
     */
	Boomerang();
};

/**
 * @brief TODO The ShortSword class
 */
class ShortSword : public Weapon
{
public:
    /**
     * @brief ShortSword
     */
	ShortSword();
};

/**
 * @brief TODO The BattleAxe class
 */
class BattleAxe : public Weapon
{
public:
    /**
     * @brief BattleAxe
     */
	BattleAxe();
};

/**
 * @brief TODO The WizardsStaff class
 */
class WizardsStaff : public Weapon
{
public:
    /**
     * @brief WizardsStaff
     */
	WizardsStaff();
};

/**
 * @brief TODO The MagicWand class
 */
class MagicWand : public Weapon
{
public:
    /**
     * @brief MagicWand
     */
	MagicWand();
};

} // namespace items
} // namespace core

std::ostream& operator<<(std::ostream &stream, core::weapons::Weapon &weapon);

#endif // WEAPONS_H
