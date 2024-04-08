#include "LoadTextures.hpp"
#include "HeroSprite.hpp"
#include "FoodSprite.hpp"
#include "SmallSnakesSprite.hpp"
#include "OtherSnakes.hpp"
#include "LifeBarSprite.hpp"
#include "Backgraound.hpp"

#include <vector>
#include <cmath>
#include <iomanip>
#include <iostream>

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

float lerp(float current, float target, float speed) {
    return current + speed * (target - current);
}

int main() {
    //-----------------------init window-----------------------
    sf::VideoMode dekstop_mode = sf::VideoMode::getDesktopMode();
    unsigned int screen_width = dekstop_mode.width;
    unsigned int screen_height = dekstop_mode.height;

    sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "Snake The Game", sf::Style::Fullscreen); 
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
    // Textures textures;
    // Icons icons;

    // icons.LoadTexturesFromFile(textures);
    // icons.SmoothTextures(textures);

    // sf::Sprite sprite_github(textures.github_icon), sprite_steam(textures.steam_icon), sprite_discord(textures.discord_icon);

    // sprite_github.setPosition(0, window.getSize().y - 25);
    // sprite_steam.setPosition(30, window.getSize().y - 25);
    // sprite_discord.setPosition(60, window.getSize().y - 25);
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
                }
            }
            //---------------------Event Mouse---------------------
        }

        //---------------------Draw objects---------------------
        window.clear(sf::Color(0, 0, 0));

        window.draw(title_text);
        window.draw(play_text);
        window.draw(settings_text);
        window.draw(exit_text);

        // window.draw(sprite_github);
        // window.draw(sprite_steam);
        // window.draw(sprite_discord);

        window.display();
        //---------------------Draw objects---------------------
    }
}

