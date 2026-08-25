//
// Created by dawud on 8/24/26.
//

#include "DataTables.h"
#include "Aircraft.h"
#include "Pickup.h"
#include "Projectile.h"

// For std::bind() placeholders _1, _2, ...
using namespace std::placeholders;


// Idk if there is a better way to do this but at least with this stuff is local
// and won't interfere with one another
namespace {
    int TypeToInt(Aircraft::Type aircraftType) {
        return static_cast<int>(aircraftType);
    }
    int TypeToInt(Projectile::Type projectileType) {
        return static_cast<int>(projectileType);
    }
    int TypeToInt(Pickup::Type projectileType) {
        return static_cast<int>(projectileType);
    }
}

// The book used push_back but clion told me to use emplace_back cos it is faster
std::vector<AircraftData> initializeAircraftData()
{
    std::vector<AircraftData> data(TypeToInt(Aircraft::Type::TypeCount));

    data[TypeToInt(Aircraft::Type::Eagle)].hitpoints = 100;
    data[TypeToInt(Aircraft::Type::Eagle)].speed = 200.f;
    data[TypeToInt(Aircraft::Type::Eagle)].fireInterval = sf::seconds(1);
    data[TypeToInt(Aircraft::Type::Eagle)].texture = Textures::Eagle;

    data[TypeToInt(Aircraft::Type::Raptor)].hitpoints = 20;
    data[TypeToInt(Aircraft::Type::Raptor)].speed = 80.f;
    data[TypeToInt(Aircraft::Type::Raptor)].texture = Textures::Raptor;
    data[TypeToInt(Aircraft::Type::Raptor)].directions.emplace_back(+45.f, 80.f);
    data[TypeToInt(Aircraft::Type::Raptor)].directions.emplace_back(-45.f, 160.f);
    data[TypeToInt(Aircraft::Type::Raptor)].directions.emplace_back(+45.f, 80.f);
    data[TypeToInt(Aircraft::Type::Raptor)].fireInterval = sf::Time::Zero;

    data[TypeToInt(Aircraft::Type::Avenger)].hitpoints = 40;
    data[TypeToInt(Aircraft::Type::Avenger)].speed = 50.f;
    data[TypeToInt(Aircraft::Type::Avenger)].texture = Textures::Avenger;
    data[TypeToInt(Aircraft::Type::Avenger)].directions.emplace_back(+45.f,  50.f);
    data[TypeToInt(Aircraft::Type::Avenger)].directions.emplace_back( 0.f,  50.f);
    data[TypeToInt(Aircraft::Type::Avenger)].directions.emplace_back(-45.f, 100.f);
    data[TypeToInt(Aircraft::Type::Avenger)].directions.emplace_back( 0.f,  50.f);
    data[TypeToInt(Aircraft::Type::Avenger)].directions.emplace_back(+45.f,  50.f);
    data[TypeToInt(Aircraft::Type::Avenger)].fireInterval = sf::seconds(2);

    return data;
}

std::vector<ProjectileData> initializeProjectileData() {
    std::vector<ProjectileData> data(TypeToInt(Projectile::Type::TypeCount));

    data[TypeToInt(Projectile::Type::AlliedBullet)].damage = 10;
    data[TypeToInt(Projectile::Type::AlliedBullet)].speed = 300.f;
    data[TypeToInt(Projectile::Type::AlliedBullet)].texture = Textures::Bullet;

    data[TypeToInt(Projectile::Type::EnemyBullet)].damage = 10;
    data[TypeToInt(Projectile::Type::EnemyBullet)].speed = 300.f;
    data[TypeToInt(Projectile::Type::EnemyBullet)].texture = Textures::Bullet;

    data[TypeToInt(Projectile::Type::Missile)].damage = 200;
    data[TypeToInt(Projectile::Type::Missile)].speed = 150.f;
    data[TypeToInt(Projectile::Type::Missile)].texture = Textures::Missile;

    return data;
}

std::vector<PickupData> initializePickupData() {
    std::vector<PickupData> data(TypeToInt(Pickup::Type::TypeCount));
    
    data[TypeToInt(Pickup::Type::HealthRefill)].texture = Textures::HealthRefill;
    data[TypeToInt(Pickup::Type::HealthRefill)].action = [] (Aircraft& a) { a.repair(25); };

    // clion is telling me off that is should use lambda but idk how to change bind to a lambda
    data[TypeToInt(Pickup::Type::MissileRefill)].texture = Textures::MissileRefill;
    data[TypeToInt(Pickup::Type::MissileRefill)].action = std::bind(&Aircraft::collectMissiles, _1, 3);
	
    data[TypeToInt(Pickup::Type::FireSpread)].texture = Textures::FireSpread;
    data[TypeToInt(Pickup::Type::FireSpread)].action = std::bind(&Aircraft::increaseSpread, _1);
	
    data[TypeToInt(Pickup::Type::FireRate)].texture = Textures::FireRate;
    data[TypeToInt(Pickup::Type::FireRate)].action = std::bind(&Aircraft::increaseFireRate, _1);
}
