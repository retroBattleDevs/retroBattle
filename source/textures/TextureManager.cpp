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

	//player animation
	//front
	auto temp = std::make_shared<AsciiTexture>(5, 5);
	temp->fillRow(0, " (\") ");
	temp->fillRow(1, " /_\\ ");
	temp->fillRow(2, "/###|");
	temp->fillRow(3, " #_# ");
	temp->fillRow(4, " |  \\");
	addTexture("player-front-0", temp);

	temp = std::make_shared<AsciiTexture>(5, 5);
	temp->fillRow(0, " (\") ");
	temp->fillRow(1, " /_\\ ");
	temp->fillRow(2, "|###\\");
	temp->fillRow(3, " #_# ");
	temp->fillRow(4, "/  | ");
	addTexture("player-front-1", temp);

	//back
	temp = std::make_shared<AsciiTexture>(5, 5);
	temp->fillRow(0, " ( ) ");
	temp->fillRow(1, " /_\\ ");
	temp->fillRow(2, "/###|");
	temp->fillRow(3, " #_# ");
	temp->fillRow(4, " |  \\");
	addTexture("player-back-0", temp);

	temp = std::make_shared<AsciiTexture>(5, 5);
	temp->fillRow(0, " ( ) ");
	temp->fillRow(1, " /_\\ ");
	temp->fillRow(2, "|###\\");
	temp->fillRow(3, " #_# ");
	temp->fillRow(4, "/  | ");
	addTexture("player-back-1", temp);

	//left
	temp = std::make_shared<AsciiTexture>(5, 5);
	temp->fillRow(0, "(' ) ");
	temp->fillRow(1, " /\\  ");
	temp->fillRow(2, "|##\\ ");
	temp->fillRow(3, " ##  ");
	temp->fillRow(4, "/ |  ");
	addTexture("player-left-0", temp);

	temp = std::make_shared<AsciiTexture>(5, 5);
	temp->fillRow(0, "(' ) ");
	temp->fillRow(1, " /\\  ");
	temp->fillRow(2, "/##| ");
	temp->fillRow(3, " ##  ");
	temp->fillRow(4, " \\/  ");
	addTexture("player-left-1", temp);

	//right
	temp = std::make_shared<AsciiTexture>(5, 5);
	temp->fillRow(0, " ( ')");
	temp->fillRow(1, "  /\\ ");
	temp->fillRow(2, " /##|");
	temp->fillRow(3, "  ## ");
	temp->fillRow(4, " /  \\");
	addTexture("player-right-0", temp);

	temp = std::make_shared<AsciiTexture>(5, 5);
	temp->fillRow(0, " ( ')");
	temp->fillRow(1, "  /\\ ");
	temp->fillRow(2, " |##\\");
	temp->fillRow(3, "  ## ");
	temp->fillRow(4, "  \\/ ");
	addTexture("player-right-1", temp);
	//end of player animation
	
	//relict animation
	temp = std::make_shared<AsciiTexture>(7, 7);
	temp->fillRow(0, "     * ");
	temp->fillRow(1, " *.-.  ");
	temp->fillRow(2, " (0*0) ");
	temp->fillRow(3, "  \\+/  ");
	temp->fillRow(4, "  / \\  ");
	temp->fillRow(5, "  | |  ");
	temp->fillRow(6, "     * ");
	addTexture("relic_0", temp);

	temp = std::make_shared<AsciiTexture>(7, 7);
	temp->fillRow(0, "*      ");
	temp->fillRow(1, "  .-.* ");
	temp->fillRow(2, " (0*0) ");
	temp->fillRow(3, "  \\+/  ");
	temp->fillRow(4, "  / \\  ");
	temp->fillRow(5, "  | |  ");
	temp->fillRow(6, "   *   ");
	addTexture("relic_1", temp);

	temp = std::make_shared<AsciiTexture>(7, 7);
	temp->fillRow(0, "       ");
	temp->fillRow(1, "* .-.  ");
	temp->fillRow(2, " (-*-)*");
	temp->fillRow(3, "  \\+/  ");
	temp->fillRow(4, "  / \\  ");
	temp->fillRow(5, " *| |  ");
	temp->fillRow(6, "       ");
	addTexture("relic_2", temp);

	temp = std::make_shared<AsciiTexture>(7, 7);
	temp->fillRow(0, "       ");
	temp->fillRow(1, "  .-. *");
	temp->fillRow(2, " (0*0) ");
	temp->fillRow(3, "* \\+/  ");
	temp->fillRow(4, "  / \\  ");
	temp->fillRow(5, "  |*|  ");
	temp->fillRow(6, "       ");
	addTexture("relic_3", temp);
	//end of relict animation frames
	
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
