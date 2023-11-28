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
	process.packman.initializePackman(process.packman);
	initializeGhostByID(process.ghosts, GhostID::FIRST);
	initializeGhostByID(process.ghosts, GhostID::SECOND);
	initializeGhostByID(process.ghosts, GhostID::THIRD);
	initializeGhostByID(process.ghosts, GhostID::FORTH);

	process.gameState = GameState::PLAY;
	process.totalCookiesCount = countRemainingCookies(process.field);

	process.gameOverBackground.setFillColor(sf::Color(200, 200, 200, 200));
	process.gameOverBackground.setSize(processSize);

	process.gameOverTitle.setFont(process.font);
	process.gameOverTitle.setFillColor(sf::Color::Black);
	process.gameOverTitle.setPosition(0.5f * processSize);
	process.gameOverTitle.setString("Game Over! BYE!!!");

	const sf::FloatRect titleBounds = process.gameOverTitle.getLocalBounds();
	process.gameOverTitle.setOrigin(0.5f * titleBounds.width, 0.5f * titleBounds.height);
}

void updateGameOverTitle(sf::Text& title, const std::string& text)
{
	title.setString(text);
	const sf::FloatRect titleBounds = title.getLocalBounds();
	title.setOrigin(0.5f * titleBounds.width, 0.5f * titleBounds.height);
}

void updateGameProcess(GameProcess& process, float elapsedTime)
{
	if (process.gameState == GameState::PLAY) {
		process.packman.updateHero(process.packman, elapsedTime, process.field, 220.f);

		for (auto& pair : process.ghosts) {
			pair.second.updateHero(pair.second, elapsedTime, process.field, 90.f);
		}

		const sf::FloatRect packmanBounds = process.packman.getPackmanBounds(process.packman);
		for (const auto& pair : process.ghosts) {
			if (pair.second.figure.getGlobalBounds().intersects(packmanBounds)) {
				process.gameState = GameState::LOSE;
			}
		}

		if (process.totalCookiesCount - process.packman.eatenCookies == 0) {
			updateGameOverTitle(process.gameOverTitle, "You WIN!!!");
			process.gameState = GameState::WIN;
		}
	}
}

std::string getGameProcessWindowTitle(const GameProcess& process)
{
	std::string title;
	static double cookiesLeft;
	int result;

	if (process.gameState == GameState::PLAY) {
		cookiesLeft = floor(static_cast<double>(process.packman.eatenCookies) / process.totalCookiesCount * 100);
		result = cookiesLeft;
		title = std::to_string(result) + '%';
	}
	if (process.gameState == GameState::WIN) {
		title = "You WIN! Nice =)";
		return title;
	}
	if (process.gameState == GameState::LOSE) {
		title = "YOU ARE LOSER!";
		return title;
	}
	return title;
}

void drawGameProcess(sf::RenderWindow& window, GameProcess& process)
{
	drawField(window, process.field);
	/*process.packman.drawHero(window, process.packman);*/
	process.packman.drawPackman(window, process.packman);

	for (auto& pair : process.ghosts) {
		pair.second.drawHero(window, pair.second);
	}

	if (process.gameState == GameState::LOSE || process.gameState == GameState::WIN) {
		window.draw(process.gameOverBackground);
		window.draw(process.gameOverTitle);
	}
}
