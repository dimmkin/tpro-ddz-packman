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

void GameProcess::initializeGameProcess(const sf::Vector2f& processSize, bool multiplayer)
{
	bool succeed = __font.loadFromFile("font/EightBits.ttf");

	__field.initializeField();
	if (multiplayer) {
		__packman1.initializePackman(__field, __packman1, 150.f, multiplayer, true);
		__packman2.initializePackman(__field, __packman2, 150.f, multiplayer);
	}
	else {
		__packman1.initializePackman(__field, __packman1, 150.f);
	}

	std::ifstream file("text.json");
	json data = json::parse(file);
	file.close();
	if (multiplayer) {
		initializeGhostByID(__ghosts, GhostID::FIRST);
		initializeGhostByID(__ghosts, GhostID::SECOND);
		initializeGhostByID(__ghosts, GhostID::THIRD);
		initializeGhostByID(__ghosts, GhostID::FORTH);
	}
	else {
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
	}

	initializeBonusByType(__bonuses, TypesBonuses::BOMB, FRAME_BOMB);
	initializeBonusByType(__bonuses, TypesBonuses::CYCLE, FRAME_CYCLE);

	__gameState = GameState::PLAY;
	__totalCookiesCount = __field.countRemainingCookies();

	const sf::FloatRect titleBounds = __gameOverTitle.getLocalBounds();
	__gameOverTitle.setOrigin(0.5f * titleBounds.width, 0.5f * titleBounds.height);
}

