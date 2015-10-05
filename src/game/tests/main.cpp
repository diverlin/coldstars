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
#include <world/starsystem.hpp>
#include <items/others/Bomb.hpp>
#include <slots/ItemSlot.hpp>
#include <spaceobjects/Container.hpp>


#include <builder/spaceobjects/ShipBuilder.hpp>
#include <builder/world/GalaxyBuilder.hpp>
#include <builder/world/SectorBuilder.hpp>
#include <builder/world/StarSystemBuilder.hpp>
#include <builder/items/other/BombBuilder.hpp>
#include <builder/spaceobjects/ContainerBuilder.hpp>
#include <descriptors/GalaxyDescriptor.hpp>
#include <descriptors/SectorDescriptor.hpp>
#include <descriptors/StarSystemDescriptor.hpp>

int test_bomb()
{
    // create builders
    auto starsystemBuilder = new StarSystemBuilder;
    auto shipBuilder = new ShipBuilder;
    auto bombBuilder = new BombBuilder;
    auto containerBuilder = new ContainerBuilder;

    // create entities
    auto starsystem = starsystemBuilder->create(StarSystemDescriptor());
    auto ship = shipBuilder->create(/*ShipDescriptor()*/);
    auto bomb = bombBuilder->create(/*BombDescriptor()*/);
    auto container = containerBuilder->create(bomb);

    // inject entities
    starsystem->add(ship, glm::vec3(0.0f), glm::vec3(0.0f));
    starsystem->add(container, glm::vec3(0.0f));

    // simulate bomb explosion
    container->hit(container->armor());
    //starystem->update();

    // check consequences

}

int main()
{
    test_bomb();
//    auto galaxyBuilder = new GalaxyBuilder;
//    auto sectorBuilder = new SectorBuilder;
//    auto starsystemBuilder = new StarSystemBuilder;
//    auto shipBuilder = new ShipBuilder;

//    GalaxyDescriptor galaxyDescriptor;
//    SectorDescriptor sectorDescriptor;
//    StarSystemDescriptor starsystemDescriptor;

//    auto galaxy = galaxyBuilder->create(galaxyDescriptor);
//    auto sector = sectorBuilder->create(sectorDescriptor);
//    auto starsystem = starsystemBuilder->create(starsystemDescriptor);
//    auto ship = shipBuilder->create();
}

