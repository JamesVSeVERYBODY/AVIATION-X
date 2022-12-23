#include "game.h"

Game::Game(RenderWindow* win) {
    window = win;

    Texture tex, tex2;

    tex.loadFromFile("Sprites/player.png");
    tex2.loadFromFile("Sprites/bullet.png");

    player.Start(tex, tex2);

    font.loadFromFile("fonts/fast99.ttf");

    
}

//INISIASI GAME

void Game::Start() {
    MainMenu();

    int timer = 0; // DELAY PELURU
    int enemyTimer = 50; // DELAY SPAWN 

    Texture texbg;
    texbg.loadFromFile("Sprites/bg.png");

    Sprite bg;
    bg.setTexture(texbg);
    bg.setTextureRect(IntRect(0, 0, 683, 384));

    Texture tex;
    tex.loadFromFile("Sprites/saucer.png");

    Sprite enemySprite;
    enemySprite.setTexture(tex);
    enemySprite.setTextureRect(IntRect(0, 0, 60, 35));

    enemies.clear();

    int score = 0;

    Text scoreText;
    scoreText.setFont(font);

    Music music;
    music.openFromFile("Sounds/music2.ogg"); 
    music.play();

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && timer <= 0) {
            player.Tembak();
            timer = 10;
        } timer--;

        if (enemyTimer <= 0) {
            while(1){
                int r = rand() % 100;
                if (r < 50) break;

                enemies.push_back(Vector2f(rand() % 100 + 690, rand() % 150 + 50));
            }
        

            enemyTimer = 50;
        } enemyTimer--;

        scoreText.setString("Score : " + std::to_string(score));

        Vector2f mousePos = Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);
        
        player.SetPosition(mousePos);
        player.Update();

        window->clear();
        window->draw(bg);

        FloatRect playerBox(player.GetSprite().getPosition().x, player.GetSprite().getPosition().y, 60, 49);
        for (int i = enemies.size() - 1; i >= 0 ; i--) {
            enemies[i].x -= 5;
            float y = enemies[i].y + 50 * sin(enemies[i].x / 100);

            enemySprite.setPosition(Vector2f(enemies[i].x, y));

            FloatRect enemyBox(enemies[i].x, y, 60, 35);
             
            if (player.CollidePeluru(enemyBox)) {
                score += 1;
                enemies.erase(enemies.begin() + i);
                continue;
            }

            if (playerBox.intersects(enemyBox)) {
                GameOver();
                return;
            }

            if (enemies[i].x < -60) {
                enemies.erase(enemies.begin() + i);
                score -= 1;
                continue;
            }

            window->draw(enemySprite);
        }

        player.Draw(*window);

        window->draw(scoreText);

        window->display();
    }

}


void Game::MainMenu() {
    Text text;
    text.setFont(font);
    text.setString("    Press Enter to Start ! .\n .\n .\n .\n        Escape to Close");
    text.setPosition(window->getSize().x / 4, window->getSize().y / 3.5f);

    Music music;
    music.openFromFile("Sounds/menusong.ogg");
    music.play();

    Texture tex;
    tex.loadFromFile("Sprites/menu.jpg");

    Sprite bg;
    bg.setTexture(tex);
    bg.setTextureRect(IntRect(0, 0, 1080, 540));

    bg.setScale(window->getSize().x / 1080.f, window->getSize().y / 540.f);

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.key.code == sf::Keyboard::Enter) {
                return;
            }
            else if (event.key.code == sf::Keyboard::Escape)
            {
                window->close();
            }

        }

        window->clear();
        window->draw(bg);
        window->draw(text);
        window->display();
    }
}

void Game::GameOver() {
    Text text;
    text.setFont(font);
    text.setString("       YOU'VE LOST.. .\n        GAMEOVER !.\n .\n .\n .\n .\n .\n Press any key to go Back");
    text.setPosition(window->getSize().x / 3.5, window->getSize().y / 3.5f);
    Music music;
   music.openFromFile("Sounds/music3.ogg");
   music.play();

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed) {
                return;
            }
        }

        window->clear();
        Texture tex;
        tex.loadFromFile("Sprites/lost2.png");
        Sprite bg;
        bg.setTexture(tex);
        bg.setTextureRect(IntRect(0, 0, 1080, 720));
        bg.setScale(window->getSize().x / 200.f, window->getSize().y / 200.f);
        window->draw(bg);
        window->draw(text);
        window->display();
    }
}