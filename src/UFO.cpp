#include "../include/UFO.h"
#include <iostream>

UFO::UFO(sf::Vector2f position, const std::string& soundFile) 
    : pos(position), isSlowed(false), isDragged(false), sound(buffer) {
    if (!buffer.loadFromFile(soundFile)) {
        std::cout << "[AVERTISMENT] Nu s-a putut incarca sunetul OZN din: " << soundFile << "\n";
    }
}




void UFO::attach(Planet* p) { 
    if (p) observers.push_back(p); 
}




void UFO::toggleSlow() {
    isSlowed = !isSlowed;
    
    sound.stop();
    float pitch = isSlowed ? 0.5f : 1.0f;
    sound.setPitch(pitch);
    sound.play();

    for (Planet* p : observers) {
        if (p) p->setPlaybackSpeed(pitch);
    }
}



void UFO::update(float dt, const sf::RenderWindow& window) {
    if (isDragged) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        pos = window.mapPixelToCoords(mousePos);
    }
}




void UFO::setDragged(bool dragged) {
    isDragged = dragged;
}




void UFO::draw(sf::RenderWindow& window) {
    sf::CircleShape disc(25.f, 30);
    disc.setOrigin({25.f, 25.f});
    disc.setPosition(pos);
    disc.setFillColor(isSlowed ? sf::Color(255, 165, 0) : sf::Color::Cyan);
    sf::CircleShape dome(15.f, 30);
    dome.setOrigin({15.f, 15.f});
    dome.setPosition({pos.x, pos.y - 10.f}); 
    dome.setFillColor(sf::Color(200, 200, 255));

    window.draw(disc);
    window.draw(dome);
}




bool UFO::contains(sf::Vector2f point) {
    float dx = pos.x - point.x;
    float dy = pos.y - point.y;
    return (dx * dx + dy * dy) < (25.f * 25.f);
}