#include "../include/Button.h"

Button::Button(sf::Vector2f pos, sf::Color color, std::string label, const sf::Font& font) 
    : text(font, label), type(label) 
{
    rect.setPosition(pos);
    rect.setSize({100.f, 40.f});
    rect.setFillColor(color);

    text.setCharacterSize(14);
    text.setFillColor(sf::Color::White);
    text.setPosition({pos.x + 10, pos.y + 10});
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(rect);
    window.draw(text);
}

bool Button::isClicked(sf::Vector2f mousePos) {
    return rect.getGlobalBounds().contains(mousePos);
}

std::string Button::getType() const {
    return type;
}