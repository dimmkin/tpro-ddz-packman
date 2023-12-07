#include "gameprocess.h"
#include <iostream>
#include <fstream>
using namespace sf;
#include "json/nlohmann/json.hpp"
using json = nlohmann::json;

bool GameProcess::initializeGhostByID(std::map<GhostID, Ghost>& ghosts, GhostID ghostID)
{
	Ghost& ghost = ghosts[ghostID];

	const std::string texturePath = TEXTURE_MAPPING.at(ghostID);

	return ghost.initializeHero(__field.getGhostsStartPosition(ghostID), texturePath);
}

bool GameProcess::initializeBonusByType(std::map<TypesBonuses, Bonus>& bonuses, TypesBonuses type, const sf::IntRect frame, bool active)
{
	Bonus& bonus = bonuses[type];

	const std::string texturePath = BONUSES_TEXTURE;

	return bonus.initializeBonus(__field.getBonusesStartPosition(type), texturePath, frame, type, active);
}

void GameProcess::initializeGameProcess(const sf::Vector2f& processSize)
{
	bool succeed = font.loadFromFile("font/EightBits.ttf");

	field.initializeField();
	packman.initializePackman(field, packman, 150.f);

	std::ifstream file("text.json");
	json data = json::parse(file);
	file.close();
	int i = data["Start_game"][1];
	switch (i)
	{
	case 1 :
		initializeGhostByID(ghosts, GhostID::FIRST);
		break;
	case 2:
		initializeGhostByID(ghosts, GhostID::FIRST);
		initializeGhostByID(ghosts, GhostID::SECOND);
		break;
	case 3:
		initializeGhostByID(ghosts, GhostID::FIRST);
		initializeGhostByID(ghosts, GhostID::SECOND);
		initializeGhostByID(ghosts, GhostID::THIRD);
		break;
	case 4:
		initializeGhostByID(ghosts, GhostID::FIRST);
		initializeGhostByID(ghosts, GhostID::SECOND);
		initializeGhostByID(ghosts, GhostID::THIRD);
		initializeGhostByID(ghosts, GhostID::FORTH);
		break;
	default:
		break;
	}

	initializeBonusByType(bonuses, TypesBonuses::BOMB, FRAME_BOMB);
	initializeBonusByType(bonuses, TypesBonuses::CYCLE, FRAME_CYCLE);

	gameState = GameState::PLAY;
	totalCookiesCount = field.countRemainingCookies();

	const sf::FloatRect titleBounds = gameOverTitle.getLocalBounds();
	gameOverTitle.setOrigin(0.5f * titleBounds.width, 0.5f * titleBounds.height);
}

void GameProcess::killBotsAndChangePosition()
{
	ghosts.clear();
	field.clearMap(SYMBOLS_GHOSTS, field.map);
	field.randomizeMap(SYMBOLS_GHOSTS, field.map);

	std::ifstream file("text.json");
	json data = json::parse(file);
	file.close();
	int i = data["Start_game"][1];
	switch (i)
	{
	case 1:
		initializeGhostByID(ghosts, GhostID::FIRST);
		break;
	case 2:
		initializeGhostByID(ghosts, GhostID::FIRST);
		initializeGhostByID(ghosts, GhostID::SECOND);
		break;
	case 3:
		initializeGhostByID(ghosts, GhostID::FIRST);
		initializeGhostByID(ghosts, GhostID::SECOND);
		initializeGhostByID(ghosts, GhostID::THIRD);
		break;
	case 4:
		initializeGhostByID(ghosts, GhostID::FIRST);
		initializeGhostByID(ghosts, GhostID::SECOND);
		initializeGhostByID(ghosts, GhostID::THIRD);
		initializeGhostByID(ghosts, GhostID::FORTH);
		break;
	default:
		break;
	}
}

