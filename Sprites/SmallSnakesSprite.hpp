#include <random>
#include <utility>
#include "SFML/Graphics.hpp"

#define GREENSNAKE 1
#define PINKSNAKE 2
#define PHARAONSNAKE 3

class SmallSnakesSpritesClass {
    public:
    virtual void LoadHeroSprite(sf::Sprite& sprite, Textures& textures) = 0;    

    static int RandomChoseSnake() {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<int> index_snake(0, 10);
        // 0 - 6     ------------        green
        // 7 - 9     ------------        pink
        // 10        ------------        pharaon

        return index_snake(gen);
    }

    virtual void CircleSpritesA(sf::Sprite& sprite) = 0;
    virtual void CircleSpritesD(sf::Sprite& sprite) = 0;
    virtual void SetPosition(sf::Sprite& sprite_hero, sf::Sprite& sprite) = 0;
};

class SmallPinkSnakeSprite : public SmallSnakesSpritesClass {
    public:
    void LoadHeroSprite(sf::Sprite& sprite, Textures& textures) override {
        sprite.setTexture(textures.small_pink_snake);
        sf::IntRect textureRect(POSDX, POSDY, SIZESPRITES, SIZESPRITES);
        sprite.setTextureRect(textureRect);
        sprite.setScale(0.8f, 0.8f);
    }

    void SetPosition(sf::Sprite& sprite_hero, sf::Sprite& sprite) override {
        sprite.setPosition(sf::Vector2f(sprite_hero.getPosition().x + 60.0, sprite_hero.getPosition().y));
    }

    void CircleSpritesA(sf::Sprite& sprite) override {
        if(iter_sprites == MAXEQUAL)
            iter_sprites = 1;

            sprite.setTextureRect(sf::IntRect(POSAX - iter_sprites * SIZESPRITES, 
                                                POSAY, SIZESPRITES, SIZESPRITES));
            ++iter_sprites;
    }

    void CircleSpritesD(sf::Sprite& sprite) override {
        if(iter_sprites == MAXEQUAL)
            iter_sprites = 1;

            sprite.setTextureRect(sf::IntRect(POSDX + iter_sprites * SIZESPRITES,
                                                POSDY, SIZESPRITES, SIZESPRITES));
            ++iter_sprites;
    }

    private:
    int POSDX = 0, POSDY = 138, POSAX = 260, POSAY = 73, SIZESPRITES = 65, MAXEQUAL = 4; 
    int iter_sprites = 1;
    int posx_hero, posy_hero;
};

class SmallGreenSnakeSprite : public SmallSnakesSpritesClass {
    public:
    void LoadHeroSprite(sf::Sprite& sprite, Textures& textures) override {
        sprite.setTexture(textures.small_green_snake);
        sf::IntRect textureRect(POSDX, POSDY, SIZESPRITES, SIZESPRITES);
        sprite.setTextureRect(textureRect);
        sprite.setScale(0.95f, 0.95f);
    }

    void SetPosition(sf::Sprite& sprite_hero, sf::Sprite& sprite) override {
        sprite.setPosition(sf::Vector2f(sprite_hero.getPosition().x + 35.0, sprite_hero.getPosition().y));
    }

    void CircleSpritesA(sf::Sprite& sprite) override {
        if(iter_sprites == MAXEQUAL)
            iter_sprites = 1;

        sprite.setTextureRect(sf::IntRect(POSAX - iter_sprites * SIZESPRITES, 
                                            POSAY, SIZESPRITES, SIZESPRITES));
        ++iter_sprites;
    }

    void CircleSpritesD(sf::Sprite& sprite) override {
        if(iter_sprites == MAXEQUAL)
            iter_sprites = 1;

        sprite.setTextureRect(sf::IntRect(POSDX + iter_sprites * SIZESPRITES, 
                                            POSDY, SIZESPRITES, SIZESPRITES));
        ++iter_sprites;
    }

    private:
    int POSDX = 0, POSDY = 0, POSAX = 880, POSAY = 80, SIZESPRITES = 80, MAXEQUAL = 11;
    int iter_sprites = 1;
};

class SmallPharaonSnakeSprite : public SmallSnakesSpritesClass {
    public:
    void LoadHeroSprite(sf::Sprite& sprite, Textures& textures) override {
        sprite.setTexture(textures.small_pharaon_snake);
        sf::IntRect textureRect(POSDX, POSDY, SIZESPRITESX, SIZESPRITESY);
        sprite.setTextureRect(textureRect);
        sprite.setScale(0.8f, 0.8f);
    }

    void SetPosition(sf::Sprite& sprite_hero, sf::Sprite& sprite) override {
        sprite.setPosition(sf::Vector2f(sprite_hero.getPosition().x + 75.0, sprite_hero.getPosition().y));
    }

    void CircleSpritesA(sf::Sprite& sprite) override {
        if(iter_sprites == MAXEQUAL)
            iter_sprites = 0;

        sprite.setTextureRect(sf::IntRect(POSAX + iter_sprites * SIZESPRITESX, 
                                            POSAY, SIZESPRITESX, SIZESPRITESY));
        ++iter_sprites;
    }

    void CircleSpritesD(sf::Sprite& sprite) override {
        if(iter_sprites == MAXEQUAL)
            iter_sprites = 0;

        sprite.setTextureRect(sf::IntRect(POSDX - iter_sprites * SIZESPRITESX, 
                                            POSDY, SIZESPRITESX, SIZESPRITESY));
        ++iter_sprites;
    }

    private:
    int POSDX = 1045, POSDY = 88, POSAX = 0, POSAY = 0, SIZESPRITESX = 95, SIZESPRITESY = 88, MAXEQUAL = 12;
    int iter_sprites = 0;
};

class SmallSnakesMoves {
    public:
    float distance(const sf::Sprite& sprite1, const sf::Sprite& sprite2) {
        sf::Vector2f pos1 = sprite1.getPosition();
        sf::Vector2f pos2 = sprite2.getPosition();
        float dx = pos1.x - pos2.x;
        float dy = pos1.y - pos2.y;
        return std::sqrt(dx * dx + dy * dy);
    }
};