void showPlay(sf::RenderWindow& window, GameState& current_state) {
    //---------------------Interface of game---------------------
    sf::Font font;
    if (!font.loadFromFile("../../assets/fonts/Klyakson.otf"));

    sf::Text score_text;
    score_text.setFont(font);
    score_text.setCharacterSize(30);
    score_text.setFillColor(sf::Color::White);

    sf::FloatRect text_bounds = score_text.getLocalBounds();

    sf::Text life_text;
    life_text.setFont(font);
    life_text.setCharacterSize(30);
    life_text.setFillColor(sf::Color::White);

    sf::Text time_text("", font, 40);
    time_text.setFillColor(sf::Color::White);

    sf::RectangleShape darken_rect(sf::Vector2f(window.getSize().x, text_bounds.height + 60));
    darken_rect.setFillColor(sf::Color(0, 0, 0, 100));
    //---------------------Interface of game---------------------

    //---------------------init textures and sprites---------------------
    Textures textures;
    Snake snake;
    Food food;
    SmallSnakes small_snakes;
    // OtherSnake barrel_snake;
    LifeBar life_bar_i;
    Background background;
    BackgroundErrors background_errors;

    HeroSprite hero;
    FoodSprites food_s;
    // OtherBarelSnake barrel_snake_s;
    LifeBarClass life_bar_s;
    BackgroundClass background_s;
    BackgroundErrorsClass background_errors_s;

    SmallPinkSnakeSprite animate_sprite_pink_snakes;
    SmallGreenSnakeSprite animate_sprite_green_snakes;
    SmallPharaonSnakeSprite animate_sprite_pharaon_snakes;

    sf::Sprite sprite_hero;
    sf::Sprite sprite_food;
    sf::Sprite small_snake_sprite;

    std::vector<sf::Sprite> life_bar(NUMBERSTATESLIFEBAR);
    std::vector<sf::Sprite> sprite_small_snakes_arr;
    std::vector<int> sprite_small_snakes_type;
    // std::vector<sf::Sprite> sprite_barrel_snake_arr(10);

    SmallSnakesMoves small_snakes_moves;

    sf::Sprite background_draw;
    sf::Sprite background_errors_draw;
    //---------------------init textures and sprites---------------------

    //---------------------loaders textures + smooth---------------------
    snake.LoadTexturesFromFile(textures);
    snake.SmoothTextures(textures);

    food.LoadTexturesFromFile(textures);
    food.SmoothTextures(textures);    

    // barrel_snake.LoadTexturesFromFile(textures);
    // barrel_snake.SmoothTextures(textures);

    life_bar_i.LoadTexturesFromFile(textures);
    life_bar_i.SmoothTextures(textures);

    background.LoadTexturesFromFile(textures);
    background.SmoothTextures(textures);

    background_errors.LoadTexturesFromFile(textures);
    background_errors.SmoothTextures(textures);
    //---------------------loaders textures + smooth---------------------

    //---------------------loaders sprites---------------------
    hero.LoadHeroSprite(sprite_hero, textures);

    food_s.InitSizes(textures.background.getSize().x, textures.background.getSize().y);
    food_s.LoadFoodSprite(sprite_food, textures);

    // barrel_snake_s.LoadHeroSprite(sprite_barrel_snake_arr, textures);
    // barrel_snake_s.SetPositionBarrelSprite(sprite_barrel_snake_arr);

    life_bar_s.LoadHeroSprite(life_bar, textures);

    background_s.LoadHeroSprites(background_draw, textures);
    background_errors_s.LoadHeroSprites(background_errors_draw, textures);
    //---------------------loaders sprites---------------------

    //---------------------init Direction---------------------
    Direction currentDirection = None;
    unsigned long current_frame = 0;
    bool last_dir_left = false;

    float followerSpeed = 2.0f; // speed slowly small snakes, while they before main snake
    //---------------------init Direction---------------------

    //---------------------init constants and bools---------------------
    int eaten_food = 0;
    int currency_food = 50;
    bool food_enough = false;

    bool loading_texture = false;

    bool game_over = false;

    int increased_time_life = 6;
    float increased_score = 1.0f;
    //---------------------init constants and bools---------------------

    //---------------------init constants and bools---------------------
    int score = 0;

    sf::Clock game_timer;

    int life_bar_index = 0;
    int switch_life_bar = 150;
    int current_frame_lifebar = 0;
    //---------------------init constants and bools---------------------

    //---------------------init View---------------------
    sf::Vector2u textureSize = textures.background.getSize();
    sf::View view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
    view.setCenter(2006, 1128);
    window.setView(view);
    //---------------------init View---------------------

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

        //---------------------Move Small Snakes---------------------
        for (size_t i{0}; i < sprite_small_snakes_type.size(); ++i) {
            bool isFollower1Ahead = (small_snakes_moves.distance(sprite_hero, sprite_small_snakes_arr[i]));
            bool isFollower2Ahead = !isFollower1Ahead;

            for (size_t j = 0; j < sprite_small_snakes_type.size(); ++j) {
                if (i != j && sprite_small_snakes_arr[i].getGlobalBounds().intersects(sprite_small_snakes_arr[j].getGlobalBounds())) {
                    sf::Vector2f direction = sprite_small_snakes_arr[i].getPosition() - sprite_small_snakes_arr[j].getPosition();
                    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
                    if (distance != 0) {
                        direction /= distance;
                        sprite_small_snakes_arr[i].move(direction * 1.0f);
                    }
                }
            }

            if (isFollower1Ahead) {
                if (sprite_small_snakes_type[i] == GREENSNAKE) {
                    sprite_small_snakes_arr[i].move((sprite_hero.getPosition().x - sprite_small_snakes_arr[i].getPosition().x) / 50.0f * followerSpeed,
                        (sprite_hero.getPosition().y - sprite_small_snakes_arr[i].getPosition().y) / 50.0f * followerSpeed);
                }
                else if (sprite_small_snakes_type[i] == PINKSNAKE) {
                    sprite_small_snakes_arr[i].move((sprite_hero.getPosition().x - sprite_small_snakes_arr[i].getPosition().x) / 75.0f * followerSpeed,
                        (sprite_hero.getPosition().y - sprite_small_snakes_arr[i].getPosition().y) / 75.0f * followerSpeed);
                }
                else if (sprite_small_snakes_type[i] == PHARAONSNAKE) {
                    sprite_small_snakes_arr[i].move((sprite_hero.getPosition().x - sprite_small_snakes_arr[i].getPosition().x) / 100.0f * followerSpeed,
                        (sprite_hero.getPosition().y - sprite_small_snakes_arr[i].getPosition().y) / 100.0f * followerSpeed);
                }
            }
            else {
                sprite_small_snakes_arr[i].move((sprite_hero.getPosition().x - sprite_small_snakes_arr[i].getPosition().x) * followerSpeed,
                    (sprite_hero.getPosition().y - sprite_small_snakes_arr[i].getPosition().y) * followerSpeed);
            }
        }
        //---------------------Move Small Snakes---------------------

        //---------------------Animation Objects with diffrent sides---------------------
        if(last_dir_left) {
            if(current_frame % 4 == 0) 
                hero.CircleSpritesA(sprite_hero);

            for(int i{0}; i < sprite_small_snakes_type.size(); ++i) {
                if(sprite_small_snakes_type[i] == GREENSNAKE) {
                    if(current_frame % 4 == 0)
                        animate_sprite_green_snakes.CircleSpritesA(sprite_small_snakes_arr[i]);
                } else if(sprite_small_snakes_type[i] == PINKSNAKE) {
                    if(current_frame % 11 == 0)
                        animate_sprite_pink_snakes.CircleSpritesA(sprite_small_snakes_arr[i]);
                } else if(sprite_small_snakes_type[i] == PHARAONSNAKE) {
                    if(current_frame % 5 == 0)
                        animate_sprite_pharaon_snakes.CircleSpritesA(sprite_small_snakes_arr[i]);
                }
            }

        } else if(!last_dir_left) {
            if(current_frame % 4 == 0)
                hero.CircleSpritesD(sprite_hero);

            for(int i{0}; i < sprite_small_snakes_type.size(); ++i) {
                if(sprite_small_snakes_type[i] == GREENSNAKE) {
                    if(current_frame % 4 == 0)
                        animate_sprite_green_snakes.CircleSpritesD(sprite_small_snakes_arr[i]);
                } else if(sprite_small_snakes_type[i] == PINKSNAKE) {
                    if(current_frame % 11 == 0)
                        animate_sprite_pink_snakes.CircleSpritesD(sprite_small_snakes_arr[i]);
                } else if(sprite_small_snakes_type[i] == PHARAONSNAKE) {
                    if(current_frame % 5 == 0)
                        animate_sprite_pharaon_snakes.CircleSpritesD(sprite_small_snakes_arr[i]);
                }
            }

        }
        //---------------------Animation Objects with diffrent sides---------------------

        //---------------------Animation Objects with static sides---------------------
        // if(current_frame % 5 == 0) {
        //     for(size_t i{0}; i < NUMBEROFBARRELS; ++i) {
        //         barrel_snake_s.CheckDistanceSprite(sprite_hero, sprite_barrel_snake_arr[i], barrel_snake_s.animation_states[i]);
        //     }
        // }
        //---------------------Animation Objects with static sides---------------------

        //---------------------Collision hero with food---------------------
        if(food_s.CheckCollision(sprite_hero, sprite_food)) {
            food_s.LoadFoodSprite(sprite_food, textures);

            ++eaten_food;
            life_bar_index = 0;

            score += std::round(currency_food * increased_score);

            ((eaten_food % 4 == 0) && (eaten_food != 0)) ? food_enough = true : food_enough; // change here
        }
        //---------------------Collision hero with food---------------------

        //---------------------Adding small random snake---------------------
        SmallSnakes small_snake_texture;
        if(!loading_texture) {
            small_snake_texture.LoadTexturesFromFile(textures);
            loading_texture = true;
        }
        if(food_enough) {
            sf::Sprite temp_sprite;

            int random_choice = SmallSnakesSpritesClass::RandomChoseSnake();
            if(random_choice >= 0 && random_choice < 7) {
                SmallGreenSnakeSprite small_snake_current;
                small_snake_current.LoadHeroSprite(temp_sprite, textures);
                small_snake_current.SetPosition(sprite_hero, temp_sprite);

                sprite_small_snakes_arr.push_back(temp_sprite);
                sprite_small_snakes_type.push_back(GREENSNAKE);
            } else if(random_choice >= 7 && random_choice < 10) {
                SmallPinkSnakeSprite small_snake_current;
                small_snake_current.LoadHeroSprite(temp_sprite, textures);
                small_snake_current.SetPosition(sprite_hero, temp_sprite);

                sprite_small_snakes_arr.push_back(temp_sprite);
                sprite_small_snakes_type.push_back(PINKSNAKE);

                switch_life_bar += increased_time_life;
            } else if(random_choice == 10) {
                SmallPharaonSnakeSprite small_snake_current;
                small_snake_current.LoadHeroSprite(temp_sprite, textures);
                small_snake_current.SetPosition(sprite_hero, temp_sprite);

                sprite_small_snakes_arr.push_back(temp_sprite);
                sprite_small_snakes_type.push_back(PHARAONSNAKE);

                increased_score += 0.1f;
            }
            food_enough = false;
        }
        //---------------------Adding small random snake---------------------

        //---------------------Update Health Bar and Score---------------------
        score_text.setString("Score: " + std::to_string(score));
        life_text.setString("Life timer:");

        sf::Time elapsed_time =  game_timer.getElapsedTime();

        int minutes = static_cast<int>(elapsed_time.asSeconds()) / 60;
        int seconds = static_cast<int>(elapsed_time.asSeconds()) % 60;

        std::string time_string = (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":" +
                                 (seconds < 10 ? "0" : "") + std::to_string(seconds);


        time_text.setString(time_string);
        //---------------------Update Health Bar and Score---------------------

        //---------------------Decreased time alive---------------------
        if(current_frame % 3600 == 0 && current_frame != 0) {
            switch_life_bar = std::round(switch_life_bar * 0.7);
        }
        //---------------------Decreased time alive---------------------

        //---------------------View Square character---------------------
        sf::Vector2f pos_hero = sprite_hero.getPosition();
        sf::Vector2f size_hero(sprite_hero.getGlobalBounds().width, sprite_hero.getGlobalBounds().height);

        sf::FloatRect viewport_rect(pos_hero.x, pos_hero.y, size_hero.x + 20, size_hero.y + 20);

        if (!viewport_rect.contains(view.getCenter())) {
            sf::Vector2f pos_target(pos_hero.x, pos_hero.y);
            sf::Vector2f pos_current = view.getCenter();
            sf::Vector2f pos_new = sf::Vector2f(
                lerp(pos_current.x, pos_target.x, 0.07f),
                lerp(pos_current.y, pos_target.y, 0.07f));
            view.setCenter(pos_new);
            window.setView(view);
        }
        //---------------------View Square character---------------------

        //---------------------Game over shit code---------------------
        if(current_frame > 60) {
            if(sprite_hero.getGlobalBounds().intersects(background_errors_draw.getGlobalBounds())) {
                if(!sprite_hero.getGlobalBounds().intersects(background_draw.getGlobalBounds())) {
                    game_over = true;
                }
            }
        }            
        //---------------------Draw objects---------------------

        //---------------------Draw objects---------------------
        window.clear();
        window.draw(background_errors_draw);
        window.draw(background_draw);

        window.draw(sprite_food);
        if(!sprite_small_snakes_arr.empty()) {
            for(auto& small_snakes_iter: sprite_small_snakes_arr) {
                window.draw(small_snakes_iter);    
            }
        }
        window.draw(sprite_hero);

        // for(auto& barrel_snake_iter: sprite_barrel_snake_arr) {
        //     window.draw(barrel_snake_iter);
        // }
        //---------------------Draw objects---------------------

        //---------------------Draw interface---------------------
        sf::Vector2u window_size = window.getSize();
        score_text.setPosition(view.getCenter().x + window_size.x / 2 - 180, view.getCenter().y - window_size.y / 2 + 20);
        life_text.setPosition(view.getCenter().x - window_size.x / 2 + 20, view.getCenter().y - window_size.y / 2 + 20);
        time_text.setPosition(view.getCenter().x - time_text.getGlobalBounds().width / 2, view.getCenter().y - window_size.y / 2 + 10);
        darken_rect.setSize(sf::Vector2f(window_size.x, score_text.getGlobalBounds().height + 60));
        darken_rect.setPosition(view.getCenter().x - window_size.x / 2, view.getCenter().y - window_size.y / 2);

        window.draw(darken_rect);
        window.draw(life_text);
        window.draw(score_text);
        window.draw(time_text);

        life_bar_s.SetPositionLifebarSprite(life_bar, view);

        current_frame_lifebar = current_frame % (switch_life_bar + 1);
        if(current_frame_lifebar < switch_life_bar) {
            window.draw(life_bar[life_bar_index]);
        } else if(current_frame_lifebar == switch_life_bar) {
            life_bar_index += 1;
        } if (life_bar_index == NUMBERSTATESLIFEBAR) {
            game_over = true;
        }
        //---------------------Draw interface---------------------

        //---------------------Draw Gameover---------------------
        if(game_over) {
            sf::Font font;
            if (!font.loadFromFile("../../assets/fonts/Klyakson.otf"));
            sf::Text game_over_text("GAME OVER", font, 200);
            game_over_text.setPosition(view.getCenter().x - game_over_text.getGlobalBounds().width / 2,
                                    view.getCenter().y - game_over_text.getGlobalBounds().height / 2 - 200);
            game_over_text.setFillColor(sf::Color::Red);

            sf::Text exit_text("Exit", font, 80);
            exit_text.setPosition(view.getCenter().x  - exit_text.getGlobalBounds().width / 2,
                                    view.getCenter().y + 310);
            exit_text.setFillColor(sf::Color::White);

            sf::Text restart_text("Restart Game", font, 100);
            restart_text.setPosition(view.getCenter().x - restart_text.getGlobalBounds().width / 2,
                                        view.getCenter().y + 170);
            restart_text.setFillColor(sf::Color::White);

            sf::RectangleShape overlay;
            overlay.setSize(sf::Vector2f(view.getCenter().x, view.getCenter().y));
            overlay.setFillColor(sf::Color(0, 0, 0, 100));

            bool choice_made = false;
            while (!choice_made) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                    }
                    else if (event.type == sf::Event::MouseButtonPressed) {
                        sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                        if (exit_text.getGlobalBounds().contains(mouse_position) && event.mouseButton.button == sf::Mouse::Left) {
                            current_state =  GameState::Exit;
                            return;
                            choice_made = true;
                        } else if (restart_text.getGlobalBounds().contains(mouse_position) && event.mouseButton.button == sf::Mouse::Left) {
                            return;
                            choice_made = true;
                        }
                    }
                }

                window.clear(sf::Color(0, 0, 0, 200));
                window.draw(game_over_text);
                window.draw(exit_text);
                window.draw(restart_text);
                window.display();         
                }
        }
        //---------------------Draw Gameover---------------------

        ++current_frame;

        window.display();
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
