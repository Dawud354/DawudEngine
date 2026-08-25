//
// Created by dawud on 6/11/26.
//

#ifndef DAWUDENGINE_CATEGORY_H
#define DAWUDENGINE_CATEGORY_H

// The book used bits to represent the categories
// So I am capped at like 32 I think. It is ok

// Entity/scene node category, used to dispatch commands
namespace Category
{
    enum Type
    {
        None				= 0,
        SceneAirLayer		= 1 << 0,
        PlayerAircraft		= 1 << 1,
        AlliedAircraft		= 1 << 2,
        EnemyAircraft		= 1 << 3,
        Pickup				= 1 << 4,
        AlliedProjectile	= 1 << 5,
        EnemyProjectile		= 1 << 6,

        Aircraft = PlayerAircraft | AlliedAircraft | EnemyAircraft,
        Projectile = AlliedProjectile | EnemyProjectile,
    };
}

#endif //DAWUDENGINE_CATEGORY_H
