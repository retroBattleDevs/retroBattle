#pragma once
#include <iostream>
#include <string>
#include "external_libraries/PDCurses/curses.h"

enum class ItemType {
	Equipment,
	Consumable,
	Relict

};

class Item {

protected:
	int id;
	ItemType type;

	std::string name;
	std::string description;
	char* asciiSymbol;

public:
	Item(int id, ItemType type, const std::string& name, const std::string& description, const char* asciiSymbol);

	// Rule of 5
	virtual ~Item();
	Item(const Item& other);
	Item& operator=(const Item& other);
	Item(Item&& other) noexcept;
	Item& operator=(Item&& other) noexcept;

	
	int getId() const;
	ItemType getType() const;
	const std::string& getName() const;
	const std::string& getDescription() const;
	const char* getAsciiSymbol() const;

	virtual void use() = 0; // Verhalten, wenn Spieler das Item benutzt 
	virtual void inspect() const = 0; // Infoanzeige des Items, wenn Spieler das Item anschaut s


};