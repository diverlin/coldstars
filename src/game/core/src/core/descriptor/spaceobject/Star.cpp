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

#include "Star.hpp"

namespace descriptor {

const int Star::SCALE_MIN = 200;
const int Star::SCALE_MAX = 300;
const int Star::DISTANCE_MIN = 50;
const int Star::DISTANCE_MAX = 100;
const int Star::SPEED_MIN = 5;
const int Star::SPEED_MAX = 10;

Star::Star()
{
    setType(Type::STAR);
}

} // namespace descriptor
