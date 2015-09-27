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

#include <common/Global.hpp>
#include <builder/spaceobjects/ShipBuilder.hpp>
#include <builder/world/GalaxyBuilder.hpp>
#include <builder/world/SectorBuilder.hpp>
#include <builder/world/StarSystemBuilder.hpp>
#include <descriptors/GalaxyDescriptor.hpp>
#include <descriptors/SectorDescriptor.hpp>
#include <descriptors/StarSystemDescriptor.hpp>

int main()
{
    auto galaxyBuilder = new GalaxyBuilder;
    auto sectorBuilder = new SectorBuilder;
    auto starsystemBuilder = new StarSystemBuilder;
    auto shipBuilder = new ShipBuilder;

    GalaxyDescriptor galaxyDescriptor;
    SectorDescriptor sectorDescriptor;
    StarSystemDescriptor starsystemDescriptor;

    auto galaxy = galaxyBuilder->create(galaxyDescriptor);
    auto sector = sectorBuilder->create(sectorDescriptor);
    auto starsystem = starsystemBuilder->create(starsystemDescriptor);

    auto ship = shipBuilder->create();
}

