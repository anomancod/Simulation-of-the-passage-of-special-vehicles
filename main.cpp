#include <SFML/Graphics.hpp>
#include <iostream>

int CountOfLines = 4;
int Traffic = 5;
bool LightCars = true;
bool HeavyCars = false;
int MaxSpeed = 60;

void Win_Sim() 
{
    float cartimer = 0; // Таймер появления машин

    // Квадрат для полос
    float BoL = CountOfLines * 110.f; // 100 - полоса, 10 - разделение

    sf::ConvexShape BoxOfLines1;
    BoxOfLines1.setPointCount(4);
    BoxOfLines1.setFillColor(sf::Color::White);
    BoxOfLines1.setPoint(0, sf::Vector2f(10.f, 10.f));
    BoxOfLines1.setPoint(1, sf::Vector2f(20 + BoL, 10.f));
    BoxOfLines1.setPoint(2, sf::Vector2f(20 + BoL, 790.f));
    BoxOfLines1.setPoint(3, sf::Vector2f(10.f, 790.f));

    sf::ConvexShape BoxOfLines2;
    BoxOfLines2.setPointCount(4);
    BoxOfLines2.setFillColor(sf::Color::Black);
    BoxOfLines2.setPoint(0, sf::Vector2f(20.f, 20.f));
    BoxOfLines2.setPoint(1, sf::Vector2f(BoL + 10.f, 20.f));
    BoxOfLines2.setPoint(2, sf::Vector2f(BoL + 10.f, 780.f));
    BoxOfLines2.setPoint(3, sf::Vector2f(20.f, 780.f));


    sf::RenderWindow window(sf::VideoMode(1200, 800), "Road Simulator");

    sf::Font font;
    font.loadFromFile("TNR.ttf");

    sf::Clock clock;

    // всё для авто
    sf::RectangleShape cars[20];
    bool ingame[20] = {false};
    float posX[4]{50, 160, 270, 380};
    
    int carin = 0;
    int carline = 0;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds(); // дать прошедшее время в микросекундах
        clock.restart(); //перезагружает время
        time = time / 1000; //скорость игры

        cartimer += time; // реализация машинного таймера

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        int startr1 = 7500;
        int endr1 = 50000;
        int r1 = std::rand() % (endr1 - startr1 + 1) + startr1;
        // авто - спаун
        if (cartimer > r1 / Traffic)
        {
            if (carin == CountOfLines * 5) {
                carin = 0;
            }

            ingame[carin] = true;
            cars[carin].setSize(sf::Vector2f(50.f, 75.f));
            cars[carin].setFillColor(sf::Color::Yellow);

            int startr2 = 0;
            int endr2 = 3;
            int r2 = std::rand() % (endr2 - startr2 + 1) + startr2;

            cars[carin].setPosition(posX[r2], 780.f);
            carin++;
            
            cartimer = 0;
        }

        // авто - движение (и удаление)
        for (int t = 0; t < 20; t++) 
        {
            if (t < 5) { carline = 0; }
            if (t < 10 && t >= 5) { carline = 1; }
            if (t < 15 && t >= 10) { carline = 2; }
            if (t < 20 && t >= 15) { carline = 3; }

            if (ingame[t] = true) {
                if (cars[t].getPosition() == sf::Vector2f(posX[carline], 50.f)) {
                    ingame[t] = false;
                }
                else {
                    cars[t].move(0.f, -0.1f * time * (MaxSpeed / 50));
                    //std::cout << "it just works";
                }
            }
        }

        window.clear(sf::Color::Black);

        // Коробка для полос
        window.draw(BoxOfLines1);
        window.draw(BoxOfLines2);

        // Рисуем полосы
        for (int i = 0; i < CountOfLines - 1; i++)
        {
            sf::RectangleShape line(sf::Vector2f(10.f, 50.f));

            for (int j = 0; j < 15; j++)
            {
                line.setPosition(20.f + ((i + 1) * 100) + i * 10.f, 20.f + j * 50.f);

                if (j % 2 == 0) {
                    line.setFillColor(sf::Color::Black);
                }
                else {
                    line.setFillColor(sf::Color::White);
                }
                window.draw(line);
            }
        }

        // авто - рисовка
        for (int t = 0; t < 20; t++)
        {
            if (ingame[t] = true) {
                window.draw(cars[t]);
            }
        }

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

    // кол-во полос
    sf::Text text1;
    text1.setFont(font);
    text1.setCharacterSize(50);
    text1.setFillColor(sf::Color::White);
    text1.setString(L"Кол-во полос:");
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

    // общая загруженность
    sf::Text text2;
    text2.setFont(font);
    text2.setCharacterSize(50);
    text2.setFillColor(sf::Color::White);
    text2.setString(L"Общая загруженность:");
    text2.setPosition(10, 70);

    sf::RectangleShape box12(sf::Vector2f(50.f, 50.f));
    box12.setFillColor(sf::Color::White);
    box12.setPosition(505, 80);
    sf::RectangleShape box22(sf::Vector2f(40.f, 40.f));
    box22.setFillColor(sf::Color::Black);
    box22.setPosition(510, 85);

    // легковые автомобили
    sf::Text text3;
    text3.setFont(font);
    text3.setCharacterSize(50);
    text3.setFillColor(sf::Color::White);
    text3.setString(L"Легковые автомобили:");
    text3.setPosition(10, 140);

    sf::RectangleShape box13(sf::Vector2f(50.f, 50.f));
    box13.setFillColor(sf::Color::White);
    box13.setPosition(495, 150);
    sf::RectangleShape box23(sf::Vector2f(40.f, 40.f));
    box23.setFillColor(sf::Color::Black);
    box23.setPosition(500, 155);

    // тяжелые автомобили
    sf::Text text4;
    text4.setFont(font);
    text4.setCharacterSize(50);
    text4.setFillColor(sf::Color::White);
    text4.setString(L"Тяжелые автомобили:");
    text4.setPosition(10, 350);

    sf::RectangleShape box14(sf::Vector2f(50.f, 50.f));
    box14.setFillColor(sf::Color::White);
    box14.setPosition(480, 360);
    sf::RectangleShape box24(sf::Vector2f(40.f, 40.f));
    box24.setFillColor(sf::Color::Black);
    box24.setPosition(485, 365);

    // скоростные ограничения
    sf::Text text5;
    text5.setFont(font);
    text5.setCharacterSize(50);
    text5.setFillColor(sf::Color::White);
    text5.setString(L"Скоростные ограничения:");
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

                // Считывания нажатия на коробки
            }
        }

        window.clear(sf::Color::Black);

        // текста
        window.draw(text1);
        window.draw(text2);
        window.draw(text3);
        window.draw(text4);
        window.draw(text5);

        // коробки
        window.draw(box12);
        window.draw(box22);
        window.draw(box13);
        window.draw(box23);
        window.draw(box14);
        window.draw(box24);
        window.draw(box15);
        window.draw(box25);

        // коробки-варианты
        window.draw(box1v11);
        window.draw(box1v21);
        window.draw(box1v12);
        window.draw(box1v22);
        window.draw(box1v13);
        window.draw(box1v23);
        window.draw(box1v14);
        window.draw(box1v24);

        // коробки-текста
        window.draw(textb11);

        window.display();
    }
}

int main()
{
    Win_Set();

    //Win_Sim();
}