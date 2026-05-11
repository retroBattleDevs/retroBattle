#include "headers/items/Item.h"
#include <cstring>

// Constructor
Item::Item(int id, ItemType type, const std::string& name,
    const std::string& description, const char* asciiSymbol)
{
    this->id = id;
    this->type = type;
    this->name = name;
    this->description = description;

    this->asciiSymbol = new char[strlen(asciiSymbol) + 1];
    std::strcpy(this->asciiSymbol, asciiSymbol);
}

// Destructor
Item::~Item()
{
    delete[] this->asciiSymbol;
}

// Copy Constructor
Item::Item(const Item& other)
{
    this->id = other.id;
    this->type = other.type;
    this->name = other.name;
    this->description = other.description;

    this->asciiSymbol = new char[strlen(other.asciiSymbol) + 1];
    std::strcpy(this->asciiSymbol, other.asciiSymbol);
}

// Copy Assignment
Item& Item::operator=(const Item& other)
{
    if (this == &other)
        return *this;

    this->id = other.id;
    this->type = other.type;
    this->name = other.name;
    this->description = other.description;

    delete[] this->asciiSymbol;
    this->asciiSymbol = new char[strlen(other.asciiSymbol) + 1];
    std::strcpy(this->asciiSymbol, other.asciiSymbol);

    return *this;
}

// Move Constructor
Item::Item(Item&& other) noexcept
{
    this->id = other.id;
    this->type = other.type;
    this->name = std::move(other.name);
    this->description = std::move(other.description);

    this->asciiSymbol = other.asciiSymbol;
    other.asciiSymbol = nullptr;
}

// Move Assignment
Item& Item::operator=(Item&& other) noexcept
{
    if (this == &other)
        return *this;

    this->id = other.id;
    this->type = other.type;
    this->name = std::move(other.name);
    this->description = std::move(other.description);

    delete[] this->asciiSymbol;
    this->asciiSymbol = other.asciiSymbol;
    other.asciiSymbol = nullptr;

    return *this;
}

// Getter
int Item::getId() const { return this->id; }
ItemType Item::getType() const { return this->type; }
const std::string& Item::getName() const { return this->name; }
const std::string& Item::getDescription() const { return this->description; }
const char* Item::getAsciiSymbol() const { return this->asciiSymbol; }
