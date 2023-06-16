
#include <SFML/Graphics.hpp>
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <SFML/Audio.hpp>
using namespace sf;
using namespace std;
void swap(int *a, int *b) //SWAP FUNTION TO SWAP TILES
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void addition(int & score) // for y axis and x axis only one time call
{
 score=score+30;
 
}

int main()
{
    int gr[10][10]; //GRID
    int x[8][8];
    int y[8][8];
    int ts = 54, move = 50,score=0; // tile size
    Vector2i offset(54, 54);
    srand(time(0));

    RenderWindow main(VideoMode(740, 480), "Pop crush");

    Texture t1, t2, t3, t4, t5, t6;
    t1.loadFromFile("sprites/bg.png");
    t2.loadFromFile("sprites/suckers.png");
    t3.loadFromFile("sprites/popcrush.jpeg");
    t4.loadFromFile("sprites/menu.jpeg");
    t5.loadFromFile("sprites/gameover.jpg");
    t6.loadFromFile("sprites/help.jpeg");
    Sprite background(t1), gems(t2), home(t3), main_menu(t4), game_over(t5), help1(t6);
    for (int i = 1; i < 8; i++)   // BASIC STRUCTURE
        for (int j = 1; j < 8; j++)
        {
            gr[i][j] = rand() % 7;
        }
    for (int i = 1; i < 8; i++)
        for (int j = 1; j < 8; j++)
        {
            x[i][j] = j * ts;
        }
    for (int i = 1; i < 8; i++)
        for (int j = 1; j < 8; j++)
        {
            y[i][j] = i * ts;
        }
    int tap = 0, x1, y1, x2, y2;
    Vector2i mou;
    main.draw(home);
    main.display();
    while (main.isOpen())
    {
        sf::Music m1; // FOR MUSIC
        m1.openFromFile("sprites/m1.wav");
        m1.setVolume(100);
        m1.setLoop(true);
        m1.play();
        Event f;
        while (main.pollEvent(f)) // WINDOW FOR TITLE PAGE
        {

            if (f.type == Event::Closed)
                main.close();

            if (f.type == Event::KeyPressed)
            {
                if (f.key.code == Keyboard::Enter)
                {
                    main.close();

                    RenderWindow menu(VideoMode(740, 480), "Pop Crush");
                    Event h;
                    menu.draw(main_menu); // WINDOW FOR MENU
                    menu.display();
                    while (menu.isOpen())
                    {

                        while (menu.pollEvent(h))
                        {

                            if (f.type == Event::Closed)
                                menu.close();

                            if (h.type == Event::KeyPressed)
                            {   if (h.key.code == Keyboard::Num0)
                                     menu.close();

                                if (h.key.code == Keyboard::Num1)
                                {
                                    menu.close();
                                    RenderWindow app(VideoMode(740, 480), "Pop Crush");
                                    app.setFramerateLimit(60);

                                    while (app.isOpen()) //MAIN GAME
                                    {
                                        Event e;
                                        Font Calibri;
                                        Calibri.loadFromFile("sprites/Calibri.ttf"); // FOR SCORE AND MOVES
                                        Text text;
                                        text.setFont(Calibri);
                                        string scores = to_string(move);
                                        Text Score(scores, Calibri);
                                        Score.setCharacterSize(20);
                                        Score.setFillColor(Color::Red);
                                        Score.setPosition(625, 160);
                                        Text text1;
                                        text1.setFont(Calibri);
                                        text1.setString("MOVES");
                                        text1.setCharacterSize(27);
                                        text1.setFillColor(Color::Red);
                                        text1.setPosition(600, 130);
                                        string scores1 = to_string(score);
                                        Text Score1(scores1, Calibri);
                                        Score1.setCharacterSize(20);
                                        Score1.setFillColor(Color::Red);
                                        Score1.setPosition(625, 250);
                                        Text text2;
                                        text2.setFont(Calibri);
                                        text2.setString("SCORE");
                                        text2.setCharacterSize(27);
                                        text2.setFillColor(Color::Red);
                                        text2.setPosition(600, 220);
                                        app.draw(Score1);
                                        app.draw(text2);
                                        app.draw(Score);
                                        app.draw(text1);
                                        app.display();
                                        while (app.pollEvent(e))
                                        {

                                            if (e.type == Event::Closed)

                                                app.close();
                                        }
                                        if (e.type == Event::MouseButtonPressed)
                                            if (e.key.code == Mouse::Left)
                                            {
                                                // code of action to be performed on mouse click
                                                mou = Mouse::getPosition(app) - offset;
                                                tap++;
                                            }
                                        if (move == 0) //WHEN MOVES ARE FINISHED  GAME CLOSES
                                        {
                                            app.close();
                                            RenderWindow over(VideoMode(740, 480), "pop crush");
                                            over.draw(game_over);
                                            over.display();
                                            while (over.isOpen())
                                            {
                                                Event k;
                                                while (over.pollEvent(k))
                                                {

                                                    if (k.type == Event::Closed)
                                                        over.close();
                                                }
                                            }
                                        }

                                        if (tap == 1)
                                        {
                                            x1 = mou.x / ts + 1;
                                            y1 = mou.y / ts + 1;
                                        }
                                        if (tap == 2)
                                        {
                                            x2 = mou.x / ts + 1;
                                            y2 = mou.y / ts + 1;

                                            if (abs(x2 - x1) + abs(y2 - y1) == 1) //CHECKING ADJACENT TILES
                                            {
                                                swap(&gr[y1][x1], &gr[y2][x2]); // will swap
                                                move--;
                                                tap = 0;
                                            }
                                            // will start from begin
                                            else
                                                tap = 1; // will check
                                        }

                                        for (int i = 1; i <= 8; i++)
                                            for (int j = 1; j <= 8; j++)
                                            {
                                                if (gr[i][j] == gr[i + 1][j])     // checkking is FRONT AND BACK is same on y axis
                                                    if (gr[i][j] == gr[i - 1][j]) 
                                                    {   addition(score);
                                                         
                                                        for (int n = -1; n <= 1; n++)
                                                        {
                                                            gr[i + 1][j] = rand() % 7;
                                                            gr[i][j] = rand() % 7; // all three will dissapear new will take their place
                                                            gr[i - 1][j] = rand() % 7;
                                                        }
                                                    }

                                                if (gr[i][j] == gr[i][j + 1])     // checkking is FRONT AND BACK is same on y axis
                                                    if (gr[i][j] == gr[i][j - 1]) 
                                                    {   addition(score);
                                                        
                                                        for (int n = -1; n <= 1; n++)
                                                            gr[i][j] = rand() % 7; // all three will dissapear new will take their place
                                                        gr[i][j - 1] = rand() % 7;
                                                    }
                                            }

                                        app.draw(background);
                                        for (int i = 1; i < 8; i++)
                                            for (int j = 1; j < 8; j++)
                                            {
                                                gems.setTextureRect(IntRect(gr[i][j] * 49, 0, 49, 49)); //DIVIDING PICTURE
                                                gems.setPosition(x[i][j], y[i][j]);
                                                gems.move(offset.x - ts, offset.y - ts);
                                                app.draw(gems);
                                            }

                                        app.display();
                                    }
                                }
                                else if (h.key.code == Keyboard::Num2)
                                {

menu.close();
                                    RenderWindow app2(VideoMode(740, 480), "Pop Crush");
                                    app2.setFramerateLimit(60);
Clock clock;
                                    while (app2.isOpen()) //MAIN GAME
                                    {
                                        Event l;
                                        Font Calibri;
                                        Calibri.loadFromFile("sprites/Calibri.ttf"); // FOR SCORE AND MOVES
                                        Text text;
                                        text.setFont(Calibri);
                                         
                                            Time elapsed=clock.getElapsedTime();
                                            int timer=elapsed.asSeconds();
                                            string scores1 = to_string(timer);
                                            Text Score2(scores1, Calibri);
                                            Score2.setCharacterSize(20);
                                            Score2.setFillColor(Color::Red);
                                            Score2.setPosition(625, 160);
                                            Text text3;
                                            text3.setFont(Calibri);
                                            text3.setString("TIMER");
                                            text3.setCharacterSize(27);
                                            text3.setFillColor(Color::Red);
                                            text3.setPosition(600, 130);
                                            
                                            string scores2 = to_string(score);
                                        Text Scor2(scores2, Calibri);
                                        Scor2.setCharacterSize(20);
                                        Scor2.setFillColor(Color::Red);
                                        Scor2.setPosition(625, 250);
                                        Text text4;
                                        text4.setFont(Calibri);
                                        text4.setString("SCORE");
                                        text4.setCharacterSize(27);
                                        text4.setFillColor(Color::Red);
                                        text4.setPosition(600, 220);
                                       
                                        
                                        
                                        
                                        
                                        while (app2.pollEvent(l))
                                        {

                                            if (l.type == Event::Closed)

                                                app2.close();
                                        }
                                        if (l.type == Event::MouseButtonPressed)
                                            if (l.key.code == Mouse::Left)
                                            {
                                                // code of action to be performed on mouse click
                                                mou = Mouse::getPosition(app2) - offset;
                                                tap++;
                                            }
                                        if (timer > 30) //WHEN MOVES ARE FINISHED  GAME CLOSES
                                        {
                                            app2.close();
                                            RenderWindow over(VideoMode(740, 480), "pop crush");
                                            over.draw(game_over);
                                            over.display();
                                            while (over.isOpen())
                                            {
                                                Event f;
                                                while (over.pollEvent(f))
                                                {

                                                    if (f.type == Event::Closed)
                                                        over.close();
                                                }
                                            }
                                        }

                                        if (tap == 1)
                                        {
                                            x1 = mou.x / ts + 1;
                                            y1 = mou.y / ts + 1;
                                        }
                                        if (tap == 2)
                                        {
                                            x2 = mou.x / ts + 1;
                                            y2 = mou.y / ts + 1;

                                            if (abs(x2 - x1) + abs(y2 - y1) == 1) //CHECKING ADJACENT TILES
                                            {
                                                swap(&gr[y1][x1], &gr[y2][x2]); // will swap
                                                move--;
                                                tap = 0;
                                            }
                                            // will start from begin
                                            else
                                                tap = 1; // will check
                                        }

                                        for (int i = 1; i <= 8; i++)
                                            for (int j = 1; j <= 8; j++)
                                            {
                                                if (gr[i][j] == gr[i + 1][j])     // checkking is FRONT AND BACK is same on y axis
                                                    if (gr[i][j] == gr[i - 1][j]) 
                                                    {   addition(score);
                                                         
                                                        for (int n = -1; n <= 1; n++)
                                                        {
                                                            gr[i + 1][j] = rand() % 7;
                                                            gr[i][j] = rand() % 7; // all three will dissapear new will take their place
                                                            gr[i - 1][j] = rand() % 7;
                                                        }
                                                    }

                                                if (gr[i][j] == gr[i][j + 1])     // checkking is FRONT AND BACK is same on y axis
                                                    if (gr[i][j] == gr[i][j - 1]) 
                                                    {   addition(score);
                                                        
                                                        for (int n = -1; n <= 1; n++)
                                                            gr[i][j] = rand() % 7; // all three will dissapear new will take their place
                                                        gr[i][j - 1] = rand() % 7;
                                                    }
                                            }

                                        app2.draw(background);
                                        for (int i = 1; i < 8; i++)
                                            for (int j = 1; j < 8; j++)
                                            {
                                                gems.setTextureRect(IntRect(gr[i][j] * 49, 0, 49, 49)); //DIVIDING PICTURE
                                                gems.setPosition(x[i][j], y[i][j]);
                                                gems.move(offset.x - ts, offset.y - ts);
                                                app2.draw(gems);
                                            }
                                         app2.draw(Score2);
                                            app2.draw(text3);
                                            app2.display();   
                                         app2.draw(Scor2);
                                        app2.draw(text4);
                                        app2.display();
                                        app2.display();
                                    }
                                


                                }

                                else if (h.key.code == Keyboard::Num5) //FOR HELP
                                {
                                    menu.close();
                                    RenderWindow help(VideoMode(740, 480), "Pop Crush");
                                    help.draw(help1);
                                    help.display();

                                    while (help.isOpen())
                                    {
                                        Event i;
                                        while (help.pollEvent(i))
                                        {

                                            if (i.type == Event::Closed)
                                                help.close();

                                            if (h.type == Event::KeyPressed)
                                            {
                                                if (h.key.code == Keyboard::Num1)
                                                    help.close();
                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return 0;
}