#pragma once
#include "BaseElement.h"
#include "Planet.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>

class UFO : public BaseElement {
private:
    sf::Vector2f pos;
    sf::SoundBuffer buffer;
    sf::Sound sound;
    bool isSlowed;
    bool isDragged; 
    std::vector<Planet*> observers;

public:
    UFO(sf::Vector2f position, const std::string& soundFile);
    void update(float dt, const sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;
    bool contains(sf::Vector2f point) override;
    void setDragged(bool dragged) override;
    void attach(Planet* p);
    void toggleSlow();
};