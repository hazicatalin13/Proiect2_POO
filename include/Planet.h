#pragma once
#include "BaseElement.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Planet : public BaseElement {
private:
    sf::CircleShape shape;
    sf::Vector2f pos;
    sf::Sound sound;
    bool isLooping;
    bool isDragged;
    float currentSpeed;

public:
    //  primeste referinta la Soundbuffer din template
    Planet(float radius, sf::Color color, sf::Vector2f position, const sf::SoundBuffer& sharedBuffer);
    void update(float dt, const sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;
    bool contains(sf::Vector2f point) override;
    void setDragged(bool dragged) override;
    void toggleLoop();
    void setPlaybackSpeed(float speed);
};