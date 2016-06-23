#pragma once
#include <SFML/Graphics.hpp>

//Si votre jeu à des problème de ralentissement vous pouvez modifier cette valeur (30-60)
const sf::Time TimePerFrame = sf::seconds(1.f / 30.f);
const float FTimePerFrame = 1.f / 30.f;
const int FPSFramerate = 30;