//
// Created by dawud on 8/24/26.
//

#ifndef DAWUDENGINE_DATATABLES_H
#define DAWUDENGINE_DATATABLES_H


#include <SFML/System/Time.hpp>

#include <vector>
#include <functional>

#include "ResourceIndentifiers.h"

class Aircraft;

struct Direction {
    Direction(float angle, float distance)
        : angle(angle)
        , distance(distance) {
    }

    float angle;
    float distance;
};

struct AircraftData {
    int hitpoints;
    float speed;
    Textures::ID texture;
    sf::Time fireInterval;
    std::vector<Direction> directions;
};

struct ProjectileData {
    int damage;
    float speed;
    Textures::ID texture;
};

struct PickupData {
    std::function<void(Aircraft &)> action;
    Textures::ID texture;
};


std::vector<AircraftData> initialiseAircraftData();
std::vector<ProjectileData> initialiseProjectileData();
std::vector<PickupData> initialisePickupData();


#endif //DAWUDENGINE_DATATABLES_H
