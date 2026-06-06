#include "headers/textures/TextureManager.h"


TextureManager::TextureManager(){
	loadDefaultTextures();
}


void TextureManager::loadDefaultTextures(){
	//	create the textures here
	//	create a new texure with a shared pointer (width, hight)
	//	fill the rows with strings of length width
	//	add them to the container with a key name
	//

	//player texure
	auto temp = std::make_shared<AsciiTexture>(3, 3);
	temp->fillRow(0, "\\07");
	temp->fillRow(1, " H ");
	temp->fillRow(2, "/ L");
	addTexture("player", temp);

	//more textures
	auto neutralChaseEnemy = std::make_shared<AsciiTexture>(5, 5);
	neutralChaseEnemy->fillRow(1, " ?O?");
	addTexture("neutralChaseEnemy", neutralChaseEnemy);

	auto aggressiveChaseEnemy = std::make_shared<AsciiTexture>(5, 5);
	aggressiveChaseEnemy->fillRow(1, "!!W!!");
	addTexture("aggressiveChaseEnemy", aggressiveChaseEnemy);
}

void TextureManager::addTexture(const std::string& key, std::shared_ptr<AsciiTexture> tex){
	textureMap[key] = tex;
}

std::shared_ptr<AsciiTexture> TextureManager::getTexture(const std::string& key) const{
	if (textureMap.count(key)) {
		return textureMap.at(key);
	}
	return nullptr;
}