void GameProcess::changedBonusesPosition()
{
	__field.clearMap(SYMBOLS_BONUSES, __field.__map);
	__field.randomizeMap(SYMBOLS_BONUSES, __field.__map);
	initializeBonusByType(__bonuses, TypesBonuses::BOMB, FRAME_BOMB);
	initializeBonusByType(__bonuses, TypesBonuses::CYCLE, FRAME_CYCLE);
	__field.__changed = true;
}

void GameProcess::redrawingBonuses()
{
	if (packman.eatenCookies == 50 && !field.changed) {
		changedBonusesPosition();
	}
	if (packman.eatenCookies == 51) {
		field.changed = false;
	}
	if (packman.eatenCookies == 100 && !field.changed) {
		changedBonusesPosition();
	}
	if (packman.eatenCookies == 101) {
		field.changed = false;
	}
	if (packman.eatenCookies == 150 && !field.changed) {
		changedBonusesPosition();
	}
	if (packman.eatenCookies == 151) {
		field.changed = false;
	}
	if (packman.eatenCookies == 200 && !field.changed) {
		changedBonusesPosition();
	}
	if (packman.eatenCookies == 201) {
		field.changed = false;
	}
}

void GameProcess::updateGameProcess(float elapsedTime, bool &flag_lifes, unsigned int lifes)
{

	if (gameState == GameState::PLAY) {
		packman.updateHero(elapsedTime, field);

		redrawingBonuses();

		for (auto& pair : ghosts) {
			pair.second.updateHero(elapsedTime, field, 90.f);
		}

		const sf::FloatRect packmanBounds = packman.getPackmanBounds();
		for ( auto& pair : ghosts) {
			if (pair.second.figure.getGlobalBounds().intersects(packmanBounds)) {
				if (lifes == 1) {
					gameState = GameState::LOSE;
				}
				else
				{
					flag_lifes = true;
					packman.direction = packman.changeOfDirection(packman.direction);
					packman.orientationDegrees = packman.directionOrientationDegrees(packman.direction);
					pair.second.direction = pair.second.changeOfDirection(pair.second.direction);
					exit;
				}
			}
		}
		for (auto it = packman.activeBonuses.begin(); it != packman.activeBonuses.end(); ++it) {
			if (it->second.bonusType == TypesBonuses::CYCLE && it->second.active && packman.eatenCookies >= it->second.eatenDots + 10) {
				packman.setSpeedMultiplier(120.f);
				it->second.active = false;
			}
		}

		for (auto it = bonuses.begin(); it != bonuses.end();) {
			if (it->second.figure.getGlobalBounds().intersects(packmanBounds)) {
				if (it->second.bonusType == TypesBonuses::BOMB) {
					it->second.active = true;
					killBotsAndChangePosition();
				}
				if (it->second.bonusType == TypesBonuses::CYCLE) {
					packman.setSpeedMultiplier(240.f);
					it->second.active = true;
					it->second.eatenDots = packman.eatenCookies;
					packman.activeBonuses[it->first] = it->second;
				}
			}
			if (it->second.bonusType == TypesBonuses::BOMB && it->second.active) {
				it = bonuses.erase(it);
				continue;
			}
			if (it->second.bonusType == TypesBonuses::CYCLE && it->second.active) {
				it = bonuses.erase(it);
				continue;
			}
			++it;
		}

		if (__totalCookiesCount - __packman.__eatenCookies == 0) {
			__gameState = GameState::WIN;
		}
	}
}

std::string GameProcess::getGameProcessWindowTitle()
{
	std::string title;
	static double cookiesLeft;
	int result;

	if (__gameState == GameState::PLAY) {
		cookiesLeft = floor(static_cast<double>(__packman.__eatenCookies) / __totalCookiesCount * 100);
		result = cookiesLeft;
		title = std::to_string(result) + '%';
	}
	return title;
}

void GameProcess::drawGameProcess(sf::RenderWindow& window)
{
	__field.drawField(window);
	__packman.drawPackman(window);

	for (auto& pair : __ghosts) {
		pair.second.drawHero(window);
	}

	for (auto& pair : __bonuses) {
		pair.second.drawBonus(window);
	}

}
