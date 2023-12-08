#include "../include/gameprocess.h"
#include <iostream>
#include <fstream>
using namespace sf;
#include "../json/nlohmann/json.hpp"
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
	bool succeed = __font.loadFromFile("font/EightBits.ttf");

	__field.initializeField();
	__packman.initializePackman(__field, __packman, 150.f);

	std::ifstream file("text.json");
	json data = json::parse(file);
	file.close();
	int i = data["Start_game"][1];
	switch (i)
	{
	case 1 :
		initializeGhostByID(__ghosts, GhostID::FIRST);
		break;
	case 2:
		initializeGhostByID(__ghosts, GhostID::FIRST);
		initializeGhostByID(__ghosts, GhostID::SECOND);
		break;
	case 3:
		initializeGhostByID(__ghosts, GhostID::FIRST);
		initializeGhostByID(__ghosts, GhostID::SECOND);
		initializeGhostByID(__ghosts, GhostID::THIRD);
		break;
	case 4:
		initializeGhostByID(__ghosts, GhostID::FIRST);
		initializeGhostByID(__ghosts, GhostID::SECOND);
		initializeGhostByID(__ghosts, GhostID::THIRD);
		initializeGhostByID(__ghosts, GhostID::FORTH);
		break;
	default:
		break;
	}

	initializeBonusByType(__bonuses, TypesBonuses::BOMB, FRAME_BOMB);
	initializeBonusByType(__bonuses, TypesBonuses::CYCLE, FRAME_CYCLE);

	__gameState = GameState::PLAY;
	__totalCookiesCount = __field.countRemainingCookies();

	const sf::FloatRect titleBounds = __gameOverTitle.getLocalBounds();
	__gameOverTitle.setOrigin(0.5f * titleBounds.width, 0.5f * titleBounds.height);
}

void GameProcess::killBotsAndChangePosition()
{
	__ghosts.clear();
	__field.clearMap(SYMBOLS_GHOSTS, __field.__map);
	__field.randomizeMap(SYMBOLS_GHOSTS, __field.__map);

	std::ifstream file("text.json");
	json data = json::parse(file);
	file.close();
	int i = data["Start_game"][1];
	switch (i)
	{
	case 1:
		initializeGhostByID(__ghosts, GhostID::FIRST);
		break;
	case 2:
		initializeGhostByID(__ghosts, GhostID::FIRST);
		initializeGhostByID(__ghosts, GhostID::SECOND);
		break;
	case 3:
		initializeGhostByID(__ghosts, GhostID::FIRST);
		initializeGhostByID(__ghosts, GhostID::SECOND);
		initializeGhostByID(__ghosts, GhostID::THIRD);
		break;
	case 4:
		initializeGhostByID(__ghosts, GhostID::FIRST);
		initializeGhostByID(__ghosts, GhostID::SECOND);
		initializeGhostByID(__ghosts, GhostID::THIRD);
		initializeGhostByID(__ghosts, GhostID::FORTH);
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
	if (__packman.__eatenCookies == 50 && !__field.__changed) {
		changedBonusesPosition();
	}
	if (__packman.__eatenCookies == 51) {
		__field.__changed = false;
	}
	if (__packman.__eatenCookies == 100 && !__field.__changed) {
		changedBonusesPosition();
	}
	if (__packman.__eatenCookies == 101) {
		__field.__changed = false;
	}
	if (__packman.__eatenCookies == 150 && !__field.__changed) {
		changedBonusesPosition();
	}
	if (__packman.__eatenCookies == 151) {
		__field.__changed = false;
	}
	if (__packman.__eatenCookies == 200 && !__field.__changed) {
		changedBonusesPosition();
	}
	if (__packman.__eatenCookies == 201) {
		__field.__changed = false;
	}
}

void GameProcess::updateGameProcess(float elapsedTime, bool &flag_lifes, unsigned int lifes)
{

	if (__gameState == GameState::PLAY) {
		__packman.updateHero(elapsedTime, __field);

		redrawingBonuses();

		for (auto& pair : __ghosts) {
			pair.second.updateHero(elapsedTime, __field, 90.f);
		}

		const sf::FloatRect packmanBounds = __packman.getPackmanBounds();
		for ( auto& pair : __ghosts) {
			if (pair.second.__figure.getGlobalBounds().intersects(packmanBounds)) {
				if (lifes == 1) {
					__gameState = GameState::LOSE;
				}
				else
				{
					flag_lifes = true;
					__packman.__direction = __packman.changeOfDirection(__packman.__direction);
					__packman.__orientationDegrees = __packman.directionOrientationDegrees(__packman.__direction);
					pair.second.__direction = pair.second.changeOfDirection(pair.second.__direction);
					exit;
				}
			}
		}
		for (auto it = __packman.__activeBonuses.begin(); it != __packman.__activeBonuses.end(); ++it) {
			if (it->second.__bonusType == TypesBonuses::CYCLE && it->second.__active && __packman.__eatenCookies >= it->second.__eatenDots + 10) {
				__packman.setSpeedMultiplier(120.f);
				it->second.__active = false;
			}
		}

		for (auto it = __bonuses.begin(); it != __bonuses.end();) {
			if (it->second.__figure.getGlobalBounds().intersects(packmanBounds)) {
				if (it->second.__bonusType == TypesBonuses::BOMB) {
					it->second.__active = true;
					killBotsAndChangePosition();
				}
				if (it->second.__bonusType == TypesBonuses::CYCLE) {
					__packman.setSpeedMultiplier(240.f);
					it->second.__active = true;
					it->second.__eatenDots = __packman.__eatenCookies;
					__packman.__activeBonuses[it->first] = it->second;
				}
			}
			if (it->second.__bonusType == TypesBonuses::BOMB && it->second.__active) {
				it = __bonuses.erase(it);
				continue;
			}
			if (it->second.__bonusType == TypesBonuses::CYCLE && it->second.__active) {
				it = __bonuses.erase(it);
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
