#ifndef CARD_GAME_H
#define CARD_GAME_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <random>
#include <memory>
#include <sstream>
#include <iomanip>

// Better Enums 头文件
#include <enum.h>

// 简单的CRC32校验 (header-only)
namespace crc32 {
    uint32_t calculate(const std::string& input);
    std::string generate_checksum(const std::string& input);
}

// Base64编码库
namespace base64 {
    std::string encode(const std::string &input);
    std::string decode(const std::string &input);
}

// 定义卡牌类型
BETTER_ENUM(CardType, int,
    Creature = 1,    // 生物
    Spell = 2        // 法术  
)

// 定义卡牌属性
BETTER_ENUM(Element, int,
    Physical = 1,    // 物理
    Light = 2,       // 光
    Dark = 3,        // 暗
    Water = 4,       // 水
    Fire = 5,        // 火
    Earth = 6,       // 土
    Wind = 7         // 风
)

// 定义稀有度
BETTER_ENUM(Rarity, int,
    Common = 1,
    Uncommon = 2,
    Rare = 3,
    Mythic = 4, 
    Funny = 5
)

// 卡牌类
class Card {
private:
    std::string id;
    std::string name;
    CardType type;
    std::vector<Element> elements;
    int cost;
    Rarity rarity;
    std::string description;
    int attack;
    int defense;
    int health;

    std::string elementToString(Element element) const;
    std::string rarityToString(Rarity rarity) const;

public:
    // 修改构造函数，明确初始化type
    Card(const std::string& id, const std::string& name, const std::vector<Element>& elements, 
         int cost, Rarity rarity, const std::string& description,
         int attack = 0, int defense = 0, int health = 0);

    std::string getId() const { return id; }
    std::string getName() const { return name; }
    CardType getType() const { return type; }
    std::vector<Element> getElements() const { return elements; }
    int getCost() const { return cost; }
    Rarity getRarity() const { return rarity; }
    std::string getDescription() const { return description; }
    int getAttack() const { return attack; }
    int getDefense() const { return defense; }
    int getHealth() const { return health; }

    bool hasElement(Element element) const;
    std::string serialize() const;
    void display() const;
};

// 套牌类
class Deck {
private:
    std::string name;
    std::vector<std::shared_ptr<Card>> cards;
    std::vector<Element> deckElements;
    std::string deckCode;

    void updateDeckElements();
    void updateDeckCode();
    std::string elementToString(Element element) const;
    std::string cardTypeToString(CardType type) const;

public:
    Deck(const std::string& name);
    
    void addCard(const std::shared_ptr<Card>& card);
    bool removeCard(const std::string& cardName);
    size_t getCardCount() const;
    std::string getName() const;
    std::string getDeckCode() const;
    
    std::map<Element, int> getElementDistribution() const;
    void display() const;
    void shuffle(); // 修复shuffle函数
    
    bool importFromDeckCode(const std::string& code, const std::vector<std::shared_ptr<Card>>& allCards);
    static bool isValidDeckCode(const std::string& code);
};

// 卡牌数据库类
class CardDatabase {
private:
    std::vector<std::shared_ptr<Card>> allCards;
    void initializeCards();

public:
    CardDatabase();
    const std::vector<std::shared_ptr<Card>>& getAllCards() const;
    std::shared_ptr<Card> findCard(const std::string& name) const;
    std::shared_ptr<Card> findCardById(const std::string& id) const;
    std::vector<std::shared_ptr<Card>> getCardsByType(CardType type) const;
    std::vector<std::shared_ptr<Card>> getCardsByElement(Element element) const;
};

// 游戏管理器类
class GameManager {
private:
    CardDatabase cardDB;
    std::vector<Deck> decks;

public:
    void displayAllCards() const;
    void createDeck();
    void displayDecks() const;
    void displayDeckDetails() const;
    void exportDeckCode() const;
    void importDeckFromCode();
    void showMenu() const;
    void run();
};

#endif // CARD_GAME_H
