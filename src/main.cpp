#include "menuBase.h"

using namespace sf;

void InitText(Text& mtext, float xpos, float ypos, String str, int size_font = 60,
    Color menuTextColor = Color::Yellow, int bord = 0, Color borderColor = Color::Blue);

void MainMenu(sf::RenderWindow& window, sf::Font& font, double width, double height);

void GamåStart(RenderWindow& window, Font& font)
{
    RenderWindow Play(VideoMode::getDesktopMode(), L"Start Game", Style::Fullscreen);

    RectangleShape backgroundPlay(Vector2f(1920, 1080));

    Texture texturePlay;
    if (!texturePlay.loadFromFile("image/start.png")) exit(1);
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

    game::GameSelection myGameSelection(Play, 210, 320, 2, nameGameSelection, 90, 270);

    myGameSelection.setColorTextMenu(Color::Blue, Color::Yellow, Color::Black);

    myGameSelection.AlignMenu(2);

    String bots[]{ L"1",L"2",L"3",L"4" };

    game::ChoseBots myBots(Play, 175, 650, 4, bots, 90, 120);

    myBots.setColorTextMenu(Color::Blue, Color::Yellow, Color::Black);

    myBots.AlignMenu(2);

    String maps[]{ L"1",L"2",L"3" };

    game::Maps myMaps(Play, 950, 725, 3, maps, 90, 370);

    myMaps.setColorTextMenu(Color::Blue, Color::Yellow, Color::Black);

    myMaps.AlignMenu(2);
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
                    if (eventPlay.key.code == Keyboard::Left) { myGameSelection.MovePrev(); }

                    if (eventPlay.key.code == Keyboard::Right) { myGameSelection.MoveNext(); }
                    if (eventPlay.key.code == Keyboard::Return)
                    {
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

void Option(sf::RenderWindow& window, sf::Font& font)
{
    RectangleShape backgroundOpt(Vector2f(1920, 1080));
    Texture textureOpt;
    if (!textureOpt.loadFromFile("image/settings.jpg")) exit(2);
    backgroundOpt.setTexture(&textureOpt);

    Text Titul, SettingsMenu1, SettingsMenu2, Save;
    SettingsMenu1.setFont(font);
    SettingsMenu2.setFont(font);
    Titul.setFont(font);
    Save.setFont(font);


    InitText(Titul, 780, -30, "Settings", 150, Color::Yellow, 3, Color::Black);
    InitText(SettingsMenu1, 300, 150, "Management", 100, Color::Yellow, 3, Color::Black);
    InitText(SettingsMenu2, 1400, 150, "Game", 100, Color::Yellow, 3, Color::Black);
    InitText(Save, 830, 840, L"SAVE", 200, Color::Blue, 3, Color::Black);

    String ManagementCount[]{ L"1",L"2" };

    game::Settigns Management(window, 260, 550, 2, ManagementCount,90, 430);

    Management.setColorTextMenu(Color::Blue, Color::Yellow, Color::Black);

    Management.AlignMenu(2);

    String name_user[]{ L"Name :"};
    game::Settigns Name(window, 1150, 340, 1,name_user, 90);

    Name.setColorTextMenu(Color::Blue, Color::Yellow, Color::Black);

    Name.AlignMenu(2);

    String color_menu[]{ L"Color :" };
    game::Settigns Color(window, 1150, 560, 1, color_menu, 90);

    Color.setColorTextMenu(Color::Blue, Color::Yellow, Color::Black);

    Color.AlignMenu(2);

    String Color_count[]{ L"1",L"2", L"3"};

    game::Settigns Color_name(window, 1450, 700, 3, Color_count, 90, 150);

    Color_name.setColorTextMenu(Color::Blue, Color::Yellow, Color::Black);

    Color_name.AlignMenu(2);

    Text message("", font, 20);
    int page = 0;
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
                        page = 1;
                    }
                }
                break;
            case 1:
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
                        page = 2;
                    }
                }
                break;
            case 2:
                 if (eventOpt.type == Event::KeyReleased)
                 {
                     if (eventOpt.key.code == Keyboard::Left) { Color_name.MovePrev(); }
                     if (eventOpt.key.code == Keyboard::Right) { Color_name.MoveNext(); }
                     if (eventOpt.key.code == Keyboard::Return)
                     {
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
        window.draw(Titul);
        window.draw(SettingsMenu1);
        window.draw(SettingsMenu2);
        window.draw(Save);
        window.draw(message);
        Name.draw();
        Color.draw();
        Color_name.draw();
        Management.draw();
        window.display();
    }
}

void MainMenu(sf::RenderWindow& window, sf::Font& font, double width, double height)
{
    RectangleShape background(Vector2f(width, height));

    Texture textureWindow;
    if (!textureWindow.loadFromFile("image/start.jpg")) exit(1);
    background.setTexture(&textureWindow);

    String nameMenu[]{ L"START",L"SETTINGS",L"EXIT" };

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
                if (event.key.code == Keyboard::Up) { mymenu.MovePrev(); }

                if (event.key.code == Keyboard::Down) { mymenu.MoveNext(); }

                if (event.key.code == Keyboard::Return)
                {
                    switch (mymenu.getSelectedMenuNumber())
                    {
                    case 0:GamåStart(window, font);    break;
                    case 1:Option(window, font);     break;
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
}

int main()
{
    RenderWindow window;

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