#include "LoadTextures.hpp"
#include "HeroSprite.hpp"
#include "FoodSprite.hpp"
#include "SmallSnakesSprite.hpp"
#include "OtherSnakes.hpp"

#include <vector>

enum class GameState {
    MainMenu,
    Settings, 
    Play, 
    Exit
};

enum Direction { None, Up, Down, Left, Right };

void showMainMenu(sf::RenderWindow &window, GameState &current_state);
void showPlay(sf::RenderWindow &window, GameState &current_state);
void showSettings(sf::RenderWindow &window, GameState &current_state);

int main() {
    //-----------------------init window-----------------------
    sf::VideoMode dekstop_mode = sf::VideoMode::getDesktopMode();
    unsigned int screen_width = dekstop_mode.width;
    unsigned int screen_height = dekstop_mode.height;


    sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "Snake The Game"); // sf::Style::Fullscreen
    window.setFramerateLimit(60);
    //-----------------------init window-----------------------

    //---------------------draw windows---------------------
    GameState current_state = GameState::MainMenu;

    while(current_state != GameState::Exit) {
        switch (current_state) {
            case GameState::MainMenu:
                showMainMenu(window, current_state);
                break;

            case GameState::Settings:
                showSettings(window, current_state);
                break;
            
            case GameState::Play:
                showPlay(window, current_state);
                break;
        }
    }
    //---------------------draw windows---------------------
    
    return EXIT_SUCCESS;
}

void showMainMenu(sf::RenderWindow& window, GameState& current_state) {
    sf::Font font;
    if (!font.loadFromFile("../../assets/fonts/Klyakson.otf")) {
        return;
    }

    //---------------------Init text Main menu---------------------
    sf::Text title_text("Snake The Game", font, 150);
    title_text.setFillColor(sf::Color::White);
    title_text.setStyle(sf::Text::Bold);
    title_text.setPosition((window.getSize().x - title_text.getLocalBounds().width) / 2, 150);

    sf::Text play_text("Play", font, 140);
    sf::Text settings_text("Settings", font, 80);
    sf::Text exit_text("Exit", font, 80);

    play_text.setFillColor(sf::Color::White);
    settings_text.setFillColor(sf::Color::White);
    exit_text.setFillColor(sf::Color::White);

    play_text.setPosition((window.getSize().x - play_text.getLocalBounds().width) / 2, 550);
    settings_text.setPosition((window.getSize().x - settings_text.getLocalBounds().width) / 2, 750);
    exit_text.setPosition((window.getSize().x - exit_text.getLocalBounds().width) / 2, 850);
    //---------------------Init text Main menu---------------------

    //---------------------Init icons Main menu---------------------
    Textures textures;
    Icons icons;

    icons.LoadTexturesFromFile(textures);
    icons.SmoothTextures(textures);

    sf::Sprite sprite_github(textures.github_icon), sprite_steam(textures.steam_icon), sprite_discord(textures.discord_icon);

    sprite_github.setPosition(0, window.getSize().y - 25);
    sprite_steam.setPosition(30, window.getSize().y - 25);
    sprite_discord.setPosition(60, window.getSize().y - 25);
    //---------------------Init icons Main menu---------------------

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                    return;
                }
            }

            //---------------------Event Mouse---------------------
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mouse_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (play_text.getGlobalBounds().contains(mouse_pos)) {
                    current_state = GameState::Play;
                    return;
                } else if (settings_text.getGlobalBounds().contains(mouse_pos)) {
                    current_state = GameState::Settings;
                    return;
                } else if (exit_text.getGlobalBounds().contains(mouse_pos)) {
                    window.close();
                    return;
                } else if (sprite_github.getGlobalBounds().contains(mouse_pos)) {
                    
                } else if (sprite_steam.getGlobalBounds().contains(mouse_pos)) {
                    
                } else if (sprite_discord.getGlobalBounds().contains(mouse_pos)) {
                    
                }
            }
            //---------------------Event Mouse---------------------
        }

        //---------------------Draw objects---------------------
        window.clear(sf::Color(0, 128, 0));

        window.draw(title_text);
        window.draw(play_text);
        window.draw(settings_text);
        window.draw(exit_text);

        window.draw(sprite_github);
        window.draw(sprite_steam);
        window.draw(sprite_discord);

        window.display();
        //---------------------Draw objects---------------------
    }
}

