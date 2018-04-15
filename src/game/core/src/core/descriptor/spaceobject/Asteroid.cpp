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

#include "Asteroid.hpp"

namespace core {

const int AsteroidDescr::ARMOR_MIN = 10;
const int AsteroidDescr::ARMOR_MAX = 100;
const int AsteroidDescr::SCALE_MIN = 50;
const int AsteroidDescr::SCALE_MAX = 100;
const int AsteroidDescr::DISTANCE_MIN = 400;
const int AsteroidDescr::DISTANCE_MAX = 1600;
const int AsteroidDescr::SPEED_MIN = 40;
const int AsteroidDescr::SPEED_MAX = 100;

AsteroidDescr::AsteroidDescr()
{
    setType(Type::ASTEROID);
    setObType(entity::Type::ASTEROID);
}

} // namespace descriptor
