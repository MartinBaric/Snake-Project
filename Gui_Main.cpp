#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <random>

using namespace sf;

int SIZE_X = 800;
int SIZE_Y = 800;

int main()
{
    RenderWindow window(VideoMode(SIZE_X, SIZE_Y), "Snake Game",Style::Close);

    bool Loose = false;
    Vertex Snake_pos;
    Snake_pos.position = {SIZE_X/2,SIZE_Y/2};
    RectangleShape snake(Vector2f(10,10));
    snake.setFillColor(sf::Color(150, 50, 250));
    snake.setPosition(Snake_pos.position.x,Snake_pos.position.y);
    window.draw(snake);
    int Random_Rec[2] = {0,0};
    Random_Rec[0] = rand()%int(window.getSize().x);
    Random_Rec[1] = rand()%int(window.getSize().y);
    // Round to 10 step size for matching the snake path
    Random_Rec[0] = Random_Rec[0] - Random_Rec[0]%10;
    Random_Rec[1] = Random_Rec[1] - Random_Rec[1]%10;
    RectangleShape Snake_Food(Vector2f(10,10));
    Snake_Food.setFillColor(sf::Color(255, 255, 0));
    Snake_Food.setPosition(Random_Rec[0],Random_Rec[1]);
    while (Loose == false)
    {
        Event event;
        if (Snake_pos.position.x < 0 || Snake_pos.position.x >= window.getSize().x || Snake_pos.position.y < 0 || Snake_pos.position.y >= window.getSize().y)
           Loose = true;
        else 
        { 
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
                if (event.key.code == Keyboard::Down)
                    Snake_pos.position.y += 10; 
                    // Key up pressed
                if (event.key.code == Keyboard::Up)
                    Snake_pos.position.y -= 10; 
                    // Key left pressed
                if (event.key.code == Keyboard::Left)
                    Snake_pos.position.x -= 10;
                    // Key right pressed
                if (event.key.code == Keyboard::Right)
                    Snake_pos.position.x += 10; 
            }
            snake.setPosition(Snake_pos.position.x,Snake_pos.position.y);
            // Sample new food position for the snake
            if (Snake_pos.position.x == Random_Rec[0] && Snake_pos.position.y == Random_Rec[1])
            {
                Random_Rec[0] = rand()%int(window.getSize().x);
                Random_Rec[1] = rand()%int(window.getSize().y);
                Random_Rec[0] -=  Random_Rec[0]%10;
                Random_Rec[1] -=  Random_Rec[1]%10;
                Snake_Food.setFillColor(sf::Color(255, 255, 0));
                Snake_Food.setPosition(Random_Rec[0],Random_Rec[1]);
            }
            window.clear();
            window.draw(snake);
            window.draw(Snake_Food);
            window.display();
        }
    }
    std::cout << Snake_pos.position.x << window.getSize().y   ;
    return 0;
}
