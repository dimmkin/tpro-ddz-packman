#include "../include/menuBase.h"
#include "../include/field.h"
#include "../include/gameprocess.h"
#include "../include/packman.h"
#include "../include/Music.h"
#include "../include/GameSelect.h"
#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>
using namespace sf;
#include "../json/nlohmann/json.hpp"
using json = nlohmann::json;

GameMusic Fon_music;
GameMusic Fon_Map_music;
bool stop = false;


void InitText(Text& mtext, float xpos, float ypos, String str, int size_font = 60,
    Color menuTextColor = Color::Yellow, int bord = 0, Color borderColor = Color::Blue);

void PlayGame(RenderWindow& window, Font& font, double width, double height, int RoundCounter = 1);

void GameStart(RenderWindow& window, Font& font, double width, double height);

void MainMenu(RenderWindow& window, Font& font, double width, double height);

void Pause(RenderWindow& window, Font& font, double width, double height)
{
    RectangleShape backgroundPlay(Vector2f(width, height));

    Texture texturePlay;
    if (!texturePlay.loadFromFile("image/pause.png")) exit(1);
    backgroundPlay.setTexture(&texturePlay);

    Text TitulPause;
    TitulPause.setFont(font);
    InitText(TitulPause, 800, -80, L"PAUSE", 200, Color::Yellow, 3, Color::Black);

    String namePause[]{ L"RESUME",L"RESTART",L"EXIT GAME" };

    game::Pause myPause(window, 950, 175, 3, namePause, 200, 200);

    myPause.setColorTextMenu(Color::Blue, Color::Yellow, Color::Blue);

    myPause.AlignMenu(2);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {

            Fon_music.Music_return(0);

            if (event.type == Event::KeyReleased)
            {
                if (event.key.code == Keyboard::Up) { myPause.MovePrev(); }

                if (event.key.code == Keyboard::Down) { myPause.MoveNext(); }

                if (event.key.code == Keyboard::Return)
                {
                    switch (myPause.getSelectedMenuNumber())
                    {
                    case 0: stop = false; return;                     break;
                    case 1:PlayGame(window, font, width, height);     break;
                    case 2:MainMenu(window, font, width, height);     break;
                    }
                }
            }
        }
        window.clear();
        window.draw(backgroundPlay);
        window.draw(TitulPause);
        myPause.draw();
        window.display();
    }
}

void EndGame(sf::RenderWindow& window, sf::Font& font, double width, double height, GameProcess& process, unsigned int scores)
{
    sf::RectangleShape backgrounGameOver(sf::Vector2f(width, height));

    sf::Texture textureGameOver;
    if (!textureGameOver.loadFromFile("image/exit.png")) exit(1);
    backgrounGameOver.setTexture(&textureGameOver);

    sf::Text TitulGameOver;
    TitulGameOver.setFont(font);
    InitText(TitulGameOver, 725, 200, L"GAME OVER", 150, sf::Color::Yellow, 3, sf::Color::Blue);
    
    sf::Text TitulGameWon;
    TitulGameWon.setFont(font);
    InitText(TitulGameWon, 600, 200, L"CONGRATULATION!", 150, sf::Color::Yellow, 3, sf::Color::Blue);

    sf::Text TitulFirstPlayerForGameOver;
    TitulFirstPlayerForGameOver.setFont(font);
    InitText(TitulFirstPlayerForGameOver, 550, 350, L"Player 1", 90, sf::Color::Yellow, 3, sf::Color::Blue);

    sf::Text TitulFirstPlayerForGameWon;
    TitulFirstPlayerForGameWon.setFont(font);
    InitText(TitulFirstPlayerForGameWon, 750, 400, L"Player 1", 140, sf::Color::Yellow, 3, sf::Color::Blue);

    sf::Text TitulScores;
    TitulScores.setFont(font);
    InitText(TitulScores, 550, 500, L"SCORES: " + std::to_string(scores) + "%", 90, sf::Color::Yellow, 3, sf::Color::Blue);

    sf::String nameEndGame[]{ L"RESTART",L"EXIT" };

    game::EndGame myEndGame(window, 800, 625, 2, nameEndGame, 150, 350);

    myEndGame.setColorTextMenu(sf::Color::Blue, sf::Color::Yellow, sf::Color::Blue);

    myEndGame.AlignMenu(2);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Left) { myEndGame.MovePrev(); }

                if (event.key.code == sf::Keyboard::Right) { myEndGame.MoveNext(); }

                if (event.key.code == sf::Keyboard::Return)
                {
                    switch (myEndGame.getSelectedMenuNumber())
                    {
                    case 0:PlayGame(window, font, width, height, 1);     break;
                    case 1:MainMenu(window, font, width, height);     break;
                    }
                }
            }
        }
        window.clear();
        window.draw(backgrounGameOver);
        if (process.__gameState == GameState::LOSE) {
            window.draw(TitulGameOver);
            window.draw(TitulScores);
            window.draw(TitulFirstPlayerForGameOver);
        }
        if (process.__gameState == GameState::WIN) {
            window.draw(TitulGameWon);
            window.draw(TitulFirstPlayerForGameWon);
        }
        myEndGame.draw();
        window.display();
    }
}

