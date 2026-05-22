# Proiect2_POO
Sistem Planetar Interactiv - Music Studio


Un studio muzical interactiv bazat pe conceptul unui sistem planetar, dezvoltat în C++ folosind grafica și procesarea audio din biblioteca SFML. Proiectul simulează un mediu spațial în care utilizatorul poate interacționa polimorfic cu diverse elemente (Planete, Rachete, OZN-uri) pentru a genera, modifica și controla bucle muzicale în timp real.

Tehnologii și Cerințe de Sistem

Limbaj de programare: C++ (Standard minim C++17)
Librărie multimedia: SFML 3.0.0 (Folosită pentru randare grafică, gestionarea evenimentelor ferestrei și redare audio avansată)
Compilator: g++ (recomandat din suita MinGW-w64, versiunea GCC 13+ / 15+)
Sistem de build: Script automatizat de compilare locală (build.bat)

Structură și Principii POO Aplicate


Moștenire și Polimorfism: Toate obiectele din spațiu moștenesc clasa abstractă BaseElement. Interacțiunile de desenare (draw), actualizare (update) și detecție (contains) sunt complet polimorfe.

Genericitate (Templates): Implementarea clasei ResourceManager<T> (cu specializare pentru sf::Font) care asigură încărcarea o singură dată în memorie a resurselor grele (SoundBuffers, Fonturi), optimizând consumul de memorie RAM (conceptul Flyweight).

Design Patterns:

Factory Method (ElementFactory): Centralizează și decuplează logica de creare a obiectelor complexe de tip Rachetă și OZN.

Observer Pattern: Vehiculele spațiale acționează ca subiecte (Subjects) care își notifică observatorii (Observers - planetele atașate) pentru a-și modifica dinamic viteza sunetului în funcție de efectele active.


Cum se compilează

Asigură-te că ai calea către compilatorul g++ adăugată în variabilele de mediu (PATH).
Deschide o consolă (Terminal / Command Prompt) în folderul principal al proiectului.


Nu au putut fi încărcate toate fișierele SFML
Rulează scriptul de build:

.\build.bat

Executabilul compilat va fi plasat în folderul bin/. Mergi în bin/ și rulează proiect_poo.exe.
