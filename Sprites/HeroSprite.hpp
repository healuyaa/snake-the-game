#include "SFML/Graphics.hpp"

class HeroSprite {
    public:

    void LoadHeroSprite(sf::Sprite& sprite, Textures& textures) {
        sprite.setTexture(textures.snake);
        sf::IntRect textureRect(POSDX, POSDY, SIZESPRITES, SIZESPRITES);
        sprite.setTextureRect(textureRect);
        sprite.setScale(1.2f, 1.2f);

        sprite.setPosition(startPosX, startPosY);
    }

    void CircleSpritesA(sf::Sprite& sprite) {
        if(iter_sprites == MAXEQUAL)
            iter_sprites = 1;

        sprite.setTextureRect(sf::IntRect(POSAX - iter_sprites * SIZESPRITES, 
                                            POSAY, SIZESPRITES, SIZESPRITES));
        ++iter_sprites;
    }

    void CircleSpritesD(sf::Sprite& sprite) {
        if(iter_sprites == MAXEQUAL)
            iter_sprites = 1;

        sprite.setTextureRect(sf::IntRect(POSDX + iter_sprites * SIZESPRITES, 
                                            POSDY, SIZESPRITES, SIZESPRITES));
        ++iter_sprites;
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

    private:
    int POSDX = 0, POSDY = 160, POSAX = 880, POSAY = 320, SIZESPRITES = 80, startPosX = 2006, startPosY = 1128, MAXEQUAL = 12;
    int iter_sprites = 1;
};