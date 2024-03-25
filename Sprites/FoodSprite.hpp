#include <random>
#include <utility>

#include "SFML/Graphics.hpp"

class FoodSprites {
    public:
    void InitSizes(int x, int y) {
        x_size = x;
        y_size = y;
    }

    void LoadFoodSprite(sf::Sprite& sprite, Textures& textures) {
        sprite.setTexture(textures.food);
        sf::IntRect textureRect(POSX + RandomSprite().first * SIZESPRITES, POSY + RandomSprite().second * SIZESPRITES, SIZESPRITES, SIZESPRITES);
        sprite.setTextureRect(textureRect);

        sprite.setPosition(RandomSprite(x_size, y_size).first, RandomSprite(x_size, y_size).second);
    }

    std::pair<int, int> RandomSprite() {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<int> dist_x(0, 6);
        std::uniform_int_distribution<int> dist_y(0, 7);

        return std::make_pair(dist_x(gen), dist_y(gen));
    }

    std::pair<int, int> RandomSprite(int x, int y) {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<int> dist_x(0, x - 100);
        std::uniform_int_distribution<int> dist_y(0, y - 100);

        return std::make_pair(dist_x(gen), dist_y(gen));
    }

    bool CheckCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2) {
        return sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds());
    }

    private:
    int POSX = 0, POSY = 0, SIZESPRITES = 65, startPosX = 500, startPosY = 500, POSXMAX = 394, POSYMAX = 455;
    int randx = 0, randy = 0;
    int x_size = 0, y_size = 0;
};