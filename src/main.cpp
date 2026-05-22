#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../include/Planet.h"
#include "../include/Button.h"
#include "../include/Rocket.h"
#include "../include/UFO.h"
#include "../include/ElementFactory.h"
#include "../include/ResourceManager.h" 
#include <vector>
#include <memory>
#include <optional>
#include <iostream>

int main() {

    sf::RenderWindow window(sf::VideoMode({800, 600}), "Sistem Planetar - Music Studio");
    sf::Clock clock;
    ResourceManager<sf::Font> fontManager;
    ResourceManager<sf::SoundBuffer> soundManager; 
    sf::Font& font = fontManager.get("assets/Orbitron.ttf");
    std::vector<std::unique_ptr<BaseElement>> objects;
    std::vector<Button> buttons;

    buttons.push_back(Button({10, 10}, sf::Color::Red, "BASS", font));
    buttons.push_back(Button({120, 10}, sf::Color::Blue, "LEAD", font));
    buttons.push_back(Button({230, 10}, sf::Color::Green, "DRUM", font));
    buttons.push_back(Button({340, 10}, sf::Color::Magenta, "ROCKET", font));
    buttons.push_back(Button({450, 10}, sf::Color(255, 165, 0), "UFO", font));

    BaseElement* draggedObject = nullptr;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();

            // click stanga
            if (event->is<sf::Event::MouseButtonPressed>()) {
                const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();
                if (mouseEvent && mouseEvent->button == sf::Mouse::Button::Left) {
                    sf::Vector2f clickPos = window.mapPixelToCoords(mouseEvent->position);
                    bool buttonClicked = false;

                    for (auto& btn : buttons) {
                        if (btn.isClicked(clickPos)) {
                            buttonClicked = true;
                            sf::Vector2f spawnCenter{400.f, 300.f};

                            if (btn.getType() == "BASS") {
                                sf::SoundBuffer& buffer = soundManager.get("assets/bass.wav");
                                objects.push_back(std::make_unique<Planet>(25.f, sf::Color::Red, spawnCenter, buffer));
                            }
                            else if (btn.getType() == "LEAD") {
                                sf::SoundBuffer& buffer = soundManager.get("assets/lead.wav");
                                objects.push_back(std::make_unique<Planet>(20.f, sf::Color::Blue, spawnCenter, buffer));
                            }
                            else if (btn.getType() == "DRUM") {
                                sf::SoundBuffer& buffer = soundManager.get("assets/drum.wav");
                                objects.push_back(std::make_unique<Planet>(30.f, sf::Color::Green, spawnCenter, buffer));
                            }
                            else if (btn.getType() == "ROCKET") {
                                auto rocket = ElementFactory::create(ElementType::ROCKET, spawnCenter);
                                Rocket* ptr = dynamic_cast<Rocket*>(rocket.get());
                                for(auto& obj : objects) {
                                    if(auto p = dynamic_cast<Planet*>(obj.get())) ptr->attach(p);
                                }
                                objects.push_back(std::move(rocket));
                            }
                            else if (btn.getType() == "UFO") {
                                auto ufo = ElementFactory::create(ElementType::UFO, spawnCenter);
                                UFO* ptr = dynamic_cast<UFO*>(ufo.get());
                                for(auto& obj : objects) {
                                    if(auto p = dynamic_cast<Planet*>(obj.get())) ptr->attach(p);
                                }
                                objects.push_back(std::move(ufo));
                            }
                            break;
                        }
                    }

                    if (!buttonClicked) {
                        for (auto it = objects.rbegin(); it != objects.rend(); ++it) {
                            if ((*it)->contains(clickPos)) {
                                draggedObject = it->get();
                                draggedObject->setDragged(true);
                                break;
                            }
                        }
                    }
                }
            }
            if (event->is<sf::Event::MouseButtonReleased>()) {
                const auto* mouseEvent = event->getIf<sf::Event::MouseButtonReleased>();
                if (mouseEvent && mouseEvent->button == sf::Mouse::Button::Left) {
                    if (draggedObject) {
                        draggedObject->setDragged(false);
                        draggedObject = nullptr;
                    }
                }
            }

            // click dreappta
           
            if (event->is<sf::Event::MouseButtonPressed>()) {
                const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();
                if (mouseEvent && mouseEvent->button == sf::Mouse::Button::Right) {
                    sf::Vector2f clickPos = window.mapPixelToCoords(mouseEvent->position);
                    
                    for (auto it = objects.rbegin(); it != objects.rend(); ++it) {
                        if ((*it)->contains(clickPos)) {
                            if (Rocket* rocketPtr = dynamic_cast<Rocket*>(it->get())) {
                                rocketPtr->toggleActive();
                                break;
                            }
                            else if (UFO* ufoPtr = dynamic_cast<UFO*>(it->get())) {
                                ufoPtr->toggleSlow();
                                break;
                            }
                            else if (Planet* planetPtr = dynamic_cast<Planet*>(it->get())) {
                                planetPtr->toggleLoop();
                                break;
                            }
                        }
                    }
                }
            }
        }

        for (auto& obj : objects) {
            obj->update(dt, window);
        }

        window.clear(sf::Color(10, 10, 25));
        
        for (auto& obj : objects) {
            obj->draw(window);
        }
        
        for (auto& btn : buttons) {
            btn.draw(window);
        }
        
        window.display();
    }
    return 0;
}