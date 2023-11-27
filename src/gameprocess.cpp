#include "gameprocess.h"

void initializeGhostByID(std::map<GhostID, Ghost>& ghosts, GhostID ghostID)
{
	Ghost& ghost = ghosts[ghostID];
	ghost.initializeHero(ghost, getGhostsStartPosition(ghostID), 20.f, sf::Color::Green);
}

void initializeGameProcess(GameProcess& process, const sf::Vector2f& processSize)
{
	bool succeed = process.font.loadFromFile("C:\\Users\\user\\Desktop\\font\\EightBits.ttf");

	if (!succeed) {
		assert(false);
		exit(1);
	}

	initializeField(process.field);
	process.packman.initializeHero(process.packman, getPackmanStartPosition(), 20.f, sf::Color::Yellow);
	initializeGhostByID(process.ghosts, GhostID::FIRST);
	initializeGhostByID(process.ghosts, GhostID::SECOND);
	initializeGhostByID(process.ghosts, GhostID::THIRD);
	initializeGhostByID(process.ghosts, GhostID::FORTH);

	process.gameOverBackground.setFillColor(sf::Color(200, 200, 200, 200));
	process.gameOverBackground.setSize(processSize);

	process.gameOverTitle.setFont(process.font);
	process.gameOverTitle.setFillColor(sf::Color::Black);
	process.gameOverTitle.setPosition(0.5f * processSize);
	process.gameOverTitle.setString("Game Over! BYE!!!");

	const sf::FloatRect titleBounds = process.gameOverTitle.getLocalBounds();
	process.gameOverTitle.setOrigin(0.5f * titleBounds.width, 0.5f * titleBounds.height);
}

void updateGameProcess(GameProcess& process, float elapsedTime)
{
	if (process.gameState == GameState::PLAY) {
		process.packman.updateHero(process.packman, elapsedTime, process.field, 200.f);

		for (auto& pair : process.ghosts) {
			pair.second.updateHero(pair.second, elapsedTime, process.field, 90.f);
		}

		const sf::FloatRect packmanBounds = process.packman.figure.getGlobalBounds();
		for (const auto& pair : process.ghosts) {
			if (pair.second.figure.getGlobalBounds().intersects(packmanBounds)) {
				process.gameState = GameState::LOSE;
			}
		}
	}
}

void drawGameProcess(sf::RenderWindow& window, GameProcess& process)
{
	drawField(window, process.field);
	process.packman.drawHero(window, process.packman);

	for (auto& pair : process.ghosts) {
		pair.second.drawHero(window, pair.second);
	}

	if (process.gameState == GameState::LOSE) {
		window.draw(process.gameOverBackground);
		window.draw(process.gameOverTitle);
	}
}
