#include <unordered_map>
#include <vector>
#include "SFML/Graphics.hpp"
struct PositionBarrelSnakes{
    static std::unordered_map<std::string, sf::Vector2f> positions;
};
std::unordered_map<std::string, sf::Vector2f> PositionBarrelSnakes::positions = {
        {"sprite1", sf::Vector2f(0.0f, 0.0f)},
        {"sprite2", sf::Vector2f(200.0f, 100.0f)},
        {"sprite3", sf::Vector2f(400.0f, 200.0f)},
        {"sprite4", sf::Vector2f(600.0f, 300.0f)},
        {"sprite5", sf::Vector2f(800.0f, 400.0f)},
        {"sprite6", sf::Vector2f(1000.0f, 500.0f)},
        {"sprite7", sf::Vector2f(1200.0f, 600.0f)},
        {"sprite8", sf::Vector2f(1400.0f, 700.0f)},
        {"sprite9", sf::Vector2f(1600.0f, 800.0f)},
        {"sprite10", sf::Vector2f(1800.0f, 1000.0f)}
    };
class OtherBarelSnake {
    public:
    struct SpriteAnimationState {
        int iter_sprites = 1;
        int iter_hide_barrel = 1;
        int iter_barrel = 1;
        int iter_unhide_barrel = 1;
        bool snake_is_hide = false;
        bool step_unhide = false;
        bool step_hide = false;
    };
    std::vector<SpriteAnimationState> animation_states;

    void LoadHeroSprite(std::vector<sf::Sprite>& sprite, Textures& textures) {
        for(size_t i{0}; i < 10; ++i) {
            sprite[i].setTexture(textures.barrels09[i]);
            sf::IntRect textureRect(POSXSAB, POSYSAB, SIZESPRITESX, SIZESPRITESY);
            sprite[i].setTextureRect(textureRect);

            animation_states.push_back(SpriteAnimationState());
        }
    }

    void SetPositionBarrelSprite(std::vector<sf::Sprite>& sprites) {
        for(size_t i{0}; i < 10; ++i) {
            sprites[i].setPosition(PositionBarrelSnakes::positions["sprite" + std::to_string(i + 1)]);
        }
    }

    void CheckDistanceSprite(sf::Sprite& sprite_snake_hero, sf::Sprite& sprite_barrel_snake, SpriteAnimationState& state) {
        float distance = std::sqrt(std::pow(sprite_snake_hero.getPosition().x - sprite_barrel_snake.getPosition().x, 2) +
                                   std::pow(sprite_snake_hero.getPosition().y - sprite_barrel_snake.getPosition().y, 2));

        if (distance > 200) {
            if (state.snake_is_hide) {
                if (!state.step_unhide) {
                    CircleSpritesBarrelAnimate(sprite_barrel_snake, state);
                } else {
                    CircleSpritesSnakeUnhide(sprite_barrel_snake, state);
                }
                state.step_hide = false;
            } else {
                CircleSpritesAnimateSnake(sprite_barrel_snake, state);
            }
        } else {
            if (!state.step_hide) {
                CircleSpritesSnakeHideBarrel(sprite_barrel_snake, state);
            } else {
                CircleSpritesSnakeStatic(sprite_barrel_snake, state);
            }
            state.snake_is_hide = true;
            state.step_unhide = false;
        }
    }

    private:
    int SIZESPRITESX = 54, SIZESPRITESY = 66;
    int POSXSAB = 0, POSYSAB = 0, POSXHS = 0, POSYHS = 66, POSXOB = 270, POSYOB = 132, POSXUS = 0, POSYUS = 198;
    int MAXEQUAL = 13;

    void CircleSpritesAnimateSnake(sf::Sprite& sprite, SpriteAnimationState& state) {
        if (state.iter_sprites == MAXEQUAL) {
            state.iter_sprites = 1;
            return;
        }

        sprite.setTextureRect(sf::IntRect(POSXSAB + state.iter_sprites * SIZESPRITESX, POSYSAB, SIZESPRITESX, SIZESPRITESY));
        ++state.iter_sprites;
    }

    void CircleSpritesSnakeHideBarrel(sf::Sprite& sprite, SpriteAnimationState& state) {
        if (state.iter_hide_barrel == 11) { // 11 sprites for hide snake
            state.iter_hide_barrel = 1;
            state.step_hide = true;
            return;
        }

        sprite.setTextureRect(sf::IntRect(POSXHS + state.iter_hide_barrel * SIZESPRITESX, POSYHS, SIZESPRITESX, SIZESPRITESY));
        ++state.iter_hide_barrel;
    }

    void CircleSpritesBarrelAnimate(sf::Sprite& sprite, SpriteAnimationState& state) {
        if (state.iter_barrel == 8) { // 8 sprites for animate barrel
            state.iter_barrel = 1;
            state.step_unhide = true;
            return;
        }

        sprite.setTextureRect(sf::IntRect(POSXOB + state.iter_barrel * SIZESPRITESX, POSYOB, SIZESPRITESX, SIZESPRITESY));
        ++state.iter_barrel;
    }

    void CircleSpritesSnakeUnhide(sf::Sprite& sprite, SpriteAnimationState& state) {
        if (state.iter_unhide_barrel == 4) { // 4 sprites for unhide barrel
            state.iter_unhide_barrel = 1;
            state.snake_is_hide = false;
            return;
        }

        sprite.setTextureRect(sf::IntRect(POSXUS + state.iter_unhide_barrel * SIZESPRITESX, POSYUS, SIZESPRITESX, SIZESPRITESY));
        ++state.iter_unhide_barrel;
    }

    void CircleSpritesSnakeStatic(sf::Sprite& sprite, SpriteAnimationState& state) {
        sprite.setTextureRect(sf::IntRect(POSXOB, POSYOB, SIZESPRITESX, SIZESPRITESY));
    }
};

// POSXSAB & POSYSAB - Pos X(Y) Snake and Barrel
// POSXHS & POSYHS - Pos X(Y) Hide Snake
// POSXOB & POSYOB - Pos X(Y) Only Barrel
// POSXUS & POSYUS - Pos X(Y) Unhide Snake