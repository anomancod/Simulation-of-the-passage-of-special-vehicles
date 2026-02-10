#include <SFML/Graphics.hpp>
#include <iostream>

int CountOfLines = 4;
int Traffic = 5;
bool LightCars = true;
bool HeavyCars = false;
int MaxSpeed = 5;

int Var;

void Win_Sim()
{
    int r2 = -1;

    float cartimer = 0; 
    float lineTimer[4] = { 1000 };

    float BoL = CountOfLines * 110.f;

    sf::ConvexShape BoxOfLines1;
    BoxOfLines1.setPointCount(4);
    BoxOfLines1.setFillColor(sf::Color::White);
    BoxOfLines1.setPoint(0, sf::Vector2f(10.f, 0.f));
    BoxOfLines1.setPoint(1, sf::Vector2f(20 + BoL, 0.f));
    BoxOfLines1.setPoint(2, sf::Vector2f(20 + BoL, 800.f));
    BoxOfLines1.setPoint(3, sf::Vector2f(10.f, 800.f));

    sf::ConvexShape BoxOfLines2;
    BoxOfLines2.setPointCount(4);
    BoxOfLines2.setFillColor(sf::Color::Black);
    BoxOfLines2.setPoint(0, sf::Vector2f(20.f, 0.f));
    BoxOfLines2.setPoint(1, sf::Vector2f(BoL + 10.f, 0.f));
    BoxOfLines2.setPoint(2, sf::Vector2f(BoL + 10.f, 800.f));
    BoxOfLines2.setPoint(3, sf::Vector2f(20.f, 800.f));

    // Create of Black Screen
    sf::RectangleShape BlackScreen(sf::Vector2f(100.f * CountOfLines, 800.f));
    BlackScreen.setPosition(-35.f, 800.f);
    BlackScreen.setFillColor(sf::Color::Black);

    sf::RenderWindow window(sf::VideoMode(1200, 800), "Road Simulator");

    sf::Font font;
    font.loadFromFile("TNR.ttf");

    sf::Clock clock;

    sf::RectangleShape cars[100];
    bool ingame[100] = { false };
    bool inf[100] = { false }; // vozdeystvie (influence) spec.car na drugie machinu
    bool rotDone[100] = { false }; // povernulas' li machina
    float posX[4]{ 52.5f, 162.5f, 272.5f, 382.5f };

    int carin = 0;
    int carline = 0;

    bool spCarInGame = false;
    int spCarIs = 25;
    bool slowDown = false;
    float spCarSpd = -0.05 + MaxSpeed / 10;
    bool carsAheadCount = false;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 1000;

        cartimer += time;
        lineTimer[0] += time;
        lineTimer[1] += time;
        lineTimer[2] += time;
        lineTimer[3] += time;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        int startr1 = 1500;
        int endr1 = 7500;
        int startr2 = 0;
        int endr2 = 3;
        int r1 = std::rand() % (endr1 - startr1 + 1) + startr1;
        // àâòî - ñïàóí
        if (cartimer > r1 / Traffic)
        {
            if (carin == spCarIs)
            {
                if (Var == 1) // 1 var (sboku)
                {
                    if (lineTimer[0] > 9000 / MaxSpeed)
                    {
                        cars[carin].setSize(sf::Vector2f(40.f, 70.f));
                        cars[carin].setFillColor(sf::Color::Green);

                        cars[carin].setPosition(posX[0], 780.f);
                        carin++;
                        ingame[carin] = true;
                        spCarInGame = true;
                        cartimer = 0;
                        lineTimer[0] = 0;

                        std::cout << carin << std::endl;

                        int startr2 = 1; // teper pozadi spec transporta machinu ne poyavlyautsa
                    }
                }
                else // 2 var (megdu)
                {
                    //
                }
            }
            else
            {
                int rpast = r2;
                int r2 = std::rand() % (endr2 - startr2 + 1) + startr2;
                while (r2 == rpast) { r2 = std::rand() % (endr2 - startr2 + 1) + startr2; } // r2 - polosa

                if (lineTimer[r2] > 9000 / MaxSpeed)
                {
                    cars[carin].setSize(sf::Vector2f(40.f, 70.f));
                    cars[carin].setFillColor(sf::Color::Yellow);

                    cars[carin].setPosition(posX[r2], 780.f);
                    carin++;
                    ingame[carin] = true;
                    cartimer = 0;
                    lineTimer[r2] = 0;

                    std::cout << carin << std::endl;

                    if (carin == CountOfLines * 25) {
                        carin = 0;
                    }
                }
            }
        }

        // influence of spec.car
        if (spCarInGame == true)
        {
            for (int t = 0; t < 100; t++)
            {
                if (t != spCarIs) {
                    if (Var == 1)
                    {
                        sf::Vector2f carPos = cars[t].getPosition();
                        if (carPos.x == 52.5f) // proveraym na 1 polose li
                        {
                            sf::Vector2f spCarPos = cars[spCarIs].getPosition();
                            float dis = spCarPos.y - carPos.y;
                            if (dis > 0 && dis < 300) // podhodyshee li rastoynie
                            {
                                inf[t] = true;
                            }
                        }
                    }
                    else
                    {
                        //
                    }
                }
            }
        }

        // movement
        for (int t = 0; t < 100; t++)
        {
            if (t != spCarIs)
            {
                if (inf[t] == false) { // esli vliania net
                    cars[t].move(0.f, (-0.05f + MaxSpeed / 10) * time);
                }
                else {  // esli vlianie est
                    if (Var == 1)
                    {
                        sf::Vector2f carPos = cars[t].getPosition();
                        if (carPos.x < 125.f)
                        {
                            cars[t].rotate(0.01f);
                            cars[t].move((0.02f + MaxSpeed / 10) * time, (-0.04f + MaxSpeed / 10) * time);
                        }
                        else {
                            rotDone[t] = true;
                        }
                    }
                    else
                    {
                        //
                    }
                }
            }
            else // movement spec. car
            {
                if (spCarInGame == true) {
                    sf::Vector2f spCarPos = cars[spCarIs].getPosition();
                    for (int j = 0; j < 100; j++) {
                        if (inf[j] == true && rotDone[j] == false)
                        {
                            sf::Vector2f carPos = cars[j].getPosition();
                            float dis = spCarPos.y - carPos.y;
                            if (dis > 0 && dis < 80) {
                                slowDown = true;
                                carsAheadCount = true;
                            }
                        }
                    }
                    if (carsAheadCount == false) {
                        slowDown = false;
                    }
                    carsAheadCount = false;

                    if (slowDown == true) { // zamedlayem
                        spCarSpd += 0.0001f;
                        cars[spCarIs].move(0.f, spCarSpd * time);
                        BlackScreen.move(0.f, spCarSpd* time);
                    }
                    else { // yscorayem
                        spCarSpd += -0.00005f;
                        cars[spCarIs].move(0.f, spCarSpd * time);
                        BlackScreen.move(0.f, spCarSpd* time);
                    }
                }
            }
        }

        window.clear(sf::Color::Black);

        // Êîðîáêà äëÿ ïîëîñ
        window.draw(BoxOfLines1);
        window.draw(BoxOfLines2);

        // Ðèñóåì ïîëîñû
        for (int i = 0; i < CountOfLines - 1; i++)
        {
            sf::RectangleShape line(sf::Vector2f(10.f, 50.f));

            for (int j = 0; j < 16; j++)
            {
                line.setPosition(20.f + ((i + 1) * 100) + i * 10.f, -20.f + j * 50.f);

                if (j % 2 == 0) {
                    line.setFillColor(sf::Color::Black);
                }
                else {
                    line.setFillColor(sf::Color::White);
                }
                window.draw(line);
            }
        }

        // àâòî - ðèñîâêà
        for (int t = 0; t < 100; t++)
        {
            if (ingame[t] == true) {
                window.draw(cars[t]);
            }
        }

        // Draw BlackScreen
        window.draw(BlackScreen);

        // end the current frame
        window.display();
    }
}


