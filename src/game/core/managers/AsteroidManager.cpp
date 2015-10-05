/*
    Copyright (C) ColdStars, Aleksandr Pivovarov <<coldstars8@gmail.com>>
    
    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.
    
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include "AsteroidManager.hpp"
#include <common/Global.hpp>
#include <common/TurnTimer.hpp>
#include <world/starsystem.hpp>
#include "../builder/spaceobjects/AsteroidBuilder.hpp"
#include "../spaceobjects/Asteroid.hpp"

void AsteroidManager::Update(StarSystem* starsystem)
{
    while (starsystem->asteroidNum() < asteroid_num) {
        starsystem->add(global::get().asteroidBuilder().create());
        int current_turn_counter = global::get().turnTimer().getStopTurnTimer();
        asteroid_last_turn_created = current_turn_counter;
        if ((asteroid_last_turn_created + asteroid_delay) > current_turn_counter) {
            break;
        }
    }
}
