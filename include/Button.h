#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Button {
private:
    sf::RectangleShape rect;
    sf::Text text;
    std::string type;

public:
    Button(sf::Vector2f pos, sf::Color color, std::string label, const sf::Font& font);
    
    void draw(sf::RenderWindow& window);
    bool isClicked(sf::Vector2f mousePos);
    std::string getType() const;
};