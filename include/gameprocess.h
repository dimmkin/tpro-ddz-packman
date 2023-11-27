#pragma once

#include "field.h"
#include "packman.h"
#include "ghost.h"

#include <cassert>
#include <map>

enum class GameState {
	PLAY,
	LOSE
};

class GameProcess
{
public:
	Field field;
	Packman packman;
	std::map<GhostID, Ghost> ghosts;
	GameState gameState = GameState::PLAY;

	sf::Font font;
	sf::RectangleShape gameOverBackground;
	sf::Text gameOverTitle;
};

static void initializeGhostByID(std::map<GhostID, Ghost>& ghosts, GhostID ghostID);
void initializeGameProcess(GameProcess& process, const sf::Vector2f& processSize);
void updateGameProcess(GameProcess& process, float elapsedTime);
void drawGameProcess(sf::RenderWindow& window, GameProcess& process);
