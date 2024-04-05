#include <iostream>

#include "SFML/Graphics.hpp"

struct Textures {
    sf::Texture github_icon;
    sf::Texture steam_icon;
    sf::Texture discord_icon;

    sf::Texture snake;
    
    sf::Texture food;

    sf::Texture small_pink_snake;
    sf::Texture small_green_snake;
    sf::Texture small_pharaon_snake;

    sf::Texture barrel_snake;
};

class ILoader {
    public:
    virtual void LoadTexturesFromFile(Textures &textures) = 0;
    virtual void SmoothTextures(Textures &textures) = 0;
};

class Icons : public ILoader {
    public:
    void LoadTexturesFromFile(Textures &textures) override {
        if (!textures.github_icon.loadFromFile(github_icon_path)) {
            std::cout << "Err load icon: github\n";
            return;
        }

        if (!textures.steam_icon.loadFromFile(steam_icon_path)) {
            std::cout << "Err load icon: steam\n";
            return;
        }

        if (!textures.discord_icon.loadFromFile(discord_icon_path)) {
            std::cout << "Err load icon: discord\n";
            return;
        }
    }

    void SmoothTextures(Textures &textures) override {
        textures.github_icon.setSmooth(true);
        textures.steam_icon.setSmooth(true);
        textures.discord_icon.setSmooth(true);
    }

    private:
    std::string github_icon_path = "../../assets/icons/github25.png";
    std::string steam_icon_path = "../../assets/icons/steam25.png";
    std::string discord_icon_path = "../../assets/icons/discord25.png";
};

class Snake : public ILoader {
    public:
    void LoadTexturesFromFile(Textures& textures) override {
        if(!textures.snake.loadFromFile(snakes_path)) {
            std::cout << "Err load icon: snake_moove\n";
            return;
        }
    }

    void SmoothTextures(Textures &textures) override {
        textures.snake.setSmooth(true);
    }

    private:
    std::string snakes_path = "../../assets/snakes/snake-hero.png";
};

class Food : public ILoader {
    public:

    void LoadTexturesFromFile(Textures& textures) override {
        if(!textures.food.loadFromFile(food_path)) {
            std::cout << "Err load icon: food\n";
            return;
        }
    }

    void SmoothTextures(Textures &textures) override {
        textures.food.setSmooth(true);
    }

    private:
    std::string food_path = "../../assets/food/food.png";
};

class SmallSnakes : public ILoader {
    public:
    void LoadTexturesFromFile(Textures& textures) override {
        if(!textures.small_pink_snake.loadFromFile(small_pink_snake_path)) {
            std::cout << "Err load icon: small_pink_snake\n";
            return;
        }

        if(!textures.small_green_snake.loadFromFile(small_green_snake_path)) {
            std::cout << "Err load icon: small_green_snake\n";
            return;
        }

        if(!textures.small_pharaon_snake.loadFromFile(small_pharaon_snake_path)) {
            std::cout << "Err load icon: small_pharaon_snake\n";
            return;
        }
    }

    void SmoothTextures(Textures& textures) override {
        textures.small_pink_snake.setSmooth(true);
        textures.small_green_snake.setSmooth(true);
        textures.small_pharaon_snake.setSmooth(true);
    }

    private:
    std::string small_pink_snake_path = "../../assets/snakes/pink-small-snake.png";
    std::string small_green_snake_path = "../../assets/snakes/green-small-snake.png";
    std::string small_pharaon_snake_path = "../../assets/snakes/snake-paharaon.png";
};

class OtherSnake : public ILoader{
    public:
    void LoadTexturesFromFile(Textures& textures) override {
        if(!textures.barrel_snake.loadFromFile(barrel_snake_path)) {
            std::cout << "Err load icon: barrel_snake\n";
            return;
        }
    }

    void SmoothTextures(Textures& textures) override {
        textures.barrel_snake.setSmooth(true);
    }

    private:
    std::string barrel_snake_path = "../../assets/snakes/barrel-snake.png";
};