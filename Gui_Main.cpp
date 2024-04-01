#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <random>
//#include <vector>

using namespace sf;

int SIZE_X = 800;
int SIZE_Y = 800;
int MAX_SNAKE_SIZE = 1000;


void draw_snake(RectangleShape* snake, VertexArray Snake_pos,int snake_size)
{
    int Length = snake_size;
    for (int i = 0;i < Length;i++)
    {   
        snake[i].setSize(Vector2f(10.f,10.f));
        snake[i].setFillColor(sf::Color(150, 50, 250));
        snake[i].setPosition(Snake_pos[i].position.x,Snake_pos[i].position.y);
    }
}

void move_snake(RectangleShape* snake, VertexArray* Snake_pos, const char* direction,int Length)
{
    for (int i = 0;i < Length-1;i++)
    {   
        Snake_pos[0][i].position = {Snake_pos[0][i+1].position.x, Snake_pos[0][i+1].position.y};
        snake[i].setPosition(Snake_pos[0][i].position.x,Snake_pos[0][i].position.y);
    }
    if (direction == "down")
    {
        Snake_pos[0][Length-1].position.y += 10;
        snake[Length-1].setPosition(Snake_pos[0][Length-1].position.x,Snake_pos[0][Length-1].position.y);
    }
    else if (direction == "up")
    {
        Snake_pos[0][Length-1].position.y -= 10;
        snake[Length-1].setPosition(Snake_pos[0][Length-1].position.x,Snake_pos[0][Length-1].position.y);
    }
    else if (direction == "left")
    {
        Snake_pos[0][Length-1].position.x -= 10;
        snake[Length-1].setPosition(Snake_pos[0][Length-1].position.x,Snake_pos[0][Length-1].position.y);
    }
    else if (direction == "right")
    {
        Snake_pos[0][Length-1].position.x += 10;
        snake[Length-1].setPosition(Snake_pos[0][Length-1].position.x,Snake_pos[0][Length-1].position.y);
    } 
} 

void Resize_Snake(RectangleShape* snake, VertexArray* Snake_pos, int new_size,int new_snake_end[2])
{
    Snake_pos[0][new_size-1].position = {new_snake_end[0], new_snake_end[1]};
    snake[new_size-1].setPosition(Snake_pos[0][new_size-1].position.x,Snake_pos[0][new_size-1].position.y);
}



int main()
{
    RenderWindow window(VideoMode(SIZE_X, SIZE_Y), "Snake Game",Style::Close);
    Texture texture;
    texture.loadFromFile("Desert_1.png");
    Sprite sprite;
    Vector2u size = texture.getSize();
    sprite.setTexture(texture);  //This is where you add an & to designate texture as a pointer
    sprite.setOrigin(size.x / 2, size.y / 2);
    bool Loose = false;
    int current_snake_size = 5;
    VertexArray Snake_pos(Points,MAX_SNAKE_SIZE);
    // Initial Position
    Snake_pos[0].position = {SIZE_X/2,SIZE_Y/2};
    Snake_pos[1].position = {SIZE_X/2+10,SIZE_Y/2};
    Snake_pos[2].position = {SIZE_X/2-10,SIZE_Y/2};
    Snake_pos[3].position = {SIZE_X/2-20,SIZE_Y/2};
    Snake_pos[4].position = {SIZE_X/2+20,SIZE_Y/2};
    RectangleShape snake[MAX_SNAKE_SIZE];
    draw_snake(&snake[0],Snake_pos,current_snake_size);
    int Random_Rec[2] = {0,0};
    Random_Rec[0] = rand()%int(window.getSize().x);
    Random_Rec[1] = rand()%int(window.getSize().y);
    // Round to 10 step size for matching the snake path
    Random_Rec[0] = Random_Rec[0] - Random_Rec[0]%10;
    Random_Rec[1] = Random_Rec[1] - Random_Rec[1]%10;
    RectangleShape Snake_Food(Vector2f(10,10));
    Snake_Food.setFillColor(sf::Color(255, 255, 0));
    Snake_Food.setPosition(Random_Rec[0],Random_Rec[1]);
    for (int i = 0;i < current_snake_size;i++)
    {   
        window.draw(snake[i]);
    }
    window.display();
    while (Loose == false)
    {
        Event event;
        if (Snake_pos[current_snake_size-1].position.x < 0 || Snake_pos[current_snake_size-1].position.x >= window.getSize().x || Snake_pos[current_snake_size-1].position.y < 0 || Snake_pos[current_snake_size-1].position.y >= window.getSize().y)
            Loose = true; 
        else 
        {  
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                {
                    window.close();
                } 
                if (event.key.code == Keyboard::Down)
                    move_snake(&snake[0],&Snake_pos,"down",current_snake_size);
                    // Key up pressed
                if (event.key.code == Keyboard::Up)
                    move_snake(&snake[0],&Snake_pos,"up",current_snake_size);
                    // Key left pressed
                if (event.key.code == Keyboard::Left)
                    move_snake(&snake[0],&Snake_pos,"left",current_snake_size);
                    // Key right pressed
                if (event.key.code == Keyboard::Right)
                    move_snake(&snake[0],&Snake_pos,"right",current_snake_size);  
            } 
            // Sample new food position for the snake
            if (Snake_pos[current_snake_size-1].position.x == Random_Rec[0] && Snake_pos[current_snake_size-1].position.y == Random_Rec[1])
            {
                current_snake_size += 1; 
                Resize_Snake(&snake[0],&Snake_pos,current_snake_size,Random_Rec);
                Random_Rec[0] = rand()%int(window.getSize().x);
                Random_Rec[1] = rand()%int(window.getSize().y);
                Random_Rec[0] -=  Random_Rec[0]%10;
                Random_Rec[1] -=  Random_Rec[1]%10;
                Snake_Food.setFillColor(sf::Color(255, 255, 0));
                Snake_Food.setPosition(Random_Rec[0],Random_Rec[1]);
            } 
            window.clear();
            window.draw(sprite);
            draw_snake(&snake[0],Snake_pos,current_snake_size);
            for (int i = 0;i < current_snake_size;i++)
            {   
                window.draw(snake[i]);
            } 
            window.draw(Snake_Food);
            window.display();
        }
        
    }
    std::cout << Snake_pos[4].position.x << window.getSize().y   ;
    return 0;
}


