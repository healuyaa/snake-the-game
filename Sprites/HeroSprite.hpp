#include "SFML/Graphics.hpp"

struct RectHero {
    sf::IntRect rect_d;
    sf::IntRect rect_a;
};

class HeroMoving {
    public:

    void LoadHeroSprite(sf::Sprite& sprite, Textures& textures) {
        sprite.setTexture(textures.snake_mooves);
        sf::IntRect textureRect(POSDX, POSDY, SIZESPRITES, SIZESPRITES);
        sprite.setTextureRect(textureRect);

        sprite.setPosition(startPosX, startPosY);
    }

    void InitsRects(RectHero& rects) {
        rects.rect_d = sf::IntRect(POSDX + iter_sprites_d * SIZESPRITES, POSDY, SIZESPRITES, SIZESPRITES);
        rects.rect_a = sf::IntRect(POSAX - iter_sprites_a * SIZESPRITES, POSAY, SIZESPRITES, SIZESPRITES);
    }

    void ChangeSprite(sf::Sprite& sprite, const sf::IntRect& rect) {
        sprite.setTextureRect(rect);
    }

    void CircleSpritesA(sf::Sprite& sprite) {
        if(iter_sprites_a == MAXEQUAL)
            iter_sprites_a = 0;

        sprite.setTextureRect(sf::IntRect(POSAX - iter_sprites_a * SIZESPRITES, 
                                            POSAY, SIZESPRITES, SIZESPRITES));
        ++iter_sprites_a;
    }

    void CircleSpritesD(sf::Sprite& sprite) {
        if(iter_sprites_d == MAXEQUAL)
            iter_sprites_d = 0;

        sprite.setTextureRect(sf::IntRect(POSDX + iter_sprites_d * SIZESPRITES, 
                                            POSDY, SIZESPRITES, SIZESPRITES));
        ++iter_sprites_d;
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
    int POSDX = 0, POSDY = 160, POSAX = 880, POSAY = 320, SIZESPRITES = 80, startPosX = 500, startPosY = 500, MAXEQUAL = 12;
    int iter_sprites_a = 0, iter_sprites_d = 0;
};