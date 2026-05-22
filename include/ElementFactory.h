#pragma once
#include <memory>
#include "Rocket.h"
#include "UFO.h"
#include "Planet.h"
#include "BaseElement.h"

enum class ElementType { ROCKET, UFO, PLANET };

class ElementFactory {
public:
    static std::unique_ptr<BaseElement> create(ElementType type, sf::Vector2f pos) {
        if (type == ElementType::ROCKET) 
            return std::make_unique<Rocket>(pos, "assets/rocket.png", "assets/rocket.wav");
        
        if (type == ElementType::UFO) 
            return std::make_unique<UFO>(pos, "assets/ozn.wav");
            
        return nullptr;
    }
};