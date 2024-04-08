#include "SFML/Graphics.hpp"

class BackgroundClass {
    public:
    void LoadHeroSprites(sf::Sprite& sprite, Textures& texture) {
        sprite.setTexture(texture.background);
        sf::IntRect textureRect(0, 0, 4012, 2257);
        sprite.setPosition(0, 0);
    }
};

class BackgroundErrorsClass {
    public:
    void LoadHeroSprites(sf::Sprite& sprite, Textures& texture) {
        sprite.setTexture(texture.background_errors);
        sf::IntRect textureRect(0, 0, 5000, 3000);
        sprite.setPosition(-500, -400);
    }
};