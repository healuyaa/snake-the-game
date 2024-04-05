#include "SFML/Graphics.hpp"

#define PINKSNAKE 1
#define GREENSNAKE 2
#define PHARAONSNAKE 3

class SmallSnakesSpritesClass {
    public:
    virtual void LoadHeroSprite(sf::Sprite& sprite, Textures& textures) = 0;    
    virtual void InitXYHero(int x, int y) = 0;

    int RandomChoseSnake() {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<int> index_snake(0, 10);
        // 0 - 3     ------------        pink
        // 4 - 9     ------------        green
        // 10        ------------        pharaon

        return index_snake(gen);
    }

    void MoveUp(sf::Sprite& sprite) {
        sprite.move(0, -5);
    }

    void MoveDown(sf::Sprite& sprite) {
        sprite.move(0, 5);
    }

    void MoveLeft(sf::Sprite& sprite) {
        sprite.move(-5, 0);
    }

    void MoveRight(sf::Sprite& sprite) {
        sprite.move(5, 0);
    }

    virtual void CircleSpritesA(sf::Sprite& sprite) = 0;
    virtual void CircleSpritesD(sf::Sprite& sprite) = 0;
};
class SmallPinkSnakeSprite : public SmallSnakesSpritesClass {
    public:
    void LoadHeroSprite(sf::Sprite& sprite, Textures& textures) override {
        sprite.setTexture(textures.small_pink_snake);
        sf::IntRect textureRect(POSDX, POSDY, SIZESPRITES, SIZESPRITES);
        sprite.setTextureRect(textureRect);

        sprite.setPosition(500.0, 500.0);
    }

    void InitXYHero(int x, int y) override {
        posx_hero = x;
        posy_hero = y;
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

        sprite.setPosition(700.0, 700.0);
    }

    void InitXYHero(int x, int y) override {
        posx_hero = x;
        posy_hero = y;
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
    int posx_hero, posy_hero;
};

class SmallPharaonSnakeSprite : public SmallSnakesSpritesClass {
    public:
    void LoadHeroSprite(sf::Sprite& sprite, Textures& textures) override {
        sprite.setTexture(textures.small_pharaon_snake);
        sf::IntRect textureRect(POSDX, POSDY, SIZESPRITESX, SIZESPRITESY);
        sprite.setTextureRect(textureRect);

        sprite.setPosition(300.0, 300.0);
    }

    void InitXYHero(int x, int y) override {
        posx_hero = x;
        posy_hero = y;
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
    int posx_hero, posy_hero;
};