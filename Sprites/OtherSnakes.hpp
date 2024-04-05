#include "SFML/Graphics.hpp"

class OtherBarelSnake {
    public:
    void LoadHeroSprite(sf::Sprite& sprite, Textures& textures) {
        sprite.setTexture(textures.barrel_snake);
        sf::IntRect textureRect(POSXSAB, POSYSAB, SIZESPRITESX, SIZESPRITESY);
        sprite.setTextureRect(textureRect);

        sprite.setPosition(700.0, 300.0);
    }

    void CircleSpritesAnimateSnake(sf::Sprite& sprite) {
        if(iter_sprites == MAXEQUAL) {
            iter_sprites = 1;
            return;
        }

        sprite.setTextureRect(sf::IntRect(POSXSAB + iter_sprites * SIZESPRITESX, 
                                            POSYSAB, SIZESPRITESX, SIZESPRITESY));
        ++iter_sprites;
    }

    void CircleSpritesSnakeHideBarrel(sf::Sprite& sprite) {
        if(iter_hide_barrel == 11) { // 11 sprites for hide snake
            iter_hide_barrel = 1;
            step_hide = true;
            return;
        }

        sprite.setTextureRect(sf::IntRect(POSXHS + iter_hide_barrel * SIZESPRITESX, 
                                            POSYHS, SIZESPRITESX, SIZESPRITESY));
        ++iter_hide_barrel;
    }

    void CircleSpritesBarrelAnimate(sf::Sprite& sprite) {
        if(iter_barrel == 8) { // 8 sprites for animate barrel
            iter_barrel = 1;
            step_unhide = true;
            return;
        }

        sprite.setTextureRect(sf::IntRect(POSXOB + iter_barrel * SIZESPRITESX, 
                                            POSYOB, SIZESPRITESX, SIZESPRITESY));
        ++iter_barrel;
    }

    void CircleSpritesSnakeUnhide(sf::Sprite& sprite) {
        if(iter_unhide_barrel == 4) { // 4 sprites for unhide barrel
            iter_unhide_barrel = 1;
            snake_is_hide = false;
            return;
        }

        sprite.setTextureRect(sf::IntRect(POSXUS + iter_unhide_barrel * SIZESPRITESX, 
                                            POSYUS, SIZESPRITESX, SIZESPRITESY));
        ++iter_unhide_barrel;
    }

    void CircleSpritesSnakeStatic(sf::Sprite& sprite) {
        sprite.setTextureRect(sf::IntRect(POSXOB, POSYOB, SIZESPRITESX, SIZESPRITESY));
    }

    void CheckDistanceSprite(sf::Sprite& sprite_snake_hero, sf::Sprite& sprite_barrel_snake) {
        float distance = std::sqrt(std::pow(sprite_snake_hero.getPosition().x - sprite_barrel_snake.getPosition().x, 2) +
                                std::pow(sprite_snake_hero.getPosition().y - sprite_barrel_snake.getPosition().y, 2));

        if (distance > 200) {
            if (snake_is_hide) {
                if (!step_unhide) {
                    CircleSpritesBarrelAnimate(sprite_barrel_snake);
                } else {
                    CircleSpritesSnakeUnhide(sprite_barrel_snake);
                }
                step_hide = false;
            } else {
                CircleSpritesAnimateSnake(sprite_barrel_snake);
            }
        } else {
            if (!step_hide) {
                CircleSpritesSnakeHideBarrel(sprite_barrel_snake);
            } else {
                CircleSpritesSnakeStatic(sprite_barrel_snake);
            }
            snake_is_hide = true;
            step_unhide = false;
        }
    }

    private:
    int SIZESPRITESX = 54, SIZESPRITESY = 66;
    int POSXSAB = 0, POSYSAB = 0, POSXHS = 0, POSYHS = 66, POSXOB = 270, POSYOB = 132, POSXUS = 0, POSYUS = 198;
    int iter_sprites = 1, MAXEQUAL = 13;
    int iter_hide_barrel = 1, iter_barrel = 1, iter_unhide_barrel = 1;
    int static_pos_x, static_pos_y;

    static bool snake_is_hide;
    static bool step_unhide;
    static bool step_hide;
};
bool OtherBarelSnake::snake_is_hide = false;
bool OtherBarelSnake::step_unhide = false;
bool OtherBarelSnake::step_hide = false;

// POSXSAB & POSYSAB - Pos X(Y) Snake and Barrel
// POSXHS & POSYHS - Pos X(Y) Hide Snake
// POSXOB & POSYOB - Pos X(Y) Only Barrel
// POSXUS & POSYUS - Pos X(Y) Unhide Snake