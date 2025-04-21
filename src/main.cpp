#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "game.h"

using namespace std;

int main() {

    int width = 1800;
    int height = 1200;
    
    sf::RenderWindow window(sf::VideoMode(width, height), "Esther's Platformer");
    Game game = Game(&window, width, height, width/2, height/2);
    window.display();

    //game loop
    sf::Event event;
    while(window.isOpen()) {
        game.update();
        window.display();

        //check to close window
        window.pollEvent(event);
        if (event.type == sf::Event::Closed) {
            break;
        }  
    }

    game.destroy();
    window.close();

    return 0;
}