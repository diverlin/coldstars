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


#pragma once

#include <core/type/TechLevelType.hpp>
#include <core/descriptor/spaceobject/Vehicle.hpp>

class Vehicle;

class BaseVehicle
{
public:
    static void equip(Vehicle* vehicle, descriptor::Vehicle* descriptor);
    static void equip(Vehicle*, tech::type tech_leve = tech::type::LEVEL0);
    static void equipModules(Vehicle*, tech::type tech_leve = tech::type::LEVEL0);
    static void equipArtefacts(Vehicle*, tech::type tech_leve = tech::type::LEVEL0);
    static void equipBomb(Vehicle*, tech::type tech_leve = tech::type::LEVEL0);

protected:
    static void _createSlots(Vehicle*);
}; 