void GameProcess::killBotsAndChangePosition(bool multiplayer)
{
	__ghosts.clear();
	__field.clearMap(SYMBOLS_GHOSTS, __field.__map);
	__field.randomizeMap(SYMBOLS_GHOSTS, __field.__map);

	std::ifstream file("text.json");
	json data = json::parse(file);
	file.close();

	if (multiplayer ) {
		initializeGhostByID(__ghosts, GhostID::FIRST);
		initializeGhostByID(__ghosts, GhostID::SECOND);
		initializeGhostByID(__ghosts, GhostID::THIRD);
		initializeGhostByID(__ghosts, GhostID::FORTH);
	}
	else {
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
}

void GameProcess::changedBonusesPosition()
{
	__field.clearMap(SYMBOLS_BONUSES, __field.__map);
	__field.randomizeMap(SYMBOLS_BONUSES, __field.__map);
	initializeBonusByType(__bonuses, TypesBonuses::BOMB, FRAME_BOMB);
	initializeBonusByType(__bonuses, TypesBonuses::CYCLE, FRAME_CYCLE);
	__field.__changed = true;
}

void GameProcess::redrawingBonuses(bool multiplayer)
{
	if (multiplayer) {
		if ((__packman1.__eatenCookies + __packman2.__eatenCookies) == 50 && !__field.__changed) {
			changedBonusesPosition();
		}
		if ((__packman1.__eatenCookies + __packman2.__eatenCookies) == 51) {
			__field.__changed = false;
		}
		if ((__packman1.__eatenCookies + __packman2.__eatenCookies) == 100 && !__field.__changed) {
			changedBonusesPosition();
		}
		if ((__packman1.__eatenCookies + __packman2.__eatenCookies) == 101) {
			__field.__changed = false;
		}
		if ((__packman1.__eatenCookies + __packman2.__eatenCookies) == 150 && !__field.__changed) {
			changedBonusesPosition();
		}
		if ((__packman1.__eatenCookies + __packman2.__eatenCookies) == 151) {
			__field.__changed = false;
		}
		if ((__packman1.__eatenCookies + __packman2.__eatenCookies) == 200 && !__field.__changed) {
			changedBonusesPosition();
		}
		if ((__packman1.__eatenCookies + __packman2.__eatenCookies) == 201) {
			__field.__changed = false;
		}
	}
	else {
		if (__packman1.__eatenCookies == 50 && !__field.__changed) {
			changedBonusesPosition();
		}
		if (__packman1.__eatenCookies == 51) {
			__field.__changed = false;
		}
		if (__packman1.__eatenCookies == 100 && !__field.__changed) {
			changedBonusesPosition();
		}
		if (__packman1.__eatenCookies == 101) {
			__field.__changed = false;
		}
		if (__packman1.__eatenCookies == 150 && !__field.__changed) {
			changedBonusesPosition();
		}
		if (__packman1.__eatenCookies == 151) {
			__field.__changed = false;
		}
		if (__packman1.__eatenCookies == 200 && !__field.__changed) {
			changedBonusesPosition();
		}
		if (__packman1.__eatenCookies == 201) {
			__field.__changed = false;
		}
	}
}

void GameProcess::updateGameProcess(float elapsedTime, bool &flag_lifes, unsigned int lifes, bool stop, bool multiplayer)
{
	float localspeed_bonus = (stop) ? 0 : 250.f;
	float localspeed_multiplier = (stop) ? 0 : 150.f;
	float localspeed_ghost = (stop) ? 0 : 100.f;
	__packman1.__speed = (stop) ? 0 : __packman1.__speed;

	if(multiplayer) {
		__packman1.__speed = (stop) ? 0 : __packman1.__speed;
		__packman2.__speed = (stop) ? 0 : __packman2.__speed;
	}

	std::ifstream file("multiplayer_game.json");
    json user = json::parse(file);
    file.close();

	if (__gameState == GameState::PLAY) {
		__packman1.updateHero(elapsedTime, __field, stop);
		if (multiplayer) {
			__packman2.updateHero(elapsedTime, __field, stop, multiplayer);
		}

		redrawingBonuses(multiplayer);

		for (auto& pair : __ghosts) {
			pair.second.updateHero(elapsedTime, __field, localspeed_ghost, stop);
		}

		const sf::FloatRect packmanBounds1 = __packman1.getPackmanBounds();
		const sf::FloatRect packmanBounds2 = __packman2.getPackmanBounds();

		for ( auto& pair : __ghosts) {
			if (multiplayer) {
					if (pair.second.__figure.getGlobalBounds().intersects(packmanBounds1)) {
						unsigned int count = user["Game"][1];
						++count;
						user["Game"][1] = count;
						std::ofstream file_close("multiplayer_game.json");
						file_close << user;
    					file_close.close();
						__gameState = GameState::LOSE;
					}
					if (pair.second.__figure.getGlobalBounds().intersects(packmanBounds2)) {
						unsigned int count = user["Game"][0];
						++count;
						user["Game"][0] = count;
						std::ofstream file_close("multiplayer_game.json");
						file_close << user;
    					file_close.close();
						__gameState = GameState::LOSE;
					}
			}
			else  {
				if (pair.second.__figure.getGlobalBounds().intersects(packmanBounds1)) {
					if (lifes == 1) {
						__gameState = GameState::LOSE;
					}
					else
					{
						flag_lifes = true;
						__packman1.__direction = __packman1.changeOfDirection(__packman1.__direction);
						__packman1.__orientationDegrees = __packman1.directionOrientationDegrees(__packman1.__direction);
						pair.second.__direction = pair.second.changeOfDirection(pair.second.__direction);
						exit;
					}
				}
				
			}
			for (auto it = __packman1.__activeBonuses.begin(); it != __packman1.__activeBonuses.end(); ++it) {
				if (it->second.__bonusType == TypesBonuses::CYCLE && it->second.__active && __packman1.__eatenCookies >= it->second.__eatenDots + 10) {
					__packman1.setSpeedMultiplier(localspeed_multiplier);
					it->second.__active = false;
				}
			}
			for (auto it = __bonuses.begin(); it != __bonuses.end();) {
				if (it->second.__figure.getGlobalBounds().intersects(packmanBounds1)) {
					if (it->second.__bonusType == TypesBonuses::BOMB) {
						it->second.__active = true;
						killBotsAndChangePosition(multiplayer);
					}
					if (it->second.__bonusType == TypesBonuses::CYCLE) {
						__packman1.setSpeedMultiplier(localspeed_bonus);
						it->second.__active = true;
						it->second.__eatenDots = __packman1.__eatenCookies;
						__packman1.__activeBonuses[it->first] = it->second;
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

			if (__totalCookiesCount - (__packman1.__eatenCookies + __packman2.__eatenCookies) == 0) {
				__gameState = GameState::WIN;
			}
		}
		if (multiplayer) {
			const sf::FloatRect packmanBounds2 = __packman2.getPackmanBounds();
			for ( auto& pair : __ghosts) {
				if (pair.second.__figure.getGlobalBounds().intersects(packmanBounds2)) {
					if (lifes == 1) {
						__gameState = GameState::LOSE;
					}
					else
					{
						flag_lifes = true;
						__packman2.__direction = __packman2.changeOfDirection(__packman2.__direction);
						__packman2.__orientationDegrees = __packman2.directionOrientationDegrees(__packman2.__direction);
						pair.second.__direction = pair.second.changeOfDirection(pair.second.__direction);
						exit;
					}
				}
			}
			for (auto it = __packman2.__activeBonuses.begin(); it != __packman2.__activeBonuses.end(); ++it) {
				if (it->second.__bonusType == TypesBonuses::CYCLE && it->second.__active && __packman2.__eatenCookies >= it->second.__eatenDots + 10) {
					__packman2.setSpeedMultiplier(localspeed_multiplier);
					it->second.__active = false;
				}
			}

			for (auto it = __bonuses.begin(); it != __bonuses.end();) {
				if (it->second.__figure.getGlobalBounds().intersects(packmanBounds2)) {
					if (it->second.__bonusType == TypesBonuses::BOMB) {
						it->second.__active = true;
						killBotsAndChangePosition(multiplayer);
					}
					if (it->second.__bonusType == TypesBonuses::CYCLE) {
						__packman2.setSpeedMultiplier(localspeed_bonus);
						it->second.__active = true;
						it->second.__eatenDots = __packman2.__eatenCookies;
						__packman2.__activeBonuses[it->first] = it->second;
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

			if (__totalCookiesCount - __packman2.__eatenCookies == 0) {
				__gameState = GameState::WIN;
			}
		}
	}
}

std::string GameProcess::getGameProcessWindowTitle()
{
	std::string title;
	static double cookiesLeft;
	int result;

	if (__gameState == GameState::PLAY) {
		cookiesLeft = floor(static_cast<double>(__packman1.__eatenCookies) / __totalCookiesCount * 100);
		result = cookiesLeft;
		title = std::to_string(result) + '%';
	}
	return title;
}

void GameProcess::drawGameProcess(sf::RenderWindow& window, bool multiplayer)
{
	__field.drawField(window);
	__packman1.drawPackman(window);
	if (multiplayer) {
		__packman2.drawPackman(window);
	}

	for (auto& pair : __ghosts) {
		pair.second.drawHero(window);
	}

	for (auto& pair : __bonuses) {
		pair.second.drawBonus(window);
	}
}
