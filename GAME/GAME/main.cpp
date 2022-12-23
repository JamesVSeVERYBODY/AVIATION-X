#include <SFML/Graphics.hpp>

#include "game.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(683, 384), "AVIATION X"); //inisiasi window
    window.setFramerateLimit(60); //setting framerate limit (60)

    Game game(&window); //BIKIN CLASSS GAME

    while (window.isOpen()) {
        game.Start();
    } //LOOP GAME 

    return 0;
}