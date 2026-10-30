#include "Orbiter.h"

#include "bn_sprite_items_snakehead.h"
#include "bn_sprite_items_snakebody.h"

Orbiter::Orbiter(bn::fixed_point starting_location, bn::fixed_point starting_velocity, Center &center, bool isHead) : _sprite(isHead ? (bn::sprite_items::snakehead.create_sprite(starting_location)) : (bn::sprite_items::snakebody.create_sprite(starting_location))),
                                                                                                                      _velocity(starting_velocity),
                                                                                                                      _center(center)
{
}

void Orbiter::update()
{
    // A vector from the Orbiter to the Center
    bn::fixed_point delta = _center.position() - _sprite.position();

    // Scale the vector by the mass and apply a FORCE_SCALE
    // This is done in two steps instead of having a pre-scaled mass to prevent loss of
    // fixed point precision
    bn::fixed_point force = delta * _center.mass();
    static constexpr bn::fixed FORCE_SCALE = 10;
    force /= FORCE_SCALE;

    // Update the current velocity with the force
    _velocity += force;

    // Update the position by taking a step by the velocity vector
    _sprite.set_position(_sprite.position() + _velocity);
}
