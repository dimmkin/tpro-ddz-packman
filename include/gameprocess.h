#pragma once

#include "../include/bonus.h"
#include "../include/hero.h"
#include "../include/field.h"
#include "../include/packman.h"
#include "../include/ghost.h"
//#include <Windows.h>
#include <thread>
#include <cassert>
#include <map>

// constants 
const std::vector<char> SYMBOLS_GHOSTS = { '1','2','3','4' };
const std::vector<char> SYMBOLS_BONUSES = { 'Q', 'W', 'E' };

static const std::map<GhostID, std::string> TEXTURE_MAPPING = {
	{ GhostID::FIRST, RED_GHOST_TEXTURE },
	{ GhostID::SECOND, PINK_GHOST_TEXTURE },
	{ GhostID::THIRD, GREEN_GHOST_TEXTURE },
	{ GhostID::FORTH, ORANGE_GHOST_TEXTURE },
};

enum class GameState
{
	PLAY,
	LOSE,
	WIN
};

class GameProcess
{
public:

	// fields 
	Field __field;
	Packman __packman;
	std::map<GhostID, Ghost> __ghosts;
	std::map<TypesBonuses, Bonus> __bonuses;
	GameState __gameState = GameState::PLAY;
	unsigned int __totalCookiesCount;
	sf::Font __font;
	sf::RectangleShape __gameOverBackground;
	sf::Text __gameOverTitle;

	// methods
	void redrawingBonuses();
	void changedBonusesPosition();
	void killBotsAndChangePosition();
	bool initializeGhostByID(std::map<GhostID, Ghost>& ghosts, GhostID ghostID);
	bool initializeBonusByType(std::map<TypesBonuses, Bonus>& bonuses, TypesBonuses type, const sf::IntRect frame, bool active = false);

	void updateGameOverTitle(sf::Text& title, const std::string& text);
	void updateGameProcess(float elapsedTime, bool &flag_lifes, unsigned int lifes);

	std::string getGameProcessWindowTitle();
	void drawGameProcess(sf::RenderWindow& window);
	void initializeGameProcess(const sf::Vector2f& processSize);
};
