#pragma once
#include "BaseElement.h"
#include "Planet.h" // pt. observer
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>

class Rocket : public BaseElement {
private:
    sf::Vector2f pos; // Grafica
    sf::SoundBuffer buffer;
    sf::Sound sound;
    bool isActive;
    bool isDragged;
    std::vector<Planet*> observers; 

public:
    Rocket(sf::Vector2f position, const std::string& textureFile, const std::string& soundFile);
    void update(float dt, const sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;
    bool contains(sf::Vector2f point) override;
    void toggleActive();
    bool getActive() const { return isActive; }
    void setDragged(bool dragged) { isDragged = dragged; }
    void attach(Planet* planet);
    void detach(Planet* planet);
    void notifyObservers();
};