//=================================================================


void Win_Set()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Road Simulator");

    sf::Font font;
    font.loadFromFile("TNR.ttf");

    // êîë-âî ïîëîñ
    sf::Text text1;
    text1.setFont(font);
    text1.setCharacterSize(50);
    text1.setFillColor(sf::Color::White);
    text1.setString(L"Êîë-âî ïîëîñ:");
    text1.setPosition(10, 0);
    //1
    sf::RectangleShape box1v11(sf::Vector2f(50.f, 50.f));
    box1v11.setFillColor(sf::Color::White);
    box1v11.setPosition(315, 10);
    sf::RectangleShape box1v21(sf::Vector2f(40.f, 40.f));
    box1v21.setFillColor(sf::Color::Black);
    box1v21.setPosition(320, 15);

    sf::Text textb11;
    textb11.setFont(font);
    textb11.setCharacterSize(40);
    textb11.setFillColor(sf::Color::White);
    textb11.setString("1");
    textb11.setPosition(320, 15);
    //2
    sf::RectangleShape box1v12(sf::Vector2f(50.f, 50.f));
    box1v12.setFillColor(sf::Color::White);
    box1v12.setPosition(375, 10);
    sf::RectangleShape box1v22(sf::Vector2f(40.f, 40.f));
    box1v22.setFillColor(sf::Color::Black);
    box1v22.setPosition(380, 15);
    //3
    sf::RectangleShape box1v13(sf::Vector2f(50.f, 50.f));
    box1v13.setFillColor(sf::Color::White);
    box1v13.setPosition(435, 10);
    sf::RectangleShape box1v23(sf::Vector2f(40.f, 40.f));
    box1v23.setFillColor(sf::Color::Black);
    box1v23.setPosition(440, 15);
    //4
    sf::RectangleShape box1v14(sf::Vector2f(50.f, 50.f));
    box1v14.setFillColor(sf::Color::White);
    box1v14.setPosition(495, 10);
    sf::RectangleShape box1v24(sf::Vector2f(40.f, 40.f));
    box1v24.setFillColor(sf::Color::Black);
    box1v24.setPosition(500, 15);

    // îáùàÿ çàãðóæåííîñòü
    sf::Text text2;
    text2.setFont(font);
    text2.setCharacterSize(50);
    text2.setFillColor(sf::Color::White);
    text2.setString(L"Îáùàÿ çàãðóæåííîñòü:");
    text2.setPosition(10, 70);

    sf::RectangleShape box12(sf::Vector2f(50.f, 50.f));
    box12.setFillColor(sf::Color::White);
    box12.setPosition(505, 80);
    sf::RectangleShape box22(sf::Vector2f(40.f, 40.f));
    box22.setFillColor(sf::Color::Black);
    box22.setPosition(510, 85);

    // ëåãêîâûå àâòîìîáèëè
    sf::Text text3;
    text3.setFont(font);
    text3.setCharacterSize(50);
    text3.setFillColor(sf::Color::White);
    text3.setString(L"Ëåãêîâûå àâòîìîáèëè:");
    text3.setPosition(10, 140);

    sf::RectangleShape box13(sf::Vector2f(50.f, 50.f));
    box13.setFillColor(sf::Color::White);
    box13.setPosition(495, 150);
    sf::RectangleShape box23(sf::Vector2f(40.f, 40.f));
    box23.setFillColor(sf::Color::Black);
    box23.setPosition(500, 155);

    // òÿæåëûå àâòîìîáèëè
    sf::Text text4;
    text4.setFont(font);
    text4.setCharacterSize(50);
    text4.setFillColor(sf::Color::White);
    text4.setString(L"Òÿæåëûå àâòîìîáèëè:");
    text4.setPosition(10, 350);

    sf::RectangleShape box14(sf::Vector2f(50.f, 50.f));
    box14.setFillColor(sf::Color::White);
    box14.setPosition(480, 360);
    sf::RectangleShape box24(sf::Vector2f(40.f, 40.f));
    box24.setFillColor(sf::Color::Black);
    box24.setPosition(485, 365);

    // ñêîðîñòíûå îãðàíè÷åíèÿ
    sf::Text text5;
    text5.setFont(font);
    text5.setCharacterSize(50);
    text5.setFillColor(sf::Color::White);
    text5.setString(L"Ñêîðîñòíûå îãðàíè÷åíèÿ:");
    text5.setPosition(10, 420);

    sf::RectangleShape box15(sf::Vector2f(50.f, 50.f));
    box15.setFillColor(sf::Color::White);
    box15.setPosition(575, 430);
    sf::RectangleShape box25(sf::Vector2f(40.f, 40.f));
    box25.setFillColor(sf::Color::Black);
    box25.setPosition(580, 435);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type = sf::Event::MouseButtonPressed)
            {
                int xm;
                int ym;
                xm = event.mouseButton.x;
                ym = event.mouseButton.y;

                // Ñ÷èòûâàíèÿ íàæàòèÿ íà êîðîáêè
            }
        }

        window.clear(sf::Color::Black);

        // òåêñòà
        window.draw(text1);
        window.draw(text2);
        window.draw(text3);
        window.draw(text4);
        window.draw(text5);

        // êîðîáêè
        window.draw(box12);
        window.draw(box22);
        window.draw(box13);
        window.draw(box23);
        window.draw(box14);
        window.draw(box24);
        window.draw(box15);
        window.draw(box25);

        // êîðîáêè-âàðèàíòû
        window.draw(box1v11);
        window.draw(box1v21);
        window.draw(box1v12);
        window.draw(box1v22);
        window.draw(box1v13);
        window.draw(box1v23);
        window.draw(box1v14);
        window.draw(box1v24);

        // êîðîáêè-òåêñòà
        window.draw(textb11);

        window.display();
    }
}

int main()
{
    Var = 1;
    //Var = 2;

    //Win_Set();
    Win_Sim();
}


