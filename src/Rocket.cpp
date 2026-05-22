#include "../include/Rocket.h"
#include <iostream>
#include <algorithm>

Rocket::Rocket(sf::Vector2f position, const std::string& textureFile, const std::string& soundFile) 
    : pos(position), isActive(false), isDragged(false), sound(buffer) { 
    if (!buffer.loadFromFile(soundFile)) {
        std::cout << "[AVERTISMENT] Nu s-a putut incarca sunetul din: " << soundFile << "\n";
    }
}



void Rocket::update(float dt, const sf::RenderWindow& window) {
    if (isDragged) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        pos = window.mapPixelToCoords(mousePos);
    }
}



void Rocket::draw(sf::RenderWindow& window) {
    sf::RectangleShape body({30.f, 60.f});
    body.setOrigin({15.f, 30.f});
    body.setPosition(pos);
    body.setFillColor(isActive ? sf::Color::Red : sf::Color(150, 150, 150));

    sf::ConvexShape nose(3);
    nose.setPoint(0, {0.f, -30.f});
    nose.setPoint(1, {-15.f, 0.f});
    nose.setPoint(2, {15.f, 0.f});
    nose.setPosition({pos.x, pos.y - 30.f});
    nose.setFillColor(sf::Color::Red);

    sf::ConvexShape leftWing(3);
    leftWing.setPoint(0, {0.f, 0.f});
    leftWing.setPoint(1, {-15.f, 20.f});
    leftWing.setPoint(2, {0.f, 20.f});
    leftWing.setPosition({pos.x - 15.f, pos.y + 10.f});
    leftWing.setFillColor(sf::Color::Red);

    sf::ConvexShape rightWing(3);
    rightWing.setPoint(0, {0.f, 0.f});
    rightWing.setPoint(1, {15.f, 20.f});
    rightWing.setPoint(2, {0.f, 20.f});
    rightWing.setPosition({pos.x + 15.f, pos.y + 10.f});
    rightWing.setFillColor(sf::Color::Red);

    window.draw(body);
    window.draw(nose);
    window.draw(leftWing);
    window.draw(rightWing);
}




bool Rocket::contains(sf::Vector2f point) {
    sf::FloatRect bounds({pos.x - 20.f, pos.y - 55.f}, {40.f, 90.f});
    return bounds.contains(point);
}




void Rocket::toggleActive() {
    isActive = !isActive;
    if (isActive) sound.play();
    else sound.stop();
    
    notifyObservers(); 
}




void Rocket::attach(Planet* planet) {
    if (planet) {
        observers.push_back(planet);
        float pitch = isActive ? 2.0f : 1.0f;
        planet->setPlaybackSpeed(pitch);
    }
}




void Rocket::detach(Planet* planet) {
    observers.erase(std::remove(observers.begin(), observers.end(), planet), observers.end());
}




void Rocket::notifyObservers() {
    float pitch = isActive ? 2.0f : 1.0f;
    for (Planet* planet : observers) {
        if (planet) planet->setPlaybackSpeed(pitch);
    }
}