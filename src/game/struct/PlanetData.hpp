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

#ifndef PLANETDATA_H
#define PLANETDATA_H

#include <glm/glm.hpp>
#include "../common/constants.hpp"

struct PlanetData
{
    glm::vec3 orbit_center; 
    int radius_A;
    int radius_B; 
    float orbit_phi_inD;
    float speed;
    bool clockwise;

    PlanetData():
    orbit_center(glm::vec3(0, 0, DEFAULT_ENTITY_ZPOS)),
    radius_A(0),
        radius_B(0), 
        orbit_phi_inD(0.0),
        speed(0.0),
        clockwise(false)
        {};
};

#endif