void PlayGame(RenderWindow& window, Font& font, double width, double height, int RoundCounter)
{
    RectangleShape backgroundPlay(Vector2f(width, height));

    std::ifstream file("text.json");
    json data = json::parse(file);
    file.close();
    std::string gameSelect = data["Start_game"][0];

    std::string Round = "";

    Texture texturePlay;
    if (!texturePlay.loadFromFile("image/play-game.png")) exit(1);
    backgroundPlay.setTexture(&texturePlay);

    bool isFirstMusic = true;
    Text TitulRounds;
    TitulRounds.setFont(font);

    GameSelect game;
    if(game.isClassic(gameSelect)){
        Round = game.CurrentRound(RoundCounter);
        isFirstMusic = (RoundCounter == 1) ? true : false; 
        InitText(TitulRounds, 690, -80, Round, 200, Color::Yellow, 3, Color::Black);
    }
    else {
        Round = game.CurrentRound(0);
        isFirstMusic = false;
        InitText(TitulRounds, 690, -80, Round, 200, Color::Yellow, 3, Color::Black);
    }

    Text TitulPackman;
    TitulPackman.setFont(font);
    InitText(TitulPackman, 750, 840, L"PACKMAN", 200, Color::Yellow, 3, Color::Black);

    Text TitulFirstPlayer;
    TitulFirstPlayer.setFont(font);
    InitText(TitulFirstPlayer, 150, 150, L"Player 1", 100, Color::Yellow, 3, Color::Blue);

    std::string name_user = data["Option"][2];
    Text NikName1;
    NikName1.setString(name_user);
    Text TitulFirstNick;
    TitulFirstNick.setFont(font);
    InitText(TitulFirstNick, 120, 250, NikName1.getString(), 90, Color::Yellow, 3, Color::Blue);
    RectangleShape heats1(Vector2f(100, 100));
    Texture heats_image1;
    if (!heats_image1.loadFromFile("image/lifes.png")) exit(23);
    heats1.setTexture(&heats_image1);
    heats1.setPosition(110, 400);
    std::string heat_file_count = data["Option"][1];
    std::string heat_panel1 = "x" + heat_file_count;
    Text heat_text;
    heat_text.setString(heat_panel1);
    unsigned int lifes = std::stoi(heat_file_count);

    Text Heats_Count;
    Heats_Count.setFont(font);
    InitText(Heats_Count, 250, 380, heat_text.getString(), 90, Color::Yellow, 3, Color::Blue);

    Text TitulFirstScore;
    TitulFirstScore.setFont(font);
    InitText(TitulFirstScore, 75, 500, L"Score: ", 80, Color::Yellow, 3, Color::Blue);

    Text TitulSecondPlayer;
    TitulSecondPlayer.setFont(font);
    InitText(TitulSecondPlayer, 1550, 150, L"Player 2", 100, Color::Yellow, 3, Color::Blue);

    Text TitulSecondNick;
    TitulSecondNick.setFont(font);
    InitText(TitulSecondNick, 1520, 250, L"Nickname 2", 90, Color::Yellow, 3, Color::Blue);

    Text TitulSecondScore;
    TitulSecondScore.setFont(font);
    InitText(TitulSecondScore, 1475, 500, L"Score: ", 80, Color::Yellow, 3, Color::Blue);

    sf::Clock clock;
    GameProcess process;

    process.initializeGameProcess(sf::Vector2f(window.getSize()));


    sf::Text countdownText;
    countdownText.setFont(font);
    InitText(countdownText, 1475, 500, L"Score: ", 150, Color::Yellow, 3, Color::Blue);

    bool isStart = true;
    GameMusic music;
    Fon_music.Music_pause(0);
    music.Music_stop_all();
    int index = music.Random_music();

    unsigned stek = lifes;
    bool flag = false;
    int music_count = 0;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Escape) {
                    Fon_Map_music.Music_pause_all();
                    music.Music_pause_all();
                    stop = true;
                }
            }
        }

        if (isStart) {

            countdownText.setString(Round);
            sf::FloatRect textBounds = countdownText.getLocalBounds();
            countdownText.setPosition((window.getSize().x - textBounds.width) / 2,
                ((window.getSize().y - textBounds.height) / 2) - 65);
            window.clear();
            window.draw(backgroundPlay);
            window.draw(TitulRounds);
            window.draw(TitulPackman);
            window.draw(TitulFirstPlayer);
            window.draw(TitulFirstNick);
            window.draw(TitulFirstScore);
            window.draw(TitulSecondPlayer);
            window.draw(TitulSecondNick);
            window.draw(TitulSecondScore);
            window.draw(countdownText);
            window.display();

            std::this_thread::sleep_for(std::chrono::seconds(1));

            music.Music_play(1);
            music.Music_set_volume_all(10);

            for (int i = 3; i >= 0; --i) {
                countdownText.setString(std::to_string(i));

                sf::FloatRect textBounds = countdownText.getLocalBounds();
                countdownText.setPosition((window.getSize().x - textBounds.width) / 2,
                    ((window.getSize().y - textBounds.height) / 2) - 65);

                if (i == 0) {
                    countdownText.setString("Start!");
                    sf::FloatRect textBounds = countdownText.getLocalBounds();
                    countdownText.setPosition((window.getSize().x - textBounds.width) / 2,
                        ((window.getSize().y - textBounds.height) / 2) - 65);
                    window.clear();
                    window.draw(backgroundPlay);
                    window.draw(TitulRounds);
                    window.draw(TitulPackman);
                    window.draw(TitulFirstPlayer);
                    window.draw(TitulFirstNick);
                    window.draw(TitulFirstScore);
                    window.draw(TitulSecondPlayer);
                    window.draw(TitulSecondNick);
                    window.draw(TitulSecondScore);
                    window.draw(countdownText);
                    window.display();

                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    break;
                }
                window.clear();
                window.draw(backgroundPlay);
                window.draw(TitulRounds);
                window.draw(TitulPackman);
                window.draw(TitulFirstPlayer);
                window.draw(TitulFirstNick);
                window.draw(TitulFirstScore);
                window.draw(TitulSecondPlayer);
                window.draw(TitulSecondNick);
                window.draw(TitulSecondScore);
                window.draw(countdownText);
                window.display();

                std::this_thread::sleep_for(std::chrono::seconds(1));
                isStart = false;
            }
        }
        Fon_Map_music.Music_play_Map(isFirstMusic, index);
        Fon_Map_music.Music_set_volume_all(20);

        if (process.__gameState == GameState::LOSE) {
            music.Music_stop_all();
            Fon_Map_music.Music_stop_all();
            Fon_music.Music_return(0);
            unsigned int scores = floor(static_cast<double>(process.__packman.__eatenCookies) / process.__totalCookiesCount * 100);
            EndGame(window, font, width, height, process, scores);
        }

        if (process.__gameState == GameState::WIN) {
            ++RoundCounter;
            if((game.isClassic(gameSelect) && RoundCounter > 3) || !game.isClassic(gameSelect))
            {
                music.Music_stop_all();
                Fon_Map_music.Music_stop_all();
                Fon_music.Music_return(0);
                unsigned int scores = floor(static_cast<double>(process.__packman.__eatenCookies) / process.__totalCookiesCount * 100);
                EndGame(window, font, width, height, process, scores);
            }
            else {
                Fon_Map_music.Music_stop_all();
                PlayGame(window, font, width, height, RoundCounter);
            }
        }

        Text Scores;
        Scores.setFont(font);
        InitText(Scores, 225, 500, process.getGameProcessWindowTitle(), 80, Color::Yellow, 3, Color::Blue);

        const float elapsedTime = clock.getElapsedTime().asSeconds();

        if (flag) {
            --lifes;
            std::string heat_panel1 = "x" + std::to_string(lifes);
            heat_text.setString(heat_panel1);
            stek = lifes;
            InitText(Heats_Count, 250, 380, heat_text.getString(), 90, Color::Yellow, 3, Color::Blue);
            flag = false;

        }

        clock.restart();
        window.clear();
        window.draw(backgroundPlay);
        window.draw(TitulRounds);
        window.draw(TitulPackman);
        window.draw(TitulFirstPlayer);
        window.draw(TitulFirstNick);
        window.draw(TitulFirstScore);
        window.draw(TitulSecondPlayer);
        window.draw(TitulSecondNick);
        window.draw(TitulSecondScore);
        window.draw(heats1);
        window.draw(Heats_Count);
        process.updateGameProcess(elapsedTime, flag, lifes, stop);
        process.drawGameProcess(window);
        window.draw(Scores);
        window.display();
        if (stop) {
            process.updateGameProcess(elapsedTime, flag, lifes, true);
            Pause(window, font, width, height); 
        }
    }
}
void GameStart(RenderWindow& window, Font& font, double width, double height)
{
    RectangleShape backgroundPlay(Vector2f(width, height));

    Texture texturePlay;
    if (!texturePlay.loadFromFile("image/start-game.png")) exit(1);
    backgroundPlay.setTexture(&texturePlay);

    Text TitulStart;
    TitulStart.setFont(font);
    InitText(TitulStart, 800, -80, L"GAME", 200, Color::Yellow, 3, Color::Black);

    Text TitulGameSelection;
    TitulGameSelection.setFont(font);
    InitText(TitulGameSelection, 150, 200, L"GAME SELECTION", 100, Color::Yellow, 3, Color::Blue);

    Text TitulCountBots;
    TitulCountBots.setFont(font);
    InitText(TitulCountBots, 200, 535, L"COUNT BOTS", 100, Color::Yellow, 3, Color::Blue);

    Text TitulChoseMap;
    TitulChoseMap.setFont(font);
    InitText(TitulChoseMap, 1025, 140, L"CHOSE MAP", 200, Color::Yellow, 3, Color::Blue);

    Text TitulStartGame;
    TitulStartGame.setFont(font);
    InitText(TitulStartGame, 775, 840, L"START", 200, Color::Yellow, 3, Color::Black);

    String nameGameSelection[]{ L"Classic",L"Fast Game" };

    game::GameSelection myGameSelection(window, 210, 320, 2, nameGameSelection, 90, 270);

    myGameSelection.setColorTextMenu(Color::Blue, Color::Yellow, Color::Black);

    myGameSelection.AlignMenu(2);

    String bots[]{ L"1",L"2",L"3",L"4" };

    game::ChoseBots myBots(window, 175, 650, 4, bots, 90, 120);

    myBots.setColorTextMenu(Color::Blue, Color::Yellow, Color::Black);

    myBots.AlignMenu(2);

    String maps[]{ L"1",L"2",L"3" };

    game::Maps myMaps(window, 950, 725, 3, maps, 90, 370);

    myMaps.setColorTextMenu(Color::Blue, Color::Yellow, Color::Black);



    // Button map
    Texture map1_picture;
    if (!map1_picture.loadFromFile("image/Map_1.png")) exit(1);

    Texture map2_picture;
    if (!map2_picture.loadFromFile("image/Map_2.png")) exit(1);

    Texture map3_picture;
    if (!map3_picture.loadFromFile("image/Map_3.png")) exit(1);

    Sprite map1_button_sprite(map1_picture);
    Sprite map2_button_sprite(map2_picture);
    Sprite map3_button_sprite(map3_picture);

    float scaleFactorX = 0.405f;
    float scaleFactorY = 0.45f;
    map1_button_sprite.setScale(scaleFactorX, scaleFactorY);
    map2_button_sprite.setScale(scaleFactorX, scaleFactorY);
    map3_button_sprite.setScale(scaleFactorX, scaleFactorY);

    sf::Vector2u windowSize = window.getSize();
    float button1X = windowSize.x - map1_picture.getSize().x - 305;
    float button1Y = windowSize.y - map1_picture.getSize().y + 55;

    float button2X = windowSize.x - map2_picture.getSize().x + 65;
    float button2Y = windowSize.y - map2_picture.getSize().y + 55;

    float button3X = windowSize.x - map3_picture.getSize().x + 438;
    float button3Y = windowSize.y - map3_picture.getSize().y + 55;

    map1_button_sprite.setPosition(button1X, button1Y);
    map2_button_sprite.setPosition(button2X, button2Y);
    map3_button_sprite.setPosition(button3X, button3Y);



    std::ifstream file("text.json");
    json data = json::parse(file);
    data["Start_game"].clear();
    file.close();

    myMaps.AlignMenu(2);
    int countBots = 1;
    int page = 0;
    while (window.isOpen())
    {
        Event eventPlay;
        while (window.pollEvent(eventPlay))
        {
            switch (page)
            {
            case 0:
                if (eventPlay.type == Event::KeyReleased)
                {
                    if (eventPlay.key.code == Keyboard::Left) { myGameSelection.MovePrev(); }

                    if (eventPlay.key.code == Keyboard::Right) { myGameSelection.MoveNext(); }
                    if (eventPlay.key.code == Keyboard::Return)
                    {
                        std::string str = "";
                        if (myGameSelection.getSelectedMenuNumber() == 0) {
                            str = "Classic";
                        }
                        else {
                            str = "Fast Game";
                        }
                        data["Start_game"].push_back(str);
                        page = 1;
                    }
                }
                break;
            case 1:
                if (eventPlay.type == Event::KeyReleased)
                {
                    if (eventPlay.key.code == Keyboard::Left) { myBots.MovePrev(); }
                    if (eventPlay.key.code == Keyboard::Right) { myBots.MoveNext(); }
                    if (eventPlay.key.code == Keyboard::Return)
                    {

                        data["Start_game"].push_back(myBots.getSelectedMenuNumber() + 1);
                        page = 2;
                    }
                }
                break;
            case 2:
                if (eventPlay.type == Event::KeyReleased)
                {
                    if (eventPlay.key.code == Keyboard::Left) { myMaps.MovePrev(); }
                    if (eventPlay.key.code == Keyboard::Right) { myMaps.MoveNext(); }
                    if (eventPlay.key.code == Keyboard::Return)
                    {
                        data["Start_game"].push_back(myMaps.getSelectedMenuNumber());
                        std::ofstream file("text.json");
                        file << data;
                        file.close();
                        Fon_music.Music_pause(0);
                        PlayGame(window, font, width, height, 1);
                    }
                }
                break;
            }
            if (eventPlay.type == Event::KeyPressed)
            {
                if (eventPlay.key.code == Keyboard::Escape) { MainMenu(window, font, 1920, 1080); }
            }
        }
        window.clear();
        window.draw(backgroundPlay);
        window.draw(TitulStart);
        window.draw(TitulGameSelection);
        window.draw(TitulCountBots);
        window.draw(TitulChoseMap);
        window.draw(TitulStartGame);
        window.draw(map1_button_sprite);
        window.draw(map2_button_sprite);
        window.draw(map3_button_sprite);
        myGameSelection.draw();
        myBots.draw();
        myMaps.draw();
        window.display();
    }
}
void Settings(sf::RenderWindow& window, sf::Font& font, double width, double height)
{
    RectangleShape backgroundOpt(Vector2f(width, height));

    Texture textureOpt;
    if (!textureOpt.loadFromFile("image/settings.png")) exit(2);
    backgroundOpt.setTexture(&textureOpt);

    RectangleShape heats(Vector2f(150, 150));
    Texture heats_image;
    if (!heats_image.loadFromFile("image/lifes.png")) exit(23);
    heats.setTexture(&heats_image);
    heats.setPosition(100, 700);

    Text Titul, SettingsMenu1, SettingsMenu2, Save, Arrow;
    SettingsMenu1.setFont(font);
    SettingsMenu2.setFont(font);
    Titul.setFont(font);
    Save.setFont(font);

    Arrow.setFont(font);

    InitText(Titul, 780, -30, "Settings", 150, Color::Yellow, 3, Color::Black);
    InitText(SettingsMenu1, 300, 150, "Management", 100, Color::Yellow, 3, Color::Black);
    InitText(SettingsMenu2, 1400, 150, "Game", 100, Color::Yellow, 3, Color::Black);
    InitText(Save, 830, 840, L"SAVE", 200, Color::Blue, 3, Color::Black);

    InitText(Arrow, 375, 730, L"<      >", 70, Color::Yellow, 3, Color::Black);
    String ManagementCount[]{ L"1",L"2" };

    game::Settings Management(window, 260, 550, 2, ManagementCount, 90, 430);

    Management.setColorTextMenu(Color::Blue, Color::Yellow, Color::Black);

    Management.AlignMenu(2);

    String name_user[]{ L"Name :" };
    game::Settings Name(window, 1150, 340, 1, name_user, 90);

    Name.setColorTextMenu(Color::Blue, Color::Yellow, Color::Black);

    Name.AlignMenu(2);

    String color_menu[]{ L"Color :" };
    game::Settings Color(window, 1150, 560, 1, color_menu, 90);

    Color.setColorTextMenu(Color::Blue, Color::Yellow, Color::Black);

    Color.AlignMenu(2);

    String Color_count[]{ L"1",L"2", L"3" };

    game::Settings Color_name(window, 1450, 700, 3, Color_count, 90, 150);

    Color_name.setColorTextMenu(Color::Blue, Color::Yellow, Color::Black);

    std::ifstream file("text.json");
    json data = json::parse(file);
    data["Option"].clear();
    file.close();

    Text message("", font, 20);
    Text heat("1", font, 20);
    int page = 0;
    int count = 1;
    if (count == 1) {
        InitText(heat, 450, 700, heat.getString(), 100, Color::Yellow, 3, Color::Black);
    }

    while (window.isOpen())
    {
        Event eventOpt;
        while (window.pollEvent(eventOpt))
        {
            switch (page)
            {
            case 0:
                if (eventOpt.type == Event::KeyReleased)
                {
                    if (eventOpt.key.code == Keyboard::Left) { Management.MovePrev(); }

                    if (eventOpt.key.code == Keyboard::Right) { Management.MoveNext(); }
                    if (eventOpt.key.code == Keyboard::Return)
                    {
                        data["Option"].push_back(Management.getSelectedMenuNumber() + 1);
                        page = 1;
                    }
                }
                break;
            case 1 :

                if (eventOpt.type == Event::KeyReleased)
                {
                    String heat_count = heat.getString();
                    
                    if (eventOpt.key.code == Keyboard::Left) {
                        if ((count - 1) >= 1) {
                            std::string compare = std::to_string(--count);
                            heat.setString(compare);
                        }
                        InitText(heat, 450, 700, heat.getString(), 100, Color::Yellow, 3, Color::Black);
                    }

                    if (eventOpt.key.code == Keyboard::Right) {
                        if ( (count + 1) <= 5) {
                            std::string compare = std::to_string(++count);
                            heat.setString(compare);
                        }
                        InitText(heat, 450, 700, heat.getString(), 100, Color::Yellow, 3, Color::Black);
                    }
                    
                    if (eventOpt.key.code == Keyboard::Return)
                    {
                        data["Option"].push_back(heat.getString());
                        page = 2;
                    }
                }
                break;
            case 2:
                if (eventOpt.type == Event::TextEntered)
                {
                    std::string text = message.getString();
                    int digit = eventOpt.text.unicode;
                    if (text.length() < 12) {
                        message.setString(text + (char)(digit));
                    }
                    if (digit == 57) {
                        message.setString(text + '9');
                    }
                    if (digit == 8) {
                        message.setString(text.substr(0, text.length() - 1));
                    }
                    InitText(message, 1395, 320, message.getString(), 100, Color::Blue, 3, Color::Black);
                }
                if (eventOpt.type == Event::KeyReleased)
                {
                    if (eventOpt.key.code == Keyboard::Return)
                    {
                        data["Option"].push_back(message.getString());
                        page = 3;
                    }
                }
                break;
            case 3:
                if (eventOpt.type == Event::KeyReleased)
                {
                    if (eventOpt.key.code == Keyboard::Left) { Color_name.MovePrev(); }
                    if (eventOpt.key.code == Keyboard::Right) { Color_name.MoveNext(); }
                    if (eventOpt.key.code == Keyboard::Return)
                    {

                        data["Option"].push_back(Color_name.getSelectedMenuNumber() + 1);
                        std::ofstream file("text.json");
                        file << data;
                        file.close();
                        MainMenu(window, font, 1920, 1080);
                    }
                }
                break;
            };

            if (eventOpt.type == Event::KeyPressed)
            {
                if (eventOpt.key.code == Keyboard::Escape) { MainMenu(window, font, 1920, 1080); }
            }
        }
        window.clear();
        window.draw(backgroundOpt);
        window.draw(heats);
        window.draw(Titul);
        window.draw(SettingsMenu1);
        window.draw(SettingsMenu2);
        window.draw(Save);
        window.draw(Arrow);
        window.draw(message);
        window.draw(heat);
        Name.draw();
        Color.draw();
        Color_name.draw();
        Management.draw();
        window.display();
    }
}

