#include "../include/Planet.h"
#include <iostream>

Planet::Planet(float radius, sf::Color color, sf::Vector2f position, const sf::SoundBuffer& sharedBuffer)
    : shape(radius), 
      pos(position), 
      sound(sharedBuffer), 
      isLooping(false), 
      isDragged(false), 
      currentSpeed(1.0f) 
{
    sound.setLooping(true); 
    shape.setOrigin({radius, radius});
    shape.setPosition(pos);
    shape.setFillColor(color);
}



void Planet::update(float dt, const sf::RenderWindow& window) {
    if (isDragged) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        pos = window.mapPixelToCoords(mousePos);
        shape.setPosition(pos);
    }
}



void Planet::draw(sf::RenderWindow& window) {
    window.draw(shape);
}



bool Planet::contains(sf::Vector2f point) {
    float radius = shape.getRadius();
    float dx = pos.x - point.x;
    float dy = pos.y - point.y;
    return (dx * dx + dy * dy) < (radius * radius);
}



void Planet::setDragged(bool dragged) {
    isDragged = dragged;
}



void Planet::toggleLoop() {
    isLooping = !isLooping;
    if (isLooping) {
        sound.play();
        shape.setOutlineThickness(3.f);
        shape.setOutlineColor(sf::Color::White);
    } else {
        sound.stop();
        shape.setOutlineThickness(0.f);
    }
}



void Planet::setPlaybackSpeed(float speed) {
    currentSpeed = speed;
    sound.setPitch(currentSpeed);
}