#pragma once
#include <map>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

template <typename T>
class ResourceManager {
private:
    std::map<std::string, T> resources;

public:
    ResourceManager() = default;

    T& get(const std::string& filePath) {
        auto it = resources.find(filePath);
        if (it != resources.end()) {
            return it->second;
        }

        T resource;
        //  (void)  pentru a spune compil. ca ignoram valoarea returnata
        (void)resource.loadFromFile(filePath);

        resources[filePath] = resource;
        return resources[filePath];
    }
};

template <>
inline sf::Font& ResourceManager<sf::Font>::get(const std::string& filePath) {
    auto it = resources.find(filePath);
    if (it != resources.end()) {
        return it->second;
    }
    sf::Font resource;
    if (!resource.openFromFile(filePath)) {
        std::cout << "[EROARE] Nu s-a putut deschide fontul: " << filePath << std::endl;
    }
    resources[filePath] = resource;
    return resources[filePath];
}