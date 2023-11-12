#include "menu.h"
#include "gameselection.h"
#include "bots.h"
#include "maps.h"

using namespace sf;

void InitText(Text& mtext, float xpos, float ypos, String str, int size_font = 60,
    Color menuTextColor = Color::Yellow, int bord = 0, Color borderColor = Color::Blue);

void ChoseCountBots()
{
    RenderWindow Settings(VideoMode::getDesktopMode(), L"Settings", Style::Fullscreen);

    RectangleShape backgroundOpt(Vector2f(1920, 1080));
    Texture textureOpt;
    if (!textureOpt.loadFromFile("C:\\Users\\user\\Desktop\\image\\settings.png")) exit(2);

    backgroundOpt.setTexture(&textureOpt);
    while (Settings.isOpen())
    {
        Event eventOpt;
        while (Settings.pollEvent(eventOpt))
        {
            if (eventOpt.type == Event::Closed) Settings.close();
            if (eventOpt.type == Event::KeyPressed)
            {
                if (eventOpt.key.code == Keyboard::Escape) Settings.close();
            }
        }
        Settings.clear();
        Settings.draw(backgroundOpt);
        Settings.display();
    }
}

void GamеStart(RenderWindow& window, Font& font)
{
    RenderWindow Play(VideoMode::getDesktopMode(), L"Start Game", Style::Fullscreen);

    RectangleShape backgroundPlay(Vector2f(1920, 1080));

    Texture texturePlay;
    if (!texturePlay.loadFromFile("C:\\Users\\user\\Desktop\\image\\start-game.png")) exit(1);
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

    game::GameSelection myGameSelection(Play, 210, 320, 2, nameGameSelection, 90, 70);

    myGameSelection.setColorTextGameSelection(Color::Blue, Color::Yellow, Color::Black);

    myGameSelection.AlignGameSelection(2);

    String bots[]{ L"1",L"2",L"3",L"4" };

    game::Bots myBots(Play, 175, 650, 4, bots, 90, 70);

    myBots.setColorTextBots(Color::Blue, Color::Yellow, Color::Black);

    myBots.AlignBots(2);

    String maps[]{ L"1",L"2",L"3" };

    game::Maps myMaps(Play, 950, 725, 3, maps, 90, 70);

    myMaps.setColorTextMaps(Color::Blue, Color::Yellow, Color::Black);

    myMaps.AlignMaps(2);
    int countBots = 1;
    int page = 0;
    while (Play.isOpen())
    {
        Event eventPlay;
        while (Play.pollEvent(eventPlay))
        {
            switch (page)
            {
            case 0: 
                if (eventPlay.type == Event::KeyReleased)
                {
                    if (eventPlay.key.code == Keyboard::Left) { myGameSelection.MoveLeft(); }

                    if (eventPlay.key.code == Keyboard::Right) { myGameSelection.MoveRight(); }
                    if (eventPlay.key.code == Keyboard::Return)
                    {
                        page = 1;
                    }
                }
                break;
            case 1: 
                if (eventPlay.type == Event::KeyReleased)
                {
                    if (eventPlay.key.code == Keyboard::Left) { myBots.MoveLeft(); }
                    if (eventPlay.key.code == Keyboard::Right) { myBots.MoveRight(); }
                    if (eventPlay.key.code == Keyboard::Return)
                    {
                        page = 2;
                    }
                }
                break;
            case 2: 
                if (eventPlay.type == Event::KeyReleased)
                {
                    if (eventPlay.key.code == Keyboard::Left) { myMaps.MoveLeft(); }
                    if (eventPlay.key.code == Keyboard::Right) { myMaps.MoveRight(); }
                    if (eventPlay.key.code == Keyboard::Return)
                    {
                        
                    }
                }
                break;
            }
            if (eventPlay.type == Event::KeyPressed)
            {
                if (eventPlay.key.code == Keyboard::Escape) { Play.close(); }
            }
        }
        Play.clear();
        Play.draw(backgroundPlay);
        Play.draw(TitulStart);
        Play.draw(TitulGameSelection);
        Play.draw(TitulCountBots);
        Play.draw(TitulChoseMap);
        Play.draw(TitulStartGame);
        myGameSelection.draw();
        myBots.draw();
        myMaps.draw();
        Play.display();
    }
}

void Settings()
{
    RenderWindow Settings(VideoMode::getDesktopMode(), L"Settings", Style::Fullscreen);

    RectangleShape backgroundOpt(Vector2f(1920, 1080));
    Texture textureOpt;
    if (!textureOpt.loadFromFile("C:\\Users\\user\\Desktop\\image\\settings.png")) exit(2);

    backgroundOpt.setTexture(&textureOpt);
    while (Settings.isOpen())
    {
        Event eventOpt;
        while (Settings.pollEvent(eventOpt))
        {
            if (eventOpt.type == Event::Closed) Settings.close();
            if (eventOpt.type == Event::KeyPressed)
            {
                if (eventOpt.key.code == Keyboard::Escape) Settings.close();
            }
        }
        Settings.clear();
        Settings.draw(backgroundOpt);
        Settings.display();
    }
}

int main()
{
    RenderWindow window;

    window.create(VideoMode::getDesktopMode(), L"Packman", Style::Fullscreen);

    window.setMouseCursorVisible(false);

    double width = VideoMode::getDesktopMode().width;
    double height = VideoMode::getDesktopMode().height;

    RectangleShape background(Vector2f(width, height));
    
    Texture textureWindow;
    if (!textureWindow.loadFromFile("C:\\Users\\user\\Desktop\\image\\packman-menu.png")) return 4;
    background.setTexture(&textureWindow);

    Font font;
    if (!font.loadFromFile("C:\\Users\\user\\Desktop\\font\\EightBits.ttf")) return 5;
    
    String nameMenu[]{ L"Start",L"Settings",L"Exit" };

    game::Menu mymenu(window, 1400, 250, 3, nameMenu, 150, 160);
    
    mymenu.setColorTextMenu(Color::Blue, Color::Yellow, Color::Blue);
    
    mymenu.AlignMenu(2);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyReleased)
            {
                if (event.key.code == Keyboard::Up) { mymenu.MoveUp(); }
                
                if (event.key.code == Keyboard::Down) { mymenu.MoveDown(); }
                
                if (event.key.code == Keyboard::Return)
                {
                    switch (mymenu.getSelectedMenuNumber())
                    {
                    case 0:GamеStart(window, font);    break;
                    case 1:Settings();     break;
                    case 2:window.close(); break;
                    }
                }
            }
        }
        window.clear();
        window.draw(background);
        mymenu.draw();
        window.display();
    }
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