void showPlay(sf::RenderWindow& window, GameState& current_state) {
    sf::Font font;
    if (!font.loadFromFile("../../assets/fonts/Klyakson.otf")) {
        return;
    }

    //---------------------init textures and sprites---------------------
    Textures textures;
    Snake snake;
    Food food;
    SmallSnakes small_snakes;
    OtherSnake barrel_snake;

    HeroSprite hero;
    FoodSprites food_s;
    SmallPinkSnakeSprite pink_snake;
    SmallGreenSnakeSprite green_snake;
    SmallPharaonSnakeSprite pharaon_snake;
    OtherBarelSnake barrel_snake_s;

    sf::Sprite sprite_hero;
    sf::Sprite sprite_food;
    sf::Sprite sprite_pink_snake;
    sf::Sprite sprite_green_snake;
    sf::Sprite sprite_pharaon_snake;
    sf::Sprite sprite_barrel_snake;
    //---------------------init textures and sprites---------------------

    //---------------------loaders textures---------------------
    snake.LoadTexturesFromFile(textures);
    snake.SmoothTextures(textures);

    food.LoadTexturesFromFile(textures);
    food.SmoothTextures(textures);

    small_snakes.LoadTexturesFromFile(textures);
    small_snakes.SmoothTextures(textures);

    barrel_snake.LoadTexturesFromFile(textures);
    barrel_snake.SmoothTextures(textures);
    //---------------------loaders textures---------------------

    //---------------------loaders sprites + smooth---------------------
    hero.LoadHeroSprite(sprite_hero, textures);

    food_s.InitSizes(window.getSize().x, window.getSize().y);
    food_s.LoadFoodSprite(sprite_food, textures);

    pink_snake.LoadHeroSprite(sprite_pink_snake, textures);
    green_snake.LoadHeroSprite(sprite_green_snake, textures);
    pharaon_snake.LoadHeroSprite(sprite_pharaon_snake, textures);

    barrel_snake_s.LoadHeroSprite(sprite_barrel_snake, textures);
    //---------------------loaders sprites + smooth---------------------

    //---------------------init Direction---------------------
    Direction currentDirection = None;
    int current_frame = 0;
    bool last_dir_left = false;
    //---------------------init Direction---------------------

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }

            //---------------------Event Keyboard---------------------
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::W) {
                    currentDirection = Up;
                } else if (event.key.code == sf::Keyboard::S) {
                    currentDirection = Down;
                } else if (event.key.code == sf::Keyboard::A) {
                    currentDirection = Left;
                } else if (event.key.code == sf::Keyboard::D) {
                    currentDirection = Right;
                }
            }
            //---------------------Event Keyboard---------------------  
        }

        //---------------------Move hero---------------------
        if (currentDirection == Left) {
            hero.MoveLeft(sprite_hero);
            last_dir_left = true;
        } else if (currentDirection == Right) {
            hero.MoveRight(sprite_hero);        
            last_dir_left = false;
        } else if (currentDirection == Up) {
            hero.MoveUp(sprite_hero);            
        } else if (currentDirection == Down) {
            hero.MoveDown(sprite_hero);
        }
        //---------------------Move hero---------------------

        //---------------------Animation Objects with diffrent sides---------------------
        if(last_dir_left) {
            if(current_frame % 4 == 0) 
                hero.CircleSpritesA(sprite_hero);

            if(current_frame % 15 == 0)
                pink_snake.CircleSpritesA(sprite_pink_snake);

            if(current_frame % 6 == 0)
                green_snake.CircleSpritesA(sprite_green_snake);

            if(current_frame % 5 == 0)
                pharaon_snake.CircleSpritesA(sprite_pharaon_snake);

        } else if(!last_dir_left) {
            if(current_frame % 4 == 0)
                hero.CircleSpritesD(sprite_hero);

            if(current_frame % 15 == 0)
                pink_snake.CircleSpritesD(sprite_pink_snake);

            if(current_frame % 6 == 0)
                green_snake.CircleSpritesD(sprite_green_snake);

            if(current_frame % 5 == 0)
                pharaon_snake.CircleSpritesD(sprite_pharaon_snake);

        }
        //---------------------Animation Objects with diffrent sides---------------------

        //---------------------Animation Objects with static sides---------------------
        if(current_frame % 5 == 0)
            barrel_snake_s.CheckDistanceSprite(sprite_hero ,sprite_barrel_snake);
        //---------------------Animation Objects with static sides---------------------

        //---------------------Collision hero with food---------------------
        if(food_s.CheckCollision(sprite_hero, sprite_food)) {          
            food_s.LoadFoodSprite(sprite_food, textures);
        }
        //---------------------Collision hero with food---------------------

        //---------------------Draw objects---------------------
        window.clear(sf::Color(0, 128, 0));

        window.draw(sprite_hero);

        window.draw(sprite_food);

        window.draw(sprite_pink_snake);
        window.draw(sprite_green_snake);
        window.draw(sprite_pharaon_snake);

        window.draw(sprite_barrel_snake);

        window.display();
        //---------------------Draw objects---------------------

        current_frame == 250 ? current_frame = 0 : current_frame++; // update animations timer
    }
}

void showSettings(sf::RenderWindow& window, GameState& current_state) {
    sf::Font font;
    if (!font.loadFromFile("../../assets/fonts/Klyakson.otf")) {
        return;
    }

    sf::Text settingsText("Settings", font, 70);
    settingsText.setFillColor(sf::Color::White);
    settingsText.setPosition((window.getSize().x - settingsText.getLocalBounds().width) / 2, 200);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                    return;
                }
            }
        }

        //---------------------Draw objects---------------------
        window.clear(sf::Color(0, 128, 0));

        window.draw(settingsText);

        window.display();
        //---------------------Draw objects---------------------
    }
}
