#include <vector>
#include "SFML/Graphics.hpp"

#define NUMBEROFBARRELS 10
#define NUMBERSTATESLIFEBAR 11

struct Textures {
    sf::Texture github_icon;
    sf::Texture steam_icon;
    sf::Texture discord_icon;

    sf::Texture snake;
    
    sf::Texture food;

    sf::Texture small_pink_snake;
    sf::Texture small_green_snake;
    sf::Texture small_pharaon_snake;

    std::vector<sf::Texture> barrels09;

    std::vector<sf::Texture> life_bar_states;

    sf::Texture background;
    sf::Texture background_errors;
};

class ILoader {
    public:
    virtual void LoadTexturesFromFile(Textures &textures) = 0;
    virtual void SmoothTextures(Textures &textures) = 0;
};

class Icons : public ILoader {
    public:
    void LoadTexturesFromFile(Textures &textures) override {
        if (!textures.github_icon.loadFromFile(github_icon_path))
            return;

        if (!textures.steam_icon.loadFromFile(steam_icon_path))
            return;

        if (!textures.discord_icon.loadFromFile(discord_icon_path))
            return;
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
        if(!textures.snake.loadFromFile(snakes_path))
            return;
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
        if(!textures.food.loadFromFile(food_path))
            return;
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
        if(!textures.small_pink_snake.loadFromFile(small_pink_snake_path))
            return;

        if(!textures.small_green_snake.loadFromFile(small_green_snake_path))
            return;

        if(!textures.small_pharaon_snake.loadFromFile(small_pharaon_snake_path))
            return;
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

class OtherSnake : public ILoader {
    public:
    void LoadTexturesFromFile(Textures& textures) override {
        size_t i = 0;
        while(i < NUMBEROFBARRELS) {
            sf::Texture temp;
            temp.loadFromFile(barrel_snake_path);
            textures.barrels09.push_back(temp);
            ++i;
        }
    }

    void SmoothTextures(Textures& textures) override {
        for(size_t i{0}; i < NUMBEROFBARRELS; ++i) {
            textures.barrels09[i].setSmooth(true);
        }
    }

    private:
    std::string barrel_snake_path = "../../assets/snakes/barrel-snake.png";
};

class LifeBar : public ILoader {
    public:
    void LoadTexturesFromFile(Textures& textures) override {
        for(size_t i{0}; i < NUMBERSTATESLIFEBAR; ++i) {
            sf::Texture temp;
            temp.loadFromFile(lifebar_path + std::to_string(NUMBERSTATESLIFEBAR - i - 1) + ".png");
            textures.life_bar_states.push_back(temp);
        }
    }

    void SmoothTextures(Textures& textures) override {
        for(auto& lifebar_iter: textures.life_bar_states) {
            lifebar_iter.setSmooth(true);
        }
    }

    private:
    std::string lifebar_path = "../../assets/lifebar/VIDA_";
};

class Background : public ILoader {
    public:
    void LoadTexturesFromFile(Textures& textures) override {
        if(!textures.background.loadFromFile(background_path))
            return;
    }

    void SmoothTextures(Textures& textures) override {
        textures.background.setSmooth(true);
    }

    private:
    std::string background_path = "../../assets/background/background.jpg";
};

class BackgroundErrors : public ILoader {
    public:
    void LoadTexturesFromFile(Textures& textures) override {
        if(!textures.background_errors.loadFromFile(background_path))
            return;
    }

    void SmoothTextures(Textures& textures) override {
        textures.background_errors.setSmooth(true);
    }

    private:
    std::string background_path = "../../assets/background/background-errors.png";
};