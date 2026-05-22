#pragma once
#include <SFML/Graphics.hpp>


//clasa abstracta

class BaseElement{
    public:
    virtual ~BaseElement() = default;
    virtual void update(float deltaTime, const sf::RenderWindow& window) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    
    // Verificam daca mouse-ul atinge obiectul
    virtual bool contains(sf::Vector2f point) = 0;
    virtual void setDragged(bool dragged) = 0; 
};