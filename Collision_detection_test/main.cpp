#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include <iostream>
#include <vector>
#include <string>
#include "Ball.cpp"
#include <math.h>
#include "Physics.cpp"


static void mainMenu();


using namespace std;
using namespace sf;

int WIDTH=1280;
int HEIGHT=720;

sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Ball 8");

vector<Ball *> vecBalls;
Ball *selectedBall=nullptr;
bool startGame=false;
bool debug=false;

Font font;
Physics physics(vecBalls);
Color backgroundColor=Color::Black;

static void setup(void){
    if(!font.loadFromFile(resourcePath() + "sansation.ttf")){}
    
    window.setFramerateLimit(240);
    window.setVerticalSyncEnabled(true);
    for(int i=0;i<20;i++){
        float r=rand()%20+20;
        Color c(rand()%255,rand()%255,rand()%255);
        physics.addBall(new Ball(Vector2f(rand()%WIDTH,rand()%HEIGHT),r,i,c));
    }
}
    
static void mainMenu() {
    if(Keyboard::isKeyPressed(Keyboard::Return)){
        startGame=true;
    }
    RectangleShape rect(Vector2f(WIDTH/2+20,HEIGHT/2+20));
    rect.setFillColor(Color::Red);
    rect.setPosition(WIDTH/4, HEIGHT/4);
    Text text("",font);
    text.setFillColor(Color::Black);
    text.setPosition(Vector2f(rect.getPosition().x,rect.getPosition().y));
    text.setString("Left Mouse click - select a ball\n"
                   "Right Mouse click - shoot the ball\n"
                   "Spacebar - deselect a ball\n"
                   "While holding the left click you can move the balls\n\n"
                   "Press the return key to continue...");
    window.draw(rect);
    window.draw(text);
}


static void loop(void){
    if(startGame!=true){
        mainMenu();
    }else{
        //Select a ball
        if(Mouse::isButtonPressed(Mouse::Left)){
            selectedBall=nullptr;
            for(auto &ball : physics.getBalls()){
                if(isPointInCircle(ball->position,ball->raduis,Vector2f(Mouse::getPosition(window).x,Mouse::getPosition(window).y))){
                    selectedBall=ball;
//                    Drag the ball
                    if(selectedBall!=nullptr){
                        selectedBall->position.x=Mouse::getPosition(window).x;
                        selectedBall->position.y=Mouse::getPosition(window).y;
                    }
                    break;
                }
            }
        }

        physics.handle();
        
    }
}






int main(int, char const**)
{
    
    srand(clock());
    // Create the main window
    setup();

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        // Clear screen
        window.clear(backgroundColor);


        loop();

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
