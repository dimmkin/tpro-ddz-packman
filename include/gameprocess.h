#pragma once

#include "bonus.h"
#include "hero.h"
#include "field.h"
#include "packman.h"
#include "ghost.h"
#include <Windows.h>
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
	Field field;
	Packman packman;
	std::map<GhostID, Ghost> ghosts;
	std::map<TypesBonuses, Bonus> bonuses;
	GameState gameState = GameState::PLAY;
	unsigned int totalCookiesCount;
	sf::Font font;
	sf::RectangleShape gameOverBackground;
	sf::Text gameOverTitle;

	// methods
	void redrawingBonuses();
	void changedBonusesPosition();
	void killBotsAndChangePosition();
	bool initializeGhostByID(std::map<GhostID, Ghost>& ghosts, GhostID ghostID);
	bool initializeBonusByType(std::map<TypesBonuses, Bonus>& bonuses, TypesBonuses type, const sf::IntRect frame, bool active = false);
	void updateGameOverTitle(sf::Text& title, const std::string& text);
	void updateGameProcess(float elapsedTime);
	std::string getGameProcessWindowTitle();
	void drawGameProcess(sf::RenderWindow& window);
	void initializeGameProcess(const sf::Vector2f& processSize);
};

