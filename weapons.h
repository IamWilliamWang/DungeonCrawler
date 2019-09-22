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
    /**
     * @brief get 获得想获取的数据
     * @param args 任何需要传入的参数
     * @return 获得的整形数据
     */
    virtual int get(void* args = nullptr) = 0;
};

/**
 * @brief The Enchantment class 附魔基类
 */
class Enchantment : public Interface
{
public:
    /**
     * @brief Enchantment 附魔基类
     */
    Enchantment();

    /**
     * @brief instanceOf 判断附魔是否为typeName类型的instance
     * @param typeName
     * @return
     */
    bool instanceOf(std::string typeName)
    {
        return _enchantmentType == typeName;
    }

protected:
    /**
     * @brief getEnchantmentType 获得类名
     * @return
     */
    std::string getEnchantmentType();

    std::string _enchantmentType; // 储存类名
};

/**
 * @brief The FlameEnchantment class
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
 * @brief The ElectricityEnchantment class
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
 * @brief The HealingEnchantment class
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
 * @brief The VampirismEnchantment class
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
 * @brief The Weapon class 武器的基类
 */
class Weapon : public Interface
{
public:
    /**
     * @brief Weapon 武器的构造函数
     * @param name
     */
    Weapon(std::string name);

    /**
     * @brief getName 获得名字
     * @return
     */
	std::string getName();

    /**
     * @brief getFullName 获得带有前缀后缀的全名
     * @return
     */
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

    void setPrefixEnchantment(std::shared_ptr<Enchantment> prefixEnchantment);

    /**
     * @brief getSuffixEnchantment 获得后缀附魔
     * @return
     */
    std::shared_ptr<Enchantment> getSuffixEnchantment();

    void setSuffixEnchantment(std::shared_ptr<Enchantment> suffixEnchantment);

    /**
     * @brief get 使用getDamageRange()的结果随机取一个伤害值
     * @param args
     * @return
     */
    int get(void* args = nullptr);
private:

    /**
     * @brief createEnchantmentOrNot 决定是否添加附魔，如果是就自动添加
     * @return
     */
    bool createEnchantmentOrNot();

    /**
     * @brief hasEnchantmentCount 要拥有的附魔数量
     * @return
     */
    int hasEnchantmentCount();

    /**
     * @brief createEnchantment 为本武器创建enchantmentCount个附魔
     * @param enchantmentCount
     * @return
     */
    bool createEnchantment(int enchantmentCount);

    /**
     * @brief getEnchantmentDamage 获得附魔的额外伤害
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
 * @brief The Fists class
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
 * @brief The Boomerang class
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
 * @brief The ShortSword class
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
 * @brief The BattleAxe class
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
 * @brief The WizardsStaff class
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
 * @brief The MagicWand class
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