void Exit(RenderWindow& window, Font& font, double width, double height)
{
    RectangleShape backgroundExit(Vector2f(width, height));

    Texture textureExit;
    if (!textureExit.loadFromFile("image/exit.png")) exit(1);
    backgroundExit.setTexture(&textureExit);

    Text TitulExit;
    TitulExit.setFont(font);
    InitText(TitulExit, 525, 250, L"ARE YOU SURE?", 200, Color::Yellow, 3, Color::Blue);

    String nameExit[]{ L"YES",L"NO" };

    game::Exit myExit(window, 775, 450, 2, nameExit, 200, 300);

    myExit.setColorTextMenu(Color::Blue, Color::Yellow, Color::Blue);

    myExit.AlignMenu(2);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyReleased)
            {
                if (event.key.code == Keyboard::Left) { myExit.MovePrev(); }

                if (event.key.code == Keyboard::Right) { myExit.MoveNext(); }

                if (event.key.code == Keyboard::Return)
                {
                    switch (myExit.getSelectedMenuNumber())
                    {
                    case 0:window.close();                        break;
                    case 1:MainMenu(window, font, width, height); break;
                    }
                }
            }
        }
        window.clear();
        window.draw(backgroundExit);
        window.draw(TitulExit);
        myExit.draw();
        window.display();
    }
}

