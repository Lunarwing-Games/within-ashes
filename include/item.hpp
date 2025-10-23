#include <raylib.h>
#include <vector>
#include <string>
#include <cstdint>

enum ItemType
{
    IT_WEARABLE,
    IT_CONSUMABLE,
    IT_WEAPON,
};

enum WearSlot
{
    WS_NONE,
    WS_HEAD,
    WS_CHEST,
    WS_LEGS,
    WS_FEET,
};

class Item
{
public:
    std::string name;
    std::string desc;
    struct Data
    {
        uint32_t id;
        Texture2D texture;
        Texture2D icon;
    } data;

    ItemType type;

    Item(std::string n, std::string d, ItemType t)
        : name(std::move(n)), desc(std::move(d)), type(t) {}

    virtual ~Item() = default;
    virtual void Use() = 0;
};

class Weapon : public Item
{

};

class Consumable : public Item
{

};

class Armor : public Item
{

};