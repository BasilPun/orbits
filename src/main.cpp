#include <bn_core.h>
#include <bn_backdrop.h>
#include <bn_color.h>
#include <bn_keypad.h>
#include <bn_fixed_point.h>
#include <bn_sprite_ptr.h>
#include <bn_vector.h>

#include "Center.h"
#include "movement.h"
#include "Orbiter.h"

// A scaling factor by which to reduce the force applied when orbiting
// Important for numerical stability
static constexpr bn::fixed FORCE_SCALE = 10;

// Maximum number of orbiters allowed on the screen
static constexpr int MAX_ORBITERS = 30;

// Default starting posiiton and velocity for Orbiter
static constexpr bn::fixed_point ORBITER_START_POSIITON = {0, 0};
static constexpr bn::fixed_point ORBITER_START_VELOCITY = {0, 5};

int main()
{
    bn::core::init();

    Center center = Center({30, 40}, .05, 2);
    bn::vector<Orbiter, MAX_ORBITERS> orbiters = {};

    while (true)
    {
        // Add an orbiter when A is pressed if there's room
        if (bn::keypad::a_pressed())
        {
            if (orbiters.size() < 1)
            {
                orbiters.push_back(Orbiter(ORBITER_START_POSIITON, ORBITER_START_VELOCITY, center, true));
            }
            else if (orbiters.size() < MAX_ORBITERS)
            {
                // for the body, start location will be head's/previous body parts location and head's velocity will carry on
                // bug: orbiters.back()._sprite.position() spawns it right on top... we want it a lil back
                // maybe make orbiters remember their past few frames of location?
                orbiters.push_back(Orbiter(orbiters.back().positions.back(), orbiters.back()._velocity, center, false));
            }
        }

        // Remove an orbiter when B is pressed if there's at least one
        if (bn::keypad::b_pressed())
        {
            if (orbiters.size() > 0)
            {
                orbiters.pop_back();
            }
        }

        center.update();
        for (Orbiter &orbiter : orbiters)
        {
            orbiter.update();
        }

        bn::core::update();
    }
}