void MultiplayerMenu(RenderWindow& window, Font& font, double width, double height)
{
    RectangleShape background(Vector2f(width, height));

    Texture textureWindow;
    if (!textureWindow.loadFromFile("image/multiplayer-menu.png")) exit(1);
    background.setTexture(&textureWindow);

    Text TitulMultiplayer;
    TitulMultiplayer.setFont(font);
    InitText(TitulMultiplayer, 600, -80, L"MULTIPLAYER", 200, Color::Yellow, 3, Color::Black);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
           if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Escape) { MainMenu(window, font, 1920, 1080); }
            }
        }
        window.clear();
        window.draw(background);
        window.draw(TitulMultiplayer);
        window.display();
    }
}

void MainMenu(RenderWindow& window, Font& font, double width, double height)
{
    RectangleShape background(Vector2f(width, height));

    Texture textureWindow;
    if (!textureWindow.loadFromFile("image/packman-menu.png")) exit(1);
    background.setTexture(&textureWindow);

    String nameMenu[]{ L"START", L"MULTIPLAYER", L"SETTINGS",L"EXIT" };

    game::Menu mymenu(window, 1400, 190, 4, nameMenu, 150, 160);

    mymenu.setColorTextMenu(Color::Blue, Color::Yellow, Color::Blue);

    mymenu.AlignMenu(2);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyReleased)
            {
                if (event.key.code == Keyboard::Up) { mymenu.MovePrev(); }

                if (event.key.code == Keyboard::Down) { mymenu.MoveNext(); }

                if (event.key.code == Keyboard::Return)
                {
                    switch (mymenu.getSelectedMenuNumber())
                    {
                    case 0:GameStart(window, font, width, height);       break;
                    case 1:MultiplayerMenu(window, font, width, height); break;
                    case 2:Settings(window, font, width, height);        break;
                    case 3:Exit(window, font, width, height);            break;
                    }
                }
            }
        }
        window.clear();
        window.draw(background);
        mymenu.draw();
        window.display();
    }
}

int main()
{
    std::ifstream file_open("text.json");
    json data = json::parse(file_open);
    data["Start_game"] = { "Classic", 1, 1 };
    data["Option"] = { 1, "1","User",1 };
    file_open.close();
    std::ofstream file_close("text.json");
    file_close << data;
    file_close.close();

    RenderWindow window;

    Fon_music.Music_stop(0);
    Fon_music.Music_play(0);
    Fon_music.Music_set_volume_all(10);

    window.create(VideoMode::getDesktopMode(), L"Packman", Style::Fullscreen);

    window.setMouseCursorVisible(false);

    double width = VideoMode::getDesktopMode().width;
    double height = VideoMode::getDesktopMode().height;

    Font font;
    if (!font.loadFromFile("font/EightBits.ttf")) return 5;

    MainMenu(window, font, width, height);

    return 0;
}

void InitText(Text& mtext, float xpos, float ypos, String str, int size_font,
   Color menu_text_color, int bord, Color border_color)
{
   mtext.setCharacterSize(size_font);
   mtext.setPosition(xpos, ypos);
   mtext.setString(str);
   mtext.setFillColor(menu_text_color);
   mtext.setOutlineThickness(bord);
   mtext.setOutlineColor(border_color);
}