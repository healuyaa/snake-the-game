#include "SFML/Graphics.hpp"

class LifeBarClass {
    public:
    void LoadHeroSprite(std::vector<sf::Sprite>& sprites, Textures& texture) {
        for(int i{0}; i < NUMBERSTATESLIFEBAR; ++i) {
            sprites[i].setTexture(texture.life_bar_states[i]);
            sf::IntRect textureRect(0, 0, 378, 38);
            sprites[i].setTextureRect(textureRect);
        }
    }

    void SetPositionLifebarSprite(std::vector<sf::Sprite>& sprites, const sf::View& view) {
        sf::Vector2f windowSize = view.getSize();

        float offsetX = 165;
        float offsetY = 20; 

        for (size_t i = 0; i < NUMBERSTATESLIFEBAR; ++i) {
            sf::Vector2f newPosition = sf::Vector2f(view.getCenter().x - windowSize.x / 2 + offsetX, view.getCenter().y - windowSize.y / 2 + offsetY);
            sprites[i].setPosition(newPosition);
        }
    }

};