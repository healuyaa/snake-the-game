#include "LoadTextures.hpp"
#include "HeroSprite.hpp"
#include "FoodSprite.hpp"

#include <vector>

#define SPEEDVOLUMESNAKE 0.05 

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

    Textures textures;
    Icons icons;

    icons.LoadTexturesFromFile(textures);
    icons.SmoothTextures(textures);

    sf::Sprite sprite_github(textures.github_icon), sprite_steam(textures.steam_icon), sprite_discord(textures.discord_icon);

    sprite_github.setPosition(0, window.getSize().y - 25);
    sprite_steam.setPosition(30, window.getSize().y - 25);
    sprite_discord.setPosition(60, window.getSize().y - 25);

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
        }

        window.clear(sf::Color(0, 128, 0));

        window.draw(title_text);
        window.draw(play_text);
        window.draw(settings_text);
        window.draw(exit_text);

        window.draw(sprite_github);
        window.draw(sprite_steam);
        window.draw(sprite_discord);

        window.display();
    }
}

void showPlay(sf::RenderWindow& window, GameState& current_state) {
    sf::Font font;
    if (!font.loadFromFile("../../assets/fonts/Klyakson.otf")) {
        return;
    }

    Textures textures;
    Snake snake;
    Food food;

    HeroMoving moves;
    RectHero rects_hero;
    FoodSprites food_s;

    sf::Sprite sprite_hero;
    sf::Sprite sprite_food;

    // std::vector<sf::Sprite> snakes;

    snake.LoadTexturesFromFile(textures);
    snake.SmoothTextures(textures);

    food.LoadTexturesFromFile(textures);
    food.SmoothTextures(textures);

    moves.InitsRects(rects_hero);
    moves.LoadHeroSprite(sprite_hero, textures);

    food_s.InitSizes(window.getSize().x, window.getSize().y);
    food_s.LoadFoodSprite(sprite_food, textures);

    // snakes.push_back(sprite_hero);



    Direction currentDirection = None;
    int current_frame = 0;
    bool last_dir_left = false;    

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }

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
            } else if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::W && currentDirection == Up) {
                    currentDirection = None;
                } else if (event.key.code == sf::Keyboard::S && currentDirection == Down) {
                    currentDirection = None;
                } else if (event.key.code == sf::Keyboard::A && currentDirection == Left) {
                    currentDirection = None;
                } else if (event.key.code == sf::Keyboard::D && currentDirection == Right) {
                    currentDirection = None;
                }
            }          
        }

        if (currentDirection == Left) {
            moves.ChangeSprite(sprite_hero, rects_hero.rect_a);
            moves.MoveLeft(sprite_hero);

            last_dir_left = true;
        } else if (currentDirection == Right) {
            moves.ChangeSprite(sprite_hero, rects_hero.rect_d);
            moves.MoveRight(sprite_hero);

            last_dir_left = false;
        } else if (currentDirection == Up) {
            moves.MoveUp(sprite_hero);
        } else if (currentDirection == Down) {
            moves.MoveDown(sprite_hero);
        }

        if(last_dir_left && currentDirection == None) {
            if(current_frame % 7 == 0)
                moves.CircleSpritesA(sprite_hero);
        } else if(!last_dir_left && currentDirection == None) {
            if(current_frame % 7 == 0)
                moves.CircleSpritesD(sprite_hero);
        }

        if(food_s.CheckCollision(sprite_hero, sprite_food)) {
            sf::Sprite new_snake = sprite_hero;
            
            // new_snake.setPosition(sprite_hero.getPosition().x + 40, sprite_hero.getPosition().y + 10);
            // new_snake.setScale(0.77, 0.77);
            // snakes.push_back(new_snake);

            food_s.LoadFoodSprite(sprite_food, textures);
        }


        window.clear(sf::Color(0, 128, 0));

        window.draw(sprite_hero);
        window.draw(sprite_food);

        // for(auto& a: snakes) {
        //     window.draw(a);
        // }

        window.display();

        current_frame == 49 ? current_frame = 0 : current_frame++;
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

        window.clear(sf::Color(0, 128, 0));

        window.draw(settingsText);

        window.display();
    }